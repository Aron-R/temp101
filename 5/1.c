#include <stdio.h>
#include <pthread.h>

void *threadFunction(void *arg)
{
    pid_t pid = getpid();
    pthread_t tid = pthread_self();

    printf("Thread ID: %ld\n", (long)tid);
    printf("Process ID: %d\n", pid);

    return NULL;
}

int main()
{
    pthread_t thread;

    // Create a new thread
    if (pthread_create(&thread, NULL, threadFunction, NULL) != 0)
    {
        printf("Failed to create thread.\n");
        return 1;
    }

    // Wait for the thread to finish
    if (pthread_join(thread, NULL) != 0)
    {
        printf("Failed to join thread.\n");
        return 1;
    }

    return 0;
}

