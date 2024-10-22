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

// Global Variables for Shared Resources
int **Matrix;
int Rows, Cols;
int *A;
int *B;
int *updatesProcessedByOrder;
int *ActiveChaosCount; 

// Shared Memory Identifiers
int shmMatrixId; 
int shmAId, shmBId;
int shmUpdatesId, shmActiveChaosId;

sem_t SemArray, SemMatrix;
sem_t SemChaos, SemOrder;
sem_t SemActiveChaos;


void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;


    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));


    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

   
    i = 0; 
    j = 0; 
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}


void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

      
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

     
        merge(arr, left, mid, right);
    }
}

void Chaos() {
    printf("I am chaos (PID: %d)\n", getpid());
    sem_wait(&SemActiveChaos);
    (*ActiveChaosCount)++;
    sem_post(&SemActiveChaos);

    for (int updates = 0; updates < 30; updates++) {
        int i = rand() % Rows;
        int j = rand() % Cols;
        int k = (rand() % 1000) + 1;

        // Lock matrix to update a random element
        sem_wait(&SemChaos);
        sem_wait(&SemMatrix);
        Matrix[i][j] = k;
        printf("Chaos: Updated element at cell %d x %d with value %d\n", i, j, k);
        sem_post(&SemMatrix);


        sem_wait(&SemArray);
        for (int index = 0; index < 1000; index++) {
            if (A[index] == 0) {
                A[index] = i;
                B[index] = UNPROCESSED;
                break;
            }
        }
        sem_post(&SemArray);
        sem_post(&SemChaos);

        sleep(2);
    }

    printf("CHAOS PROCESS ENDS (PID: %d)\n", getpid());
    sem_wait(&SemActiveChaos);
    (*ActiveChaosCount)--;
    sem_post(&SemActiveChaos);
    exit(0);
}

void Order() {
    printf("I am order (PID: %d)\n", getpid());

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
                printf("%d ", Matrix[rowToProcess][j]);
            }
            printf("\n");

            // Sort the row using Merge Sort
            mergeSort(Matrix[rowToProcess], 0, Cols - 1);

            printf("New row %d: ", rowToProcess);
            for (int j = 0; j < Cols; j++) {
                printf("%d ", Matrix[rowToProcess][j]);
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

void PrintMatrix() {
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            printf("%d\t", Matrix[i][j]);
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

    Rows = atoi(argv[1]);
    Cols = atoi(argv[2]);

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

    // Attach Shared Memory with the process
    Matrix = (int **)shmat(shmMatrixId, NULL, 0);
    A = (int *)shmat(shmAId, NULL, 0); 
    B = (int *)shmat(shmBId, NULL, 0);  
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
    sem_init(&SemChaos, 3, 3);
    sem_init(&SemOrder, 5, 5);
    sem_init(&SemActiveChaos, 1, 1);

    // Initialize the matrix with random values
    for (int i = 0; i < Rows; i++) {
        Matrix[i] = (int *)(Matrix + Rows) + i * Cols;
        for (int j = 0; j < Cols; j++) {
            Matrix[i][j] = (rand() % 1000) + 1;
        }
    }

    printf("Random Matrix M of size (%d, %d) is created.\n", Rows, Cols);
    PrintMatrix();

    // Creating Processes
    for (int i = 0; i < 2; i++) {
        if (fork() == 0) {
            Chaos();
        }
    }

    for (int i = 0; i < NumberOfProcess; i++) {
        if (fork() == 0) {
            Order();
        }
    }

    // Waiting for child processes to complete
    while (wait(NULL) > 0);

      PrintMatrix();

  
    shmdt(Matrix);
    shmdt(A);
    shmdt(B);
    shmdt(updatesProcessedByOrder);
    shmdt(ActiveChaosCount);
    shmctl(shmMatrixId, IPC_RMID, NULL);
    shmctl(shmAId, IPC_RMID, NULL);
    shmctl(shmBId, IPC_RMID, NULL);
    shmctl(shmUpdatesId, IPC_RMID, NULL);
    shmctl(shmActiveChaosId, IPC_RMID, NULL);

    return 0;
}
