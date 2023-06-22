#include <stdio.h>
#include <limits.h>

void findWaitingTime(int n, int bt[], int wt[])
{
    int rt[n];
    for (int i = 0; i < n; i++)
        rt[i] = bt[i];

    int complete = 0, t = 0, minm = INT_MAX, shortest = 0, finish_time;

    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if (rt[j] <= minm && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
            }
        }

        rt[shortest] = 0;
        minm = INT_MAX;
        finish_time = t + 1;
        wt[shortest] = finish_time - bt[shortest];
        
        if (wt[shortest] < 0)
            wt[shortest] = 0;
        
        t += bt[shortest];
        complete++;
    }
}

void findTurnAroundTime(int n, int bt[], int wt[], int tat[])
{
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}
# sjf non-prempt
void findAvgTime(int n, int bt[])
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    findWaitingTime(n, bt, wt);

    findTurnAroundTime(n, bt, wt, tat);

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage waiting time: %.2f", (float)total_wt / n);
    printf("\nAverage turnaround time: %.2f", (float)total_tat / n);
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst_time[n];
    printf("Enter burst time for each process:\n");

    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    findAvgTime(n, burst_time);

   return 0;
}
