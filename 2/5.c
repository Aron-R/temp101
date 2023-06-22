#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t parent_pid, child_pid, grandchild_pid;

    // Get the parent process ID
    parent_pid = getpid();

    // Fork the child process
    child_pid = fork();

    if (child_pid < 0) {
        // Error occurred while forking
        fprintf(stderr, "Fork failed.\n");
        return 1;
    } else if (child_pid == 0) {
        // Child process
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), parent_pid);

        // Fork the grandchild process
        grandchild_pid = fork();

        if (grandchild_pid < 0) {
            // Error occurred while forking
            fprintf(stderr, "Fork failed.\n");
            return 1;
        } else if (grandchild_pid == 0) {
            // Grandchild process
            printf("Grandchild process: PID = %d, Parent PID = %d\n", getpid(), getppid());
            return 0;
        }

        wait(NULL);  // Wait for the grandchild process to complete

        return 0;
    } else {
        // Parent process
        printf("Parent process: PID = %d\n", getpid());
        wait(NULL);  // Wait for the child process to complete

        printf("Parent process: Child process completed.\n");
    }

    return 0;
}

