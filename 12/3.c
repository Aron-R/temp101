#include <stdio.h>
#include <pthread.h>

#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2

typedef struct {
    int state[N];
    pthread_mutex_t mutex;
    pthread_cond_t self[N];
} Monitor;

Monitor monitor;

void pickup(int phil_num)
{
    pthread_mutex_lock(&monitor.mutex);

    monitor.state[phil_num] = HUNGRY;

    while (monitor.state[(phil_num + N - 1) % N] == EATING || monitor.state[(phil_num + 1) % N] == EATING)
        pthread_cond_wait(&monitor.self[phil_num], &monitor.mutex);

    monitor.state[phil_num] = EATING;

    pthread_mutex_unlock(&monitor.mutex);
}

void putdown(int phil_num)
{
    pthread_mutex_lock(&monitor.mutex);

    monitor.state[phil_num] = THINKING;

    if (monitor.state[(phil_num + N - 1) % N] == HUNGRY)
        pthread_cond_signal(&monitor.self[(phil_num + N - 1) % N]);

    if (monitor.state[(phil_num + 1) % N] == HUNGRY)
        pthread_cond_signal(&monitor.self[(phil_num + 1) % N]);

    pthread_mutex_unlock(&monitor.mutex);
}

void* philosopher(void* arg)
{
    int phil_num = *((int*)arg);
    int i;

    for (i = 0; i < 3; i++)
    {
        printf("Philosopher %d is thinking\n", phil_num);

        sleep(rand() % 3);

        pickup(phil_num);

        printf("Philosopher %d is eating\n", phil_num);

        sleep(rand() % 3);

        putdown(phil_num);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t tid[N];
    int i, phil_num[N];

    pthread_mutex_init(&monitor.mutex, NULL);
    for (i = 0; i < N; i++)
    {
        pthread_cond_init(&monitor.self[i], NULL);
        phil_num[i] = i;
        monitor.state[i] = THINKING;
    }

    for (i = 0; i < N; i++)
        pthread_create(&tid[i], NULL, philosopher, &phil_num[i]);

    for (i = 0; i < N; i++)
        pthread_join(tid[i], NULL);

    pthread_mutex_destroy(&monitor.mutex);
    for (i = 0; i < N; i++)
        pthread_cond_destroy(&monitor.self[i]);

    return 0;
}

