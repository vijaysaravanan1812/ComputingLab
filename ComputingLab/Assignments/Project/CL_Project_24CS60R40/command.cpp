#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iomanip>



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

    while (i < MAXINODE)
    {
        if (UFDTArr[i].ptrfiletable != NULL)
            if (strcmp((UFDTArr[i].ptrfiletable->ptrinode->FileName), name) == 0)
                break;
        i++;
    }

    if (i == MAXINODE)
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
        return -4; 
    while (temp != NULL)
    {
        if (temp->FileType == 0)
            break;
        temp = temp->next;
    }

    while (i < MAXINODE)
    {
        if (UFDTArr[i].ptrfiletable == NULL)
            break;
        i++;
    }

    if (i == MAXINODE)
        return -5;

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
