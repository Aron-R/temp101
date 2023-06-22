#include <stdio.h>
#include <pthread.h>

void *printHi(void *arg)
{
    for (int i = 0; i < 100; i++)
    {
        printf("Hi ");
        fflush(stdout);  // Flush the output to ensure it's immediately printed
    }

    return NULL;
}

void *printHello(void *arg)
{
    for (int i = 0; i < 100; i++)
    {
        printf("Hello ");
        fflush(stdout);  // Flush the output to ensure it's immediately printed
    }

    return NULL;
}

int main()
{
    pthread_t thread1, thread2;

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

    printf("\n");

    return 0;
}

