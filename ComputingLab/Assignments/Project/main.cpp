#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <signal.h>
#include <thread>
#include <pthread.h>

using namespace std;
#define MAXINODE 10000

#define READ 1
#define WRITE 2

#define MAXFILESIZE 1024

#define REGULAR 1
#define SPECIAL 2

#define START 0
#define CURRENT 1
#define END 2

typedef struct superblock
{
    int TotalInodes;
    int FreeInode;
} SUPERBLOCK, *PSUPERBLOCK;

typedef struct inode
{
    char FileName[50];
    int InodeNumber;
    int FileSize;
    int FileActualSize;
    int FileType;
    char *Buffer;
    int LinkCount;
    char *created;
    char *modified;
    int ReferenceCount;
    // 1+2  3
    int permission;
    struct inode *next;
} INODE, *PINODE;

typedef struct filetable
{
    int readoffset;
    int writeoffset;
    int count;
    // 1 2 3
    int mode;
    PINODE ptrinode;
} FILETABLE, *PFILETABLE;

typedef struct ufdt
{
    PFILETABLE ptrfiletable;
} UFDT;

UFDT UFDTArr[10000];
SUPERBLOCK SUPERBLOCKobj;
PINODE head = NULL;

char *getCurrentDateTime()
{

    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    std::tm localTime = *std::localtime(&currentTime);

    std::ostringstream dateTimeStream;
    dateTimeStream << std::put_time(&localTime, "%d/%m/%Y");

    std::string date = dateTimeStream.str();

    char *cstr = new char[date.size() + 1];

    std::strcpy(cstr, date.c_str());

    return cstr;
}

void DisplayHelp()
{
    printf("\nls     : To List out all files\n");
    printf("\nls -l  : To List out all files in details\n");
    printf("create   : To create a new file\n");
    printf("read     : To Read the content from file\n");
    printf("write    : To Write content into file\n");
    printf("delete   : To Delete the file\n");
    printf("clear    : To clear console\n");
    printf("exit     : To Terminate file system\n");
}

int GetFDFromName(char *name)
{
    int i = 0;

    while (i < 50)
    {
        if (UFDTArr[i].ptrfiletable != NULL)
            if (strcmp((UFDTArr[i].ptrfiletable->ptrinode->FileName), name) == 0)
                break;
        i++;
    }

    if (i == 50)
        return -1;
    else
        return i;
}

PINODE Get_Inode(char *name)
{
    PINODE temp = head;
    int i = 0;

    if (name == NULL)
        return NULL;

    while (temp != NULL)
    {
        if (strcmp(name, temp->FileName) == 0)
            break;
        temp = temp->next;
    }
    return temp;
}

void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = head;

    while (i <= MAXINODE)
    {
        newn = (PINODE)malloc(sizeof(INODE));

        newn->LinkCount = 0;
        newn->ReferenceCount = 0;
        newn->FileType = 0;
        newn->FileSize = 0;

        newn->Buffer = NULL;
        newn->next = NULL;

        newn->InodeNumber = i;

        if (temp == NULL)
        {
            head = newn;
            temp = head;
        }
        else
        {
            temp->next = newn;
            temp = temp->next;
        }
        i++;
    }
    printf("\n---DILB created successfully---\n");
}

void InitaliseSuperBlock()
{
    int i = 0;
    while (i < MAXINODE)
    {
        UFDTArr[i].ptrfiletable = NULL;
        i++;
    }

    SUPERBLOCKobj.TotalInodes = MAXINODE;
    SUPERBLOCKobj.FreeInode = MAXINODE;
}

int CreateFile(char *name, int permission)
{
    int i = 0;
    PINODE temp = head;

    if ((name == NULL) || (permission == 0) || (permission > 3))
        return -1;

    if (SUPERBLOCKobj.FreeInode == 0)
        return -2;

    (SUPERBLOCKobj.FreeInode)--;

    if (Get_Inode(name) != NULL)
        return -3;

    if (temp == NULL)
        return -4; // No available inode found
    while (temp != NULL)
    {
        if (temp->FileType == 0)
            break;
        temp = temp->next;
    }

    while (i < 10000)
    {
        if (UFDTArr[i].ptrfiletable == NULL)
            break;
        i++;
    }

    if (i == 10000)
        return -5; // No free file table entry

    UFDTArr[i].ptrfiletable = (PFILETABLE)malloc(sizeof(FILETABLE));

    UFDTArr[i].ptrfiletable->count = 1;
    UFDTArr[i].ptrfiletable->mode = permission;
    UFDTArr[i].ptrfiletable->readoffset = 0;
    UFDTArr[i].ptrfiletable->writeoffset = 0;

    UFDTArr[i].ptrfiletable->ptrinode = temp;

    strcpy(UFDTArr[i].ptrfiletable->ptrinode->FileName, name);
    UFDTArr[i].ptrfiletable->ptrinode->FileType = REGULAR;
    UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount = 1;
    UFDTArr[i].ptrfiletable->ptrinode->LinkCount = 1;
    UFDTArr[i].ptrfiletable->ptrinode->created = getCurrentDateTime();
    UFDTArr[i].ptrfiletable->ptrinode->modified = NULL;
    UFDTArr[i].ptrfiletable->ptrinode->FileSize = MAXFILESIZE;
    UFDTArr[i].ptrfiletable->ptrinode->FileActualSize = 0;
    UFDTArr[i].ptrfiletable->ptrinode->permission = permission;
    UFDTArr[i].ptrfiletable->ptrinode->Buffer = (char *)malloc(MAXFILESIZE);

    return i;
}

int rm_File(char *name)
{
    int fd = 0, result = 0;

    fd = GetFDFromName(name);
    if (fd == -1)
        result = -1;

    (UFDTArr[fd].ptrfiletable->ptrinode->LinkCount)--;

    if (UFDTArr[fd].ptrfiletable->ptrinode->LinkCount == 0)
    {

        UFDTArr[fd].ptrfiletable->ptrinode->FileType = 0;
        free(UFDTArr[fd].ptrfiletable->ptrinode->Buffer);
        free(UFDTArr[fd].ptrfiletable);
    }

    UFDTArr[fd].ptrfiletable = NULL;
    (SUPERBLOCKobj.FreeInode)++;
    return result;
}

int ReadFile(int fd, char *arr, int isize)
{
    int read_size = 0;

    if (UFDTArr[fd].ptrfiletable == NULL)
        return -1;

    if (UFDTArr[fd].ptrfiletable->mode != READ && UFDTArr[fd].ptrfiletable->mode != READ + WRITE)
        return -2;

    if (UFDTArr[fd].ptrfiletable->ptrinode->permission != READ && UFDTArr[fd].ptrfiletable->ptrinode->permission != READ + WRITE)
        return -2;

    if (UFDTArr[fd].ptrfiletable->readoffset == UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)
        return -3;

    if (UFDTArr[fd].ptrfiletable->ptrinode->FileType != REGULAR)
        return -4;

    read_size = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) - (UFDTArr[fd].ptrfiletable->readoffset);

    if (read_size < isize)
    {
        strncpy(arr, (UFDTArr[fd].ptrfiletable->ptrinode->Buffer) + (UFDTArr[fd].ptrfiletable->readoffset), read_size);

        UFDTArr[fd].ptrfiletable->readoffset = UFDTArr[fd].ptrfiletable->readoffset + read_size;
    }
    else
    {
        strncpy(arr, (UFDTArr[fd].ptrfiletable->ptrinode->Buffer) + (UFDTArr[fd].ptrfiletable->readoffset), isize);

        (UFDTArr[fd].ptrfiletable->readoffset) = (UFDTArr[fd].ptrfiletable->readoffset) + isize;
    }

    return read_size;
}

int WriteFile(int fd, char *arr, int isize)
{
    if (((UFDTArr[fd].ptrfiletable->mode) != WRITE) && ((UFDTArr[fd].ptrfiletable->mode) != READ + WRITE))
        return -1;

    if (((UFDTArr[fd].ptrfiletable->ptrinode->permission) != WRITE) && ((UFDTArr[fd].ptrfiletable->ptrinode->permission) != READ + WRITE))
        return -1;

    if ((UFDTArr[fd].ptrfiletable->writeoffset) == MAXFILESIZE)
        return -2;

    if ((UFDTArr[fd].ptrfiletable->ptrinode->FileType) != REGULAR)
        return -3;

    strncpy((UFDTArr[fd].ptrfiletable->ptrinode->Buffer) + (UFDTArr[fd].ptrfiletable->writeoffset), arr, isize);

    (UFDTArr[fd].ptrfiletable->writeoffset) = (UFDTArr[fd].ptrfiletable->writeoffset) + isize;

    (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + isize;
    UFDTArr[fd].ptrfiletable->ptrinode->modified = getCurrentDateTime();

    return isize;
}

int CloseFileByName(char *name)
{
    int i = 0;
    i = GetFDFromName(name);
    if (i == -1)
        return -1;

    UFDTArr[i].ptrfiletable->readoffset = 0;
    UFDTArr[i].ptrfiletable->writeoffset = 0;
    (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)--;

    return 0;
}

void ls_file_in_detail()
{
    int i = 0;
    PINODE temp = head;

    if (SUPERBLOCKobj.FreeInode == MAXINODE)
    {
        printf("Error : There is no files\n");
        return;
    }

    cout << "File size" << "\t\t" << "created" << "\t\t" << "modified" << "\t\t" << "File Name\n";

    while (temp != NULL)
    {
        if (temp->FileType != 0)
        {
            if (temp->modified != NULL)
                std::cout << temp->FileActualSize << "\t\t" << temp->created << "\t\t" << temp->modified << "\t\t" << temp->FileName << "\n";
            else
            {
                std::cout << temp->FileActualSize << "\t\t" << temp->created << "\t\t" << " " << "\t\t" << temp->FileName << "\n";
            }
        }
        temp = temp->next;
    }
}

void ls_file()
{
    int i = 0;
    PINODE temp = head;

    if (SUPERBLOCKobj.FreeInode == MAXINODE)
    {
        printf("Error : There is no files\n");
        return;
    }

    while (temp != NULL)
    {
        if (temp->FileType != 0)
        {
            printf("%s \n", temp->FileName);
        }
        temp = temp->next;
    }
}

void sigintHandler(int sig_num)
{

    signal(SIGINT, sigintHandler);
    printf("\n Cannot be terminated using Ctrl+C and use exit command\n");
    fflush(stdout);
}

void threadCreateFile(char *filename, int permission, int &result)
{
    result = CreateFile(filename, permission);
}

void threadWriteFile(int fd, char *arr, int isize, int &result)
{
    result = WriteFile(fd, arr, isize);
}

void threadReadFile(int fd, char *arr, int isize, int &result)
{
    result = ReadFile(fd, arr, isize);
}

void threadDeleteFile(char *name, int &result)
{
    result = rm_File(name);
}

int main()
{
    char *ptr = NULL;
    int ret = 0, fd = 0, count = 0;
    char command[100][80], str[80], arr[1024];
    strcpy(str, "");
    for (int i = 0; i < 100; i++)
    {
        strcpy(command[i], str);
    }

    InitaliseSuperBlock();
    CreateDILB();
    signal(SIGINT, sigintHandler);

    while (1)
    {
        fflush(stdin);
        strcpy(str, "");

        printf("\nMemfs:>");

        fgets(str, 80, stdin);

        count = 0;

        // Tokenize the input using a loop and store tokens in the command array
        // Tokenize by space or newline
        char *token = strtok(str, " \n");

        while (token != NULL && count < 100)
        {
            strcpy(command[count], token);
            count++;
            token = strtok(NULL, " \n");
        }

        if (count == 1)
        {
            if (strcmp(command[0], "ls") == 0)
            {
                ls_file();
            }
            else if (strcmp(command[0], "clear") == 0)
            {
#ifdef _WIN32
                system("cls"); // For Windows
#else
                system("clear"); // For Unix/Linux/Mac
#endif
                continue;
            }
            else if (strcmp(command[0], "help") == 0)
            {
                DisplayHelp();
                continue;
            }
            else if (strcmp(command[0], "exit") == 0)
            {
                printf("----------------Terminal Closed------------------\n\n");
                break;
            }
            else if (strcmp(command[0], "test") == 0)
            {
                char Files[100][50];
                std::thread WriteThreads[100];
                for (int i = 1; i <= 100; ++i)
                {
                    // Create the string in the format "i <string.i>"
                    std::string result = "file" + std::to_string(i);

                    // Print the string
                    const char *cstr = result.c_str();
                    std::strcpy(Files[i], cstr);
                }

                for (int i = 0; i < 100; i++)
                {
                    cout<<Files[i]<<"\n";
                    WriteThreads[i] = std::thread(threadCreateFile, Files[i], 3, std::ref(ret));
                    if (ret >= 0)
                        printf("File is successfully created with file descriptor : %d\n", ret);
                    if (ret == -1)
                        printf("ERROR : Incorrect parameters\n");
                    if (ret == -2)
                        printf("ERROR : There is no inodes\n");
                    if (ret == -3)
                        printf("ERROR : File already exists\n");
                    if (ret == -4)
                        printf("ERROR : Memory allocation failure\n");
                    // sleep(1);
                }
                for (int i = 0; i < 100; i++)
                {
                    WriteThreads[i].join();
                }
            }
            else
            {
                printf("\nERROR : Command not found !!!\n");
                continue;
            }
        }
        else if (count == 2)
        {
            if (strcmp(command[0], "ls") == 0 && strcmp(command[1], "-l") == 0)
            {
                ls_file_in_detail();
            }
            else if (strcmp(command[0], "create") == 0)
            {

                std::thread _CreateFile(threadCreateFile, command[1], 3, std::ref(ret));
                _CreateFile.join();
                if (ret >= 0)
                    printf("File is successfully created with file descriptor : %d\n", ret);
                if (ret == -1)
                    printf("ERROR : Incorrect parameters\n");
                if (ret == -2)
                    printf("ERROR : There is no inodes\n");
                if (ret == -3)
                    printf("ERROR : File already exists\n");
                if (ret == -4)
                    printf("ERROR : Memory allocation failure\n");

                continue;
            }

            else if (strcmp(command[0], "read") == 0)
            {

                fd = GetFDFromName(command[1]);
                if (fd == -1)
                {
                    printf("ERROR : Incorrect parameter\n");
                    continue;
                }
                ptr = (char *)malloc(sizeof(char) * (MAXFILESIZE + 1));

                if (ptr == NULL)
                {
                    printf("ERROR: Memory allocation failure\n");
                    continue;
                }
                std::thread _ReadFile(threadReadFile, fd, ptr, MAXFILESIZE, std::ref(ret));
                _ReadFile.join();
                // ret = ReadFile(fd, ptr, MAXFILESIZE);
                if (ret == -1)
                    printf("ERROR : File not existing\n");
                if (ret == -2)
                    printf("ERROR : Permission denied\n");
                if (ret == -3)
                    printf("ERROR : Reached at end of file\n");
                if (ret == -4)
                    printf("ERROR : It is not regular file\n");
                if (ret == 0)
                    printf("ERROR : File empty\n");
                if (ret > 0)
                {
                    write(2, ptr, ret);
                }
                ret = CloseFileByName(command[1]);
                if (ret == -1)
                    printf("ERROR : There is no such file\n");

                continue;
            }

            else if (strcmp(command[0], "delete") == 0)
            {
                std::thread _DeleteFile(threadDeleteFile, command[1], std::ref(ret));
                _DeleteFile.join();
                // ret = rm_File(command[1]);
                if (ret == -1)
                    printf("ERROR : There is no such file\n");
                continue;
            }

            else
            {
                printf("\nERROR : Command not found !!!\n");
                continue;
            }
        }
        else if (count == 3)
        {

            if (strcmp(command[0], "write") == 0)
            {

                fd = GetFDFromName(command[1]);
                if (fd == -1)
                {
                    printf("ERROR : Incorret parameter\n");
                    continue;
                }

                ret = strlen(command[2]);
                if (ret == 0)
                {
                    printf("ERROR : Incorrect parameter\n");
                    continue;
                }
                cout << ret << " \n";
                char *Info = (char *)malloc(sizeof(char) * ret + 1);
                strcpy(Info, command[2]);
                Info[ret + 1] = '\0';
                std::thread _WriteFile(threadWriteFile, fd, Info, ret, std::ref(ret));
                _WriteFile.join();
                // ret = WriteFile(fd, Info, ret);
                if (ret == -1)
                    printf("ERROR : Permission denied\n");
                if (ret == -2)
                    printf("ERROR : There is no sufficient memory to write\n");
                if (ret == -3)
                    printf("ERROR : It is not regular file\n");
            }
            else
            {
                printf("\nERROR : Command not found !!!\n");
                continue;
            }
        }
        else if (count > 3)
        {
            if (strcmp(command[0], "create") == 0 && strcmp(command[1], "-n") == 0)
            {
                int i = 2;
                while (1)
                {
                    if (strcmp(command[i], "") != 0)
                    {

                        // ret = CreateFile(command[i], 3);
                        std::thread _CreateFile(threadCreateFile, command[i], 3, std::ref(ret));
                        _CreateFile.join();
                        if (ret >= 0)
                            printf("File is successfully created with file descriptor : %d\n", ret);
                        if (ret == -1)
                            printf("ERROR : Incorrect parameters\n");
                        if (ret == -2)
                            printf("ERROR : There is no inodes\n");
                        if (ret == -3)
                            printf("ERROR : File already exists\n");
                        if (ret == -4)
                            printf("ERROR : Memory allocation failure\n");
                    }
                    else
                    {
                        break;
                    }
                    i++;
                }
                continue;
            }
            else if (strcmp(command[0], "delete") == 0 && strcmp(command[1], "-n") == 0)
            {
                int i = 2;
                while (1)
                {
                    if (strcmp(command[i], "") != 0)
                    {
                        std::thread _DeleteFile(threadDeleteFile, command[i], std::ref(ret));
                        _DeleteFile.join();
                        // ret = rm_File(command[i]);
                        if (ret == -1)
                            printf("ERROR : There is no such file\n");
                    }
                    else
                    {
                        break;
                    }
                    i++;
                }
                continue;
            }
        }
        else
        {
            continue;
        }
    }
    return 0;
}