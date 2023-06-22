#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t parent_pid, child1_pid, child2_pid;

    // Get the parent process ID
    parent_pid = getpid();

    // Fork the first child process
    child1_pid = fork();

    if (child1_pid < 0) {
        // Error occurred while forking
        fprintf(stderr, "Fork failed.\n");
        return 1;
    } else if (child1_pid == 0) {
        // First child process
        printf("Child 1 process: PID = %d, Parent PID = %d\n", getpid(), parent_pid);
        return 0;
    } else {
        // Parent process

        // Fork the second child process
        child2_pid = fork();

        if (child2_pid < 0) {
            // Error occurred while forking
            fprintf(stderr, "Fork failed.\n");
            return 1;
        } else if (child2_pid == 0) {
            // Second child process
            printf("Child 2 process: PID = %d, Parent PID = %d\n", getpid(), parent_pid);
            return -2;
        }

        wait(NULL);  // Wait for both child processes to complete

        printf("Parent process: Child processes completed.\n");
    }

    return 0;
}

