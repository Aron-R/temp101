#include<stdio.h>

#define MAX_PARTITIONS 5

void firstFit(int processSizes[], int numProcesses, int partitionSizes[], int numPartitions) {
    int i, j, allocated[MAX_PARTITIONS] = {0};

    printf("Process No.\tProcess Size\tPartition No.\n");
    for (i = 0; i < numProcesses; i++) {
        for (j = 0; j < numPartitions; j++) {
            if (partitionSizes[j] >= processSizes[i] && !allocated[j]) {
                allocated[j] = 1;
                printf("%d\t\t%d\t\t%d\n", i+1, processSizes[i], j+1);
                break;
            }
        }
        if (j == numPartitions) {
            printf("%d\t\t%d\t\tNot Allocated\n", i+1, processSizes[i]);
        }
    }
}

void bestFit(int processSizes[], int numProcesses, int partitionSizes[], int numPartitions) {
    int i, j, bestFitIdx;
    int allocated[MAX_PARTITIONS] = {0};

    printf("Process No.\tProcess Size\tPartition No.\n");
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
            printf("%d\t\t%d\t\t%d\n", i+1, processSizes[i], bestFitIdx+1);
        } else {
            printf("%d\t\t%d\t\tNot Allocated\n", i+1, processSizes[i]);
        }
    }
}

void worstFit(int processSizes[], int numProcesses, int partitionSizes[], int numPartitions) {
    int i, j, worstFitIdx;
    int allocated[MAX_PARTITIONS] = {0};

    printf("Process No.\tProcess Size\tPartition No.\n");
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
            printf("%d\t\t%d\t\t%d\n", i+1, processSizes[i], worstFitIdx+1);
        } else {
            printf("%d\t\t%d\t\tNot Allocated\n", i+1, processSizes[i]);
        }
    }
}

int main() {
    int numProcesses, numPartitions; 
    
    printf("enter number of processes: ");
    scanf("%d",&numProcesses);
    
    printf("Enter number of partitions: ");
    scanf("%d",&numPartitions);
    
    int processSizes[numProcesses], partitionSizes[numPartitions];
    
    for(int i=0;i<numProcesses;i++)
    {
    	printf("Enter size of process %d: ",i+1);
    	scanf("%d",&processSizes[i]);
    }
    
    for(int i=0;i<numPartitions;i++)
    {
    	printf("Enter size of partition %d: ",i+1);
    	scanf("%d",&partitionSizes[i]);
    }

    printf("First-fit Allocation:\n");
    firstFit(processSizes, numProcesses, partitionSizes, numPartitions);

    printf("\nBest-fit Allocation:\n");
    bestFit(processSizes, numProcesses, partitionSizes, numPartitions);

    printf("\nWorst-fit Allocation:\n");
    worstFit(processSizes, numProcesses, partitionSizes, numPartitions);

    return 0;
}

