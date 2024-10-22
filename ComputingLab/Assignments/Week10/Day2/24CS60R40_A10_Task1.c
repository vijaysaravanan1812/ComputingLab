#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define UNPROCESSED -1
#define PROCESSED 1


struct SharedResources {
    int **Matrix;
    int Rows;
    int Cols;
    int *A;
    int *B;
};

//Shared Memories
int *updatesProcessedByOrder;
int *ActiveChaosCount; 
int shmMatrixId; 
int shmAId, shmBId;
int shmUpdatesId, shmActiveChaosId;


sem_t SemArray, SemMatrix;
sem_t SemChoas, SemOrder;
//check for Active Chaos process
sem_t  SemActiveChaos;


void Chaos(struct SharedResources *details) {
    int **matrix = details->Matrix;
    int *A = details->A;
    int *B = details->B;
    int Rows = details->Rows;
    int Cols = details->Cols;

    printf("I am chaos (PID: %d)\n", getpid());
    sem_wait(&SemActiveChaos);
    (*ActiveChaosCount)++;

    sem_post(&SemActiveChaos);

    for (int updates = 0; updates < 30; updates++) {
        int i = rand() % Rows;
        int j = rand() % Cols;
        int k = (rand() % 1000) + 1;

        // Lock matrix to update a random element
        sem_wait(&SemChoas);
        sem_wait(&SemMatrix);
        matrix[i][j] = k;
        printf("Chaos: Updated element at cell %d x %d with value %d\n", i, j, k);
        sem_post(&SemMatrix);

        // Lock arrays A and B to record the changed row
        sem_wait(&SemArray);
        for (int index = 0; index < 1000; index++) {
            if (A[index] == 0) {
                A[index] = i;
                B[index] = UNPROCESSED;
                break;
            }
        }
        sem_post(&SemArray);
        sem_post(&SemChoas);

        sleep(2);
    }


    printf("CHAOS PROCESS ENDS (PID: %d)\n", getpid());

    sem_wait(&SemActiveChaos);
    (*ActiveChaosCount)--;
    sem_post(&SemActiveChaos);
    exit(0);
}

void Order(struct SharedResources *details) {

    printf("I am order (PID: %d)\n", getpid());

    int **matrix = details->Matrix;
    int *A = details->A;
    int *B = details->B;
    int Rows = details->Rows;
    int Cols = details->Cols;

    while (*updatesProcessedByOrder < 30 || *ActiveChaosCount > 0) {
        int rowToProcess = -1;

        // Check the shared arrays A and B for unprocessed Rows
        sem_wait(&SemOrder);
        sem_wait(&SemArray);
        for (int index = 0; index < 1000; index++) {
            
            if (B[index] == UNPROCESSED) {
                rowToProcess = A[index];
                B[index] = PROCESSED;

                printf("Order: Detected updated element at row %d\n", rowToProcess);
                break;
            }
        }
        sem_post(&SemArray);
        sem_post(&SemOrder);

        if (rowToProcess != -1) {
            // Lock the matrix row, sort that row and unlock
            sem_wait(&SemMatrix);
            printf("Older row %d: ", rowToProcess);
            for (int j = 0; j < Cols; j++) {
                printf("%d ", matrix[rowToProcess][j]);
            }
            printf("\n");
            

            // Simple bubble sort for sorting the row
            for (int j = 0; j < Cols - 1; j++) {
                for (int k = j + 1; k < Cols; k++) {
                    if (matrix[rowToProcess][j] > matrix[rowToProcess][k]) {
                        int temp = matrix[rowToProcess][j];
                        matrix[rowToProcess][j] = matrix[rowToProcess][k];
                        matrix[rowToProcess][k] = temp;
                    }
                }
            }

            printf("New row %d: ", rowToProcess);
            for (int j = 0; j < Cols; j++) {
                printf("%d ", matrix[rowToProcess][j]);
            }
            printf("\n");

          
            sem_post(&SemMatrix);

            // Update shared variable for processed updates
            (*updatesProcessedByOrder)++;
        }
    }

    printf("ORDER PROCESS ENDS (PID: %d)\n", getpid());
    exit(0);
}

void Print(int **matrix, int Rows, int Cols) {

    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            printf("%d\t", matrix[i][j]);
        }

        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    
    int NumberOfProcess = 9;

    if (argc < 3) {
        printf("Usage: %s <Rows> <Cols>\n", argv[0]);
        exit(1);
    }

    int Rows = atoi(argv[1]);
    int Cols = atoi(argv[2]);

    // Creating shared memory for matrix M and arrays A and B
    shmMatrixId = shmget(IPC_PRIVATE, sizeof(int *) * Rows + sizeof(int) * Rows * Cols, IPC_CREAT | 0666);
    shmAId = shmget(IPC_PRIVATE, sizeof(int) * 1000, IPC_CREAT | 0666); 
    shmBId = shmget(IPC_PRIVATE, sizeof(int) * 1000, IPC_CREAT | 0666);  
    shmUpdatesId = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);  
    shmActiveChaosId = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);

    if (shmMatrixId < 0 || shmAId < 0 || shmBId < 0 || shmUpdatesId < 0) {
        perror("Shared memory creation failed");
        exit(1);
    }

    //Attach Shared Memory with the process
    int **matrix = (int **)shmat(shmMatrixId, NULL, 0);
    int *A = (int *)shmat(shmAId, NULL, 0); 
    int *B = (int *)shmat(shmBId, NULL, 0);  
    updatesProcessedByOrder = (int *)shmat(shmUpdatesId, NULL, 0); 
    ActiveChaosCount = (int *)shmat(shmActiveChaosId, NULL, 0); 

    // Initialize shared arrays A and B
    memset(A, 0, sizeof(int) * 1000);
    memset(B, 0, sizeof(int) * 1000);
    *updatesProcessedByOrder = 0; 
    *ActiveChaosCount = 0; 

    // Initialize semaphores
    sem_init(&SemMatrix, 1, 1);
    sem_init(&SemArray, 1, 1);
    sem_init(&SemChoas , 3,3);
    sem_init(&SemOrder , 5,5);
    sem_init(&SemActiveChaos, 1,1);

    // Initialize the matrix with random values
    for (int i = 0; i < Rows; i++) {

        matrix[i] = (int *)(matrix + Rows) + i * Cols;
        for (int j = 0; j < Cols; j++) {
            matrix[i][j] = (rand() % 1000) + 1;
        }
    }

    printf("Random Matrix M of size (%d, %d) is created.\n", Rows, Cols);
    Print(matrix, Rows, Cols);

 
    printf("Shared Arrays A and B are created separately.\n");
    struct SharedResources details = {matrix, Rows, Cols, A, B};
 
    //Creating the Order and Choas process
    pid_t pid;
   
    for (int i = 0; i < 3; i++) {

        pid = fork();
        //Child Process
        if (pid == 0) {
            Chaos(&details);
        }
    }

    for (int i = 0; i < 6; i++) {
        pid = fork();
        //Child Process
        if (pid == 0) {

            Order(&details);
        }
    }

    // Wait for all child processes to finish
    for (int i = 0; i < NumberOfProcess; i++) {
        wait(NULL);
    }
    Print(matrix, Rows, Cols);

 
    shmdt(A);
    shmdt(B);
    shmdt(matrix);
    shmctl(shmAId, IPC_RMID, NULL);
    shmctl(shmBId, IPC_RMID, NULL);
    shmdt(updatesProcessedByOrder);
    shmctl(shmMatrixId, IPC_RMID, NULL);
    shmctl(shmUpdatesId, IPC_RMID, NULL);
    sem_destroy(&SemMatrix);
    sem_destroy(&SemArray);
   
    
    return 0;
}
