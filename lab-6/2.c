#include <stdio.h>
#include <stdlib.h>

#define XEROX_TIME 0.78

typedef struct {
    char id[3];
    int arrival_time;
    int copies;
    double wait_time;
} Person;

void bubbleSort(Person arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].arrival_time > arr[j + 1].arrival_time) {
                // Swap persons
                Person temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int num_persons;
    printf("Enter the number of persons: ");
    scanf("%d", &num_persons);

    Person* persons = malloc(num_persons * sizeof(Person));

    printf("Enter the arrival time and number of copies for each person:\n");
    for (int i = 0; i < num_persons; i++) {
        printf("Person S%d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &persons[i].arrival_time);
        printf("Number of Copies: ");
        scanf("%d", &persons[i].copies);
        sprintf(persons[i].id, "S%d", i + 1);
        persons[i].wait_time = 0.0;
    }

    // Sort the persons based on arrival time
    bubbleSort(persons, num_persons);

    // Calculate waiting time
    double cumulative_time = 0.0;
    for (int i = 0; i < num_persons; i++) {
        if (persons[i].arrival_time > cumulative_time) {
            cumulative_time = persons[i].arrival_time;
        }
        persons[i].wait_time = cumulative_time - persons[i].arrival_time;
        cumulative_time += persons[i].copies * XEROX_TIME;
    }

    // Print the waiting time table
    printf("\nWaiting Time Table:\n");
    printf("+----+-------------+---------+-------+\n");
    printf("| ID | Arrival Time | Copies  | Wait  |\n");
    printf("+----+-------------+---------+-------+\n");

    double total_waiting_time = 0.0;

    for (int i = 0; i < num_persons; i++) {
        printf("| %s |      %2d       |   %2d    | %.2f |\n", persons[i].id, persons[i].arrival_time, persons[i].copies, persons[i].wait_time);
        total_waiting_time += persons[i].wait_time;
    }

    printf("+----+-------------+---------+-------+\n");

    // Calculate and print average waiting time
    double average_waiting_time = total_waiting_time / num_persons;
    printf("\nAverage waiting time: %.2f\n", average_waiting_time);

    // Free allocated memory
    free(persons);

    return 0;
}

