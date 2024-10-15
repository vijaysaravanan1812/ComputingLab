#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/* Shared resource */
int counter = 0;

/* Mutex for synchronizing access to the counter */
pthread_mutex_t lock;

/* Thread function to increment the counter */
void* increment_counter(void* arg)
{
    int i;
    for (i = 0; i < 1000000; i++) {
        /* Lock the mutex before accessing the shared resource */
        pthread_mutex_lock(&lock);

        /* Critical section: increment the counter */
        counter++;

        /* Unlock the mutex after accessing the shared resource */
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int main()
{
    /* Initialize the mutex */
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex initialization failed\n");
        return 1;
    }

    /* Create two threads */
    pthread_t t1, t2;

    pthread_create(&t1, NULL, increment_counter, NULL);
    pthread_create(&t2, NULL, increment_counter, NULL);

    /* Wait for both threads to finish */
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    /* Destroy the mutex */
    pthread_mutex_destroy(&lock);

    /* Print the final value of counter */
    printf("Final counter value: %d\n", counter);

    return 0;
}
