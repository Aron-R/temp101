#include<stdio.h>

#define MAX_PARTITIONS 5

void firstFit(int processSizes[], int numProcesses, int partitionSizes[], int numPartitions) {
    int i, j, allocated[MAX_PARTITIONS] = {0};

    for (i = 0; i < numProcesses; i++) {
        for (j = 0; j < numPartitions; j++) {
            if (partitionSizes[j] >= processSizes[i] && !allocated[j]) {
                allocated[j] = 1;
                printf("Process %d allocated to Partition %d\n", i+1, j+1);
                break;
            }
        }
        if (j == numPartitions) {
            printf("Process %d cannot be allocated\n", i+1);
        }
    }
}

void bestFit(int processSizes[], int numProcesses, int partitionSizes[], int numPartitions) {
    int i, j, bestFitIdx;
    int allocated[MAX_PARTITIONS] = {0};

    for (i = 0; i < numProcesses; i++) {
        bestFitIdx = -1;
        for (j = 0; j < numPartitions; j++) {
            if (partitionSizes[j] >= processSizes[i] && !allocated[j]) {
                if (bestFitIdx == -1 || partitionSizes[j] < partitionSizes[bestFitIdx]) {
                    bestFitIdx = j;
                }
            }
        }

        if (bestFitIdx != -1) {
            allocated[bestFitIdx] = 1;
            printf("Process %d allocated to Partition %d\n", i+1, bestFitIdx+1);
        } else {
            printf("Process %d cannot be allocated\n", i+1);
        }
    }
}

void worstFit(int processSizes[], int numProcesses, int partitionSizes[], int numPartitions) {
    int i, j, worstFitIdx;
    int allocated[MAX_PARTITIONS] = {0};

    for (i = 0; i < numProcesses; i++) {
        worstFitIdx = -1;
        for (j = 0; j < numPartitions; j++) {
            if (partitionSizes[j] >= processSizes[i] && !allocated[j]) {
                if (worstFitIdx == -1 || partitionSizes[j] > partitionSizes[worstFitIdx]) {
                    worstFitIdx = j;
                }
            }
        }

        if (worstFitIdx != -1) {
            allocated[worstFitIdx] = 1;
            printf("Process %d allocated to Partition %d\n", i+1, worstFitIdx+1);
        } else {
            printf("Process %d cannot be allocated\n", i+1);
        }
    }
}

int main() {
    int processSizes[] = {212, 417, 112, 426};
    int partitionSizes[] = {100, 500, 200, 300, 600};
    int numProcesses = sizeof(processSizes) / sizeof(processSizes[0]);
    int numPartitions = sizeof(partitionSizes) / sizeof(partitionSizes[0]);

    printf("First-fit Allocation:\n");
    firstFit(processSizes, numProcesses, partitionSizes, numPartitions);

    printf("\nBest-fit Allocation:\n");
    bestFit(processSizes, numProcesses, partitionSizes, numPartitions);

    printf("\nWorst-fit Allocation:\n");
    worstFit(processSizes, numProcesses, partitionSizes, numPartitions);

    return 0;
}

