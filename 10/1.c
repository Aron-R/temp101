#include <stdio.h>
#include <stdlib.h>

int safety(int alloc[5][4], int max[5][4], int avail[4], int need[5][4], int n, int m,int safeSeq[]);
int res_req(int alloc[][10], int max[][10], int avail[], int need[][10], int n, int m);

int main() {
    int n, m;
    printf("Enter the number of processes: \n");
    scanf("%d", &n);

    printf("\nEnter the number of resources: \n");
    scanf("%d", &m);

    int alloc[n][m], max[n][m];
    printf("\nAllocation table: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nMax table: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nAvailable table: \n");
    int avail[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    printf("\nCalculated Need table: \n");
    int need[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }

    int safeSequence[n];  // Array to store the safety sequence

    if (safety(alloc, max, avail, need, n, m, safeSequence)) {
        printf("\nSafe State\n");
        printf("Safety Sequence: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", safeSequence[i]);
        }
        printf("\n");
        int option=0;
        printf("To make an additional request press 1, else enter 0: ");
        scanf("%d",&option);
        if(option==1)
            res_req(alloc, max, avail, need, n, m);
    } else {
        printf("\nUnsafe State\n");
    }

    return 0;
}

int safety(int alloc[5][4], int max[5][4], int avail[4], int need[5][4], int n, int m, int safeSeq[]) {
    int finish[n], work[m], count = 0;

    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == m) {
                    for (int k = 0; k < m; k++) {
                        work[k] += alloc[i][k];
                    }

                    safeSeq[count++] = i;  // Add process to the safety sequence
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0) {
            return 0;
        }
    }

    return 1;
}

int res_req(int alloc[][10], int max[][10], int avail[], int need[][10], int n, int m) {
    int req[n][m];

    while (1) {
        int p;
        printf("\nEnter the process number for additional request:");
        scanf("%d", &p);
        int is_valid = 0;
        for (int i = 0; i < m; i++) {
            printf("\nEnter the request for resource %d:", i);
            scanf("%d", &req[p][i]);
            printf("\nNeeded resource is %d and Available resource is %d\n", need[p][i], avail[i]);
            if (req[p][i] <= need[p][i] && req[p][i] <= avail[i]) {
                is_valid = 1;
            } else {
                is_valid = 0;
            }
        }

        if (is_valid == 0) {
            printf("\nRequest cannot be fulfilled.\n");
            continue;
        }

        for (int i = 0; i < m; i++) {
            avail[i] -= req[p][i];
            alloc[p][i] += req[p][i];
            need[p][i] -= req[p][i];
        }

        int safeSequence[n];
        if (safety(alloc, max, avail, need, n, m, safeSequence)) {
            printf("\nRequest can be fulfilled.\n");
            printf("Safety Sequence: ");
            for (int i = 0; i < n; i++) {
                printf("%d ", safeSequence[i]);
            }
            printf("\n");
            break;
        } else {
            printf("\nRequest cannot be fulfilled. Releasing resources.\n");
            for (int i = 0; i < m; i++) {
                avail[i] += req[p][i];
                alloc[p][i] -= req[p][i];
                need[p][i] += req[p][i];
            }
        }
    }
    return 0;
}
