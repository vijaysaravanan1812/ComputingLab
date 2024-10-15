#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define UNPROCESSED -1
#define PROCESSED 0

pthread_mutex_t mutexMatrix, mutexArray;
int updatesProcessed = 0;

struct MatrixDetails {
    int **Matrix;
    int Rows;
    int Cols;
    int *A;
    int *B;
};

void printMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void *Chaos(void *param) {
    
    struct MatrixDetails *details = (struct MatrixDetails *)param;
    int **matrix = details->Matrix;
    int *A = details->A;
    int *B = details->B;
    int rows = details->Rows;
    int cols = details->Cols;

    printf("I am chaos\n");

    for (int updates = 0; updates < 30; updates++) {
        int i = rand() % rows;
        int j = rand() % cols;
        int k = (rand() % 1000) + 1;

        // Lock matrix to update a random element
        pthread_mutex_lock(&mutexMatrix);
        matrix[i][j] = k;
        printf("Chaos: Updated element at cell %d x %d with value %d\n", i, j, k);
        pthread_mutex_unlock(&mutexMatrix);

   
        pthread_mutex_lock(&mutexArray);
        for (int index = 0; index < 1000; index++) {

            //Finding the Free space by Linear search
            if (A[index] == 0) {
                A[index] = i;
                B[index] = UNPROCESSED;
                break;
            }
        }
        pthread_mutex_unlock(&mutexArray);

    
        sleep(2);
    }

    printf("CHAOS THREAD ENDS\n");
    return NULL;
}

void *Order(void *param) {

    struct MatrixDetails *details = (struct MatrixDetails *)param;
    int **matrix = details->Matrix;
    int *A = details->A;
    int *B = details->B;
    int rows = details->Rows;
    int cols = details->Cols;

    printf("I am order\n");

    while (updatesProcessed < 30) {
        int rowToProcess = -1;

        // Check the shared arrays A and B for unprocessed rows
        pthread_mutex_lock(&mutexArray);
        for (int index = 0; index < 1000; index++) {
            if (B[index] == UNPROCESSED) {
                rowToProcess = A[index];
                B[index] = PROCESSED;

                printf("Order: Detected updated element at row %d\n", rowToProcess);
                break;
            }
        }
        pthread_mutex_unlock(&mutexArray);

        if (rowToProcess != -1) {

            // lock the matrix row, sort that row and unlock
            pthread_mutex_lock(&mutexMatrix);
            printf("Older row %d: ", rowToProcess);
            for (int j = 0; j < cols; j++) {
                printf("%d ", matrix[rowToProcess][j]);
            }
            printf("\n");

            
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
            pthread_mutex_unlock(&mutexMatrix);

            updatesProcessed++;
        }


    }

    printf("ORDER THREAD ENDS\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <rows> <cols>\n", argv[0]);
        return 1;
    }

  
    pthread_mutex_init(&mutexMatrix, NULL);
    pthread_mutex_init(&mutexArray, NULL);

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (rand() % 1000) + 1;
        }
    }

   
    printf("Random Matrix M of size (%d, %d) is created.\n", rows, cols);
    printMatrix(matrix, rows, cols);

   

    int A[1000] = {0};
    int B[1000] = {0};
    printf("Shared Arrays A and B are created.\n");

 
    pthread_t threads[4];
    struct MatrixDetails details = {matrix, rows, cols, A, B};

    pthread_create(&threads[0], NULL, Chaos, (void *)&details);
    pthread_create(&threads[1], NULL, Order, (void *)&details);
    pthread_create(&threads[2], NULL, Order, (void *)&details);
    pthread_create(&threads[3], NULL, Order, (void *)&details);

   

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

   
    printf("Final Matrix M after all thread operations:\n");
    printMatrix(matrix, rows, cols);

   
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    pthread_mutex_destroy(&mutexMatrix);
    pthread_mutex_destroy(&mutexArray);

    return 0;
}
