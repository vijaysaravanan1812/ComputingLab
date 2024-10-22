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

sem_t a, b, c, d,e;

int *count1, *count2, shmMatrixId, shmAId, shmBId, shmUpdatesId, shmActiveChaosId;

struct MatrixDetails {
    int **Matrix, Rows, Cols, *A, *B;
};

void chaos_process(struct MatrixDetails *details) {
    int **matrix = details->Matrix;
    int *A = details->A;
    int *B = details->B;
    int rows = details->Rows;
    int cols = details->Cols;

    printf("I am chaos (PID: %d)\n", getpid());

    // Increment active chaos count
    sem_wait(&c);
    (*count2)++;
    sem_post(&c);

    for (int updates = 0; updates < 30; updates++) {
        int i = rand() % rows;
        int j = rand() % cols;
        int k = (rand() % 1000) + 1;

        // Lock matrix to update a random element
        sem_wait(&b);
        matrix[i][j] = k;
        printf("Chaos: Updated element at cell %d x %d with value %d\n", i, j, k);
        sem_post(&b);

        // Lock arrays A and B to record the changed row
        sem_wait(&a);
        for (int index = 0; index < 1000; index++) {
            if (A[index] == 0) {
                A[index] = i;
                B[index] = UNPROCESSED;
                break;
            }
        }
        sem_post(&a);

        sleep(2); // Sleep for 2 seconds between updates
    }

    // Decrement active chaos count
    sem_wait(&c);
    (*count2)--;
    sem_post(&c);

    printf("CHAOS PROCESS ENDS (PID: %d)\n", getpid());
}

void order_process(struct MatrixDetails *details) {

    int **matrix = details->Matrix;
    int *A = details->A;
    int *B = details->B;
    int rows = details->Rows;
    int cols = details->Cols;

    printf("I am order (PID: %d)\n", getpid());

    // Loop until there are no more updates to process and no active chaos processes
    while (*count1 < 30 || *count2 > 0) {
        int rowToProcess = -1;

        // Check the shared arrays A and B for unprocessed rows
        sem_wait(&a);
        sem_wait(&d);
        for (int index = 0; index < 1000; index++) {
            if (B[index] == UNPROCESSED) {
                rowToProcess = A[index];
                B[index] = PROCESSED;

                printf("Order: Detected updated element at row %d\n", rowToProcess);
                break;
            }
        }
        sem_post(&a);
        sem_post(&d);

        if (rowToProcess != -1) {
            // Lock the matrix row, sort that row and unlock
            sem_wait(&b);
            printf("Older row %d: ", rowToProcess);
            for (int j = 0; j < cols; j++) {
                printf("%d ", matrix[rowToProcess][j]);
            }
            printf("\n");

            // Simple bubble sort for sorting the row
            for (int j = 0; j < cols - 1; j++) {
                for (int k = j + 1; k < cols; k++) {
                    if (matrix[rowToProcess][j] > matrix[rowToProcess][k]) {
                        int temp = matrix[rowToProcess][j];
                        matrix[rowToProcess][j] = matrix[rowToProcess][k];
                        matrix[rowToProcess][k] = temp;
                    }
                }
            }

            printf("New row %d: ", rowToProcess);
            for (int j = 0; j < cols; j++) {
                printf("%d ", matrix[rowToProcess][j]);
            }
            printf("\n");

            sem_post(&b);

            // Update shared variable for processed updates
            (*count1)++;
        }
    }

    printf("ORDER PROCESS ENDS (PID: %d)\n", getpid());
}

void print_matrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <Rows> <Cols>\n", argv[0]);
        exit(1);
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    // Creating shared memory for matrix M and arrays A and B
    shmMatrixId = shmget(IPC_PRIVATE, sizeof(int *) * rows + sizeof(int) * rows * cols, IPC_CREAT | 0666);
    shmAId = shmget(IPC_PRIVATE, sizeof(int) * 1000, IPC_CREAT | 0666);  // Separate shared memory for A
    shmBId = shmget(IPC_PRIVATE, sizeof(int) * 1000, IPC_CREAT | 0666);  // Separate shared memory for B
    shmUpdatesId = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);  // Shared memory for updatesProcessed
    shmActiveChaosId = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666); // Shared memory for activeChaosCount

    if (shmMatrixId < 0 || shmAId < 0 || shmBId < 0 || shmUpdatesId < 0 || shmActiveChaosId < 0) {
        perror("Shared memory creation failed");
        exit(1);
    }

    int **matrix = (int *)shmat(shmMatrixId, NULL, 0);
    int *A = (int *)shmat(shmAId, NULL, 0);  // Attach shared memory for A
    int *B = (int *)shmat(shmBId, NULL, 0);  // Attach shared memory for B
    count1 = (int *)shmat(shmUpdatesId, NULL, 0);  // Attach shared memory for updatesProcessed
    count2 = (int *)shmat(shmActiveChaosId, NULL, 0); // Attach shared memory for activeChaosCount

    // Initialize the matrix with random values
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)(matrix + rows) + i * cols;
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (rand() % 1000) + 1;
        }
    }

    printf("Random Matrix M of size (%d, %d) is created.\n", rows, cols);
    print_matrix(matrix, rows, cols);

    memset(A, 0, sizeof(int) * 1000);
    memset(B, 0, sizeof(int) * 1000);
    *count1 = 0; 
    *count2 = 0;
    printf("Shared Arrays A and B are created separately.\n");
    struct MatrixDetails details = { matrix, rows, cols, A, B};
    

    sem_init(&b, 1, 1);
    sem_init(&a, 1, 1);
    sem_init(&c, 3, 3);
    sem_init(&d, 5, 5);
    sem_init(&e, 1, 1);

    pid_t pid;

    for(int i=0;i<3;i++){
            pid = fork();
            if (pid == 0) {

                chaos_process(&details);

            }   
    }
    for(int i=0;i<6;i++){
        pid = fork();
            if (pid == 0) {
            order_process(&details);
            exit(0);
         }  
    }

    for(int i=0;i<9;i++){
         wait(NULL);
    }

    printf("Final Matrix M after processing:\n");
    print_matrix(matrix, rows, cols);


    shmdt(matrix);
    shmdt(A);
    shmdt(B);

    shmdt(count1);
    shmdt(count2);

    shmctl(shmMatrixId, IPC_RMID, NULL);
    shmctl(shmAId, IPC_RMID, NULL);
    shmctl(shmBId, IPC_RMID, NULL);
    shmctl(shmUpdatesId, IPC_RMID, NULL);
    shmctl(shmActiveChaosId, IPC_RMID, NULL);

    sem_destroy(&b);
    sem_destroy(&a);
    sem_destroy(&c);

    printf("This is the end \n");

    return 0;
}