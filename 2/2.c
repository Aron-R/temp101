#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int i;

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        // Error occurred while forking
        fprintf(stderr, "Fork failed.\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        for (i = 1; i <= 100; i++) {
            printf("Child process: PID = %d\n", getpid());
            usleep(100000);  // Sleep for 100 milliseconds
        }
    } else {
        // Parent process
        for (i = 1; i <= 100; i++) {
            printf("Parent process: PID = %d\n", getpid());
            usleep(100000);  // Sleep for 100 milliseconds
        }
    }

    return 0;
}

