#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore1, semaphore2;
int counter = 0;

void *printHi(void *arg)
{
    for (int i = 0; i < 100; i++)
    {
        sem_wait(&semaphore1);
        printf("Hi ");
        fflush(stdout);
        counter++;
        sem_post(&semaphore2);
    }

    return NULL;
}

void *printHello(void *arg)
{
    for (int i = 0; i < 100; i++)
    {
        sem_wait(&semaphore2);
        printf("Hello ");
        fflush(stdout);
        counter++;
        sem_post(&semaphore1);
    }

    return NULL;
}

int main()
{
    pthread_t thread1, thread2;

    sem_init(&semaphore1, 0, 1); // Initialize semaphore1 with value 1
    sem_init(&semaphore2, 0, 0); // Initialize semaphore2 with value 0

    // Create the first thread
    if (pthread_create(&thread1, NULL, printHi, NULL) != 0)
    {
        printf("Failed to create thread1.\n");
        return 1;
    }

    // Create the second thread
    if (pthread_create(&thread2, NULL, printHello, NULL) != 0)
    {
        printf("Failed to create thread2.\n");
        return 1;
    }

    // Wait for both threads to finish
    if (pthread_join(thread1, NULL) != 0)
    {
        printf("Failed to join thread1.\n");
        return 1;
    }

    if (pthread_join(thread2, NULL) != 0)
    {
        printf("Failed to join thread2.\n");
        return 1;
    }

    sem_destroy(&semaphore1);
    sem_destroy(&semaphore2);

    printf("\nTotal prints: %d\n", counter);

    return 0;
}

