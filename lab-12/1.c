#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_rwlock_t rwlock;
int sharedData = 0;

void *reader(void *param)
{
    pthread_rwlock_rdlock(&rwlock);

    // Reading the shared data
    printf("Reader %ld reads shared data: %d\n", (long)param, sharedData);

    pthread_rwlock_unlock(&rwlock);

    return NULL;
}

void *writer(void *param)
{
    printf("Writer %ld is trying to enter\n", (long)param);
    pthread_rwlock_wrlock(&rwlock);

    // Writing to the shared data
    sharedData++;
    printf("Writer %ld writes shared data: %d\n", (long)param, sharedData);

    pthread_rwlock_unlock(&rwlock);

    return NULL;
}

int main()
{
    int nReaders, nWriters;
    printf("Enter the number of readers: ");
    scanf("%d", &nReaders);
    printf("Enter the number of writers: ");
    scanf("%d", &nWriters);

    pthread_t readerThreads[nReaders];
    pthread_t writerThreads[nWriters];

    pthread_rwlock_init(&rwlock, NULL);

    // Create reader threads
    for (long i = 0; i < nReaders; i++)
        pthread_create(&readerThreads[i], NULL, reader, (void *)i);

    // Create writer threads
    for (long i = 0; i < nWriters; i++)
        pthread_create(&writerThreads[i], NULL, writer, (void *)i);

    // Wait for reader threads to finish
    for (int i = 0; i < nReaders; i++)
        pthread_join(readerThreads[i], NULL);

    // Wait for writer threads to finish
    for (int i = 0; i < nWriters; i++)
        pthread_join(writerThreads[i], NULL);

    pthread_rwlock_destroy(&rwlock);

    return 0;
}

