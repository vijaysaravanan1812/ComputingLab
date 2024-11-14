#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>
#include <pthread.h>

#include "command.cpp"
#include <signal.h>

using namespace std;

pthread_mutex_t FileTable;

void sigintHandler(int sig_num)
{

    signal(SIGINT, sigintHandler);
    printf("\n Cannot be terminated using Ctrl+C and use exit command\n");
    fflush(stdout);
}

void threadCreateFile(char *filename, int permission, int &result)
{
    pthread_mutex_lock(&FileTable);
    result = CreateFile(filename, permission);
    pthread_mutex_unlock(&FileTable);
}

void threadWriteFile(int fd, char *arr, int isize, int &result)
{
    pthread_mutex_lock(&FileTable);
    result = WriteFile(fd, arr, isize);
    pthread_mutex_unlock(&FileTable);
}

void threadReadFile(int fd, char *arr, int isize, int &result)
{
    pthread_mutex_lock(&FileTable);
    result = ReadFile(fd, arr, isize);
    pthread_mutex_unlock(&FileTable);
}

void threadDeleteFile(char *name, int &result)
{
    pthread_mutex_lock(&FileTable);
    result = rm_File(name);
    pthread_mutex_unlock(&FileTable);
}

void Test(int Number, int ret, double *CreateTime, double *WriteTime, double *ReadTime, double *DeleteTime)
{
    char Files[Number][50];
    std::thread TestThreads[Number];
    for (int i = 0; i < Number; ++i)
    {
        
        std::string result = "file-" + std::to_string(i);

     
        const char *cstr = result.c_str();
        std::strcpy(Files[i], cstr);
    }

    for (int i = 0; i < Number; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        TestThreads[i] = std::thread(threadCreateFile, Files[i], 3, std::ref(ret));
        if (ret >= 0)
            printf("file created successfully\n");
        if (ret == -1)
            printf("ERROR : Incorrect parameters\n");
        if (ret == -2)
            printf("ERROR : There is no inodes\n");
        if (ret == -3)
            printf("ERROR : File already exists\n");
        if (ret == -4)
            printf("ERROR : Memory allocation failure\n");

        TestThreads[i].join();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        CreateTime[i] = elapsed.count(); 
    }

    for (int i = 0; i < Number; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        cout << Files[i] << "\n";
        int fd = GetFDFromName(Files[i]);
        if (fd == -1)
        {
            printf("ERROR : Incorret parameter\n");
            continue;
        }

        char Char[1000] = "Hello You need to run each of the above workloads\nand report the following metrics in each case:\n1. Average Latency\n2. CPU and Memory Utilization\nAdditionally, explain your observation of the impact of the number of threads on latency\nHello You need to run each of the above workloads\nand report the following metrics in each case:\n1. Average Latency\n2. CPU and Memory Utilization\nAdditionally, explain your observation of the impact of the number of threads on latency\0";
        ret = strlen(Char);
        if (ret == 0)
        {
            printf("ERROR : Incorrect parameter\n");
            continue;
        }

        char *Info = (char *)malloc(sizeof(char) * ret);
        strcpy(Info, Char);

        std::thread _WriteFile(threadWriteFile, fd, Info, ret, std::ref(ret));
        _WriteFile.join();
       
        if (ret == -1)
            printf("ERROR : Permission denied\n");
        else if (ret == -2)
            printf("ERROR : There is no sufficient memory to write\n");
        else if (ret == -3)
            printf("ERROR : It is not regular file\n");
        else
            cout << "successfully written to " << Files[i] << "\n";
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        WriteTime[i] = elapsed.count();
    }

    for (int i = 0; i < Number; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        int fd = GetFDFromName(Files[i]);
        if (fd == -1)
        {
            printf("ERROR : Incorrect parameter\n");
            continue;
        }
        char *ptr = (char *)malloc(sizeof(char) * (MAXFILESIZE + 1));

        if (ptr == NULL)
        {
            printf("ERROR: Memory allocation failure\n");
            continue;
        }
        std::thread _ReadFile(threadReadFile, fd, ptr, MAXFILESIZE, std::ref(ret));
        _ReadFile.join();

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
        ret = CloseFileByName(Files[i]);
        if (ret == -1)
            printf("ERROR : There is no such file\n");
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        ReadTime[i] = elapsed.count(); 
    }

    for (int i = 0; i < Number; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::thread _DeleteFile(threadDeleteFile, Files[i], std::ref(ret));
        _DeleteFile.join();
        
        if (ret == -1)
            printf("ERROR : There is no such file\n");
        else
        {
            cout << Files[i] << " Deleted Successfully\n";
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        DeleteTime[i] = elapsed.count(); 
    }
}

void WrapperTest(int Iteration)
{
    int ret = 0;
    double CreateTime[Iteration];
    double WriteTime[Iteration];
    double ReadTime[Iteration];
    double DeleteTime[Iteration];
    Test(Iteration, ret, CreateTime, WriteTime, ReadTime, DeleteTime);

    double CreateSum = 0;
    double WriteSum = 0;
    double ReadSum = 0;
    double DeleteSum = 0;
    for (int i = 0; i < Iteration; ++i)
    {
        CreateSum += CreateTime[i];
        WriteSum += WriteTime[i];
        ReadSum += ReadTime[i];
        DeleteSum += DeleteTime[i];
    }
    double CreateAverage = CreateSum / Iteration;
    double WriteAverage = WriteSum / Iteration;
    double ReadAverage = ReadSum / Iteration;
    double DeleteAverage = DeleteSum / Iteration;
    cout << "Average create latency " << CreateAverage << "\n";
    cout << "Average Write latency " << WriteAverage << "\n";
    cout << "Average Read latency " << ReadAverage << "\n";
    cout << "Average Delete latency " << DeleteAverage << "\n";
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: \n%s <Option>\nSelect the Option\n1 - Shell\n2 - To test 100 operations\n3 - To test 1000 operations\n4 - To test 10000 operations\n", argv[0]);
        return 1;
    }
    pthread_mutex_init(&FileTable, NULL);
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

    if (atoi(argv[1]) == 1)
    {
        while (1)
        {
            fflush(stdin);
            strcpy(str, "");

            printf("\nMemfs:>");

            fgets(str, 80, stdin);

            count = 0;

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
                        printf("files created successfully\n");
                    if (ret == -1)
                        printf("ERROR : Incorrect parameters\n");
                    if (ret == -2)
                        printf("ERROR : There is no inodes\n");
                    if (ret == -3)
                        printf("error: another file with same name exists\n");
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

                    if (ret == -1)
                        printf("ERROR : Permission denied\n");
                    else if (ret == -2)
                        printf("ERROR : There is no sufficient memory to write\n");
                    else if (ret == -3)
                        printf("ERROR : It is not regular file\n");
                    else
                    {
                        cout << "successfully written to " << command[1] << "\n";
                    }
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

                            
                            std::thread _CreateFile(threadCreateFile, command[i], 3, std::ref(ret));
                            _CreateFile.join();
                            if (ret >= 0)
                                printf("file created successfully\n");
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
    }
    else if (atoi(argv[1]) == 2)
    {
        WrapperTest(100);
    }
    else if (atoi(argv[1]) == 3)
    {
        WrapperTest(1000);
    }
    else if (atoi(argv[1]) == 4)
    {
        WrapperTest(10000);
    }
    else{
        cout<<"Invalid Option\n";
    }

    return 0;
}