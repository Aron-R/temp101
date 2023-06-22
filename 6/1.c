#include <stdio.h>

#define XEROX_TIME 0.78

int main() {
    int num_persons;
    printf("Enter the number of persons: ");
    scanf("%d", &num_persons);

    int num_copies[num_persons];
    double wait_time[num_persons];

    printf("Enter the number of copies for each person:\n");
    for (int i = 0; i < num_persons; i++) {
        printf("Person S%d: ", i + 1);
        scanf("%d", &num_copies[i]);
    }

    printf("\nWaiting Time Table:\n");
    printf("+----+-------+-------------+---------+-------+\n");
    printf("| ID | Order | Arrival Time | Copies  | Wait  |\n");
    printf("+----+-------+-------------+---------+-------+\n");

    double total_waiting_time = 0.0;
    double cumulative_wait_time = 0.0;

    for (int i = 0; i < num_persons; i++) {
        int person = i + 1;
        double waiting_time = cumulative_wait_time + i * XEROX_TIME * num_copies[i];

        printf("| S%d |   %d   |       0       |   %2d    | %.2f |\n", person, person, num_copies[i], waiting_time);

        wait_time[i] = waiting_time;
        total_waiting_time += waiting_time;
        cumulative_wait_time += waiting_time;
    }

    printf("+----+-------+-------------+---------+-------+\n");

    double average_waiting_time = total_waiting_time / num_persons;

    printf("\nAverage waiting time: %.2f\n", average_waiting_time);

    return 0;
}

