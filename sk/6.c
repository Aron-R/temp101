#include<stdio.h>
#include<limits.h>
  
void findWaitingTime(int processes[], int n, int bt[], int priority[], int wt[])
{
    int rt[n];
  
    for (int i = 0; i < n; i++)
        rt[i] = bt[i];
  
    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    int check = 0;
  
    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if ((processes[j] <= t) && (priority[j] < minm) && rt[j] > 0) {
                minm = priority[j];
                shortest = j;
                check = 1;
            }
        }
  
        if (check == 0) {
            t++;
            continue;
        }
  
        rt[shortest]--;
  
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;
  
        if (rt[shortest] == 0) {
  
            complete++;
            finish_time = t + 1;
  
            wt[shortest] = finish_time - bt[shortest] - processes[shortest];
  
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }
}
# prioriy preempt  
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[])
{
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}
  
void findAverageTime(int processes[], int n, int bt[], int priority[])
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
  
    findWaitingTime(processes, n, bt, priority, wt);
  
    findTurnAroundTime(processes, n, bt, wt, tat);
  
    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
  
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], priority[i], wt[i], tat[i]);
    }
  
    printf("\nAverage waiting time: %.2f", (float)total_wt / n);
    printf("\nAverage turnaround time: %.2f", (float)total_tat / n);
}
  
int main()
{
    int processes[] = {1, 2, 3};
    int n = sizeof processes / sizeof processes[0];
  
    int burst_time[] = {6, 8, 7};
    int priority[] = {2, 1, 3};
  
    findAverageTime(processes, n, burst_time, priority);
  
    return 0;
}
