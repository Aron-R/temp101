#include <stdio.h>

void findWaitingTime(int n, int bt[], int wt[], int quantum)
{
    int remaining_bt[n];
    for (int i = 0; i < n; i++)
        remaining_bt[i] = bt[i];

    int t = 0;
    while (1) {
        int done = 1;

        for (int i = 0; i < n; i++) {
            if (remaining_bt[i] > 0) {
                done = 0;
                if (remaining_bt[i] > quantum) {
                    t += quantum;
                    remaining_bt[i] -= quantum;
                }
                else {
                    t += remaining_bt[i];
                    wt[i] = t - bt[i];
                    remaining_bt[i] = 0;
                }
            }
        }

        if (done == 1)
            break;
    }
}

void findTurnAroundTime(int n, int bt[], int wt[], int tat[])
{
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}
# round robin same arriv
void findAvgTime(int n, int bt[], int quantum)
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    findWaitingTime(n, bt, wt, quantum);

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
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    int burst_time[n];
    printf("Enter burst time for each process:\n");

    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    findAvgTime(n, burst_time, quantum);

   return 0;
}
