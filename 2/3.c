#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        // Error occurred while forking
        fprintf(stderr, "Fork failed.\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process: PID = %d\n", getpid());
        execl("/path/to/child_executable", "child_executable", NULL);

        // If execl fails, an error occurred
        fprintf(stderr, "Child process: Failed to execute child_executable.\n");
        return 1;
    } else {
        // Parent process
        printf("Parent process: PID = %d\n", getpid());
        wait(NULL);  // Wait for the child process to complete

        printf("Parent process: Child process completed.\n");
    }

    return 0;
}

