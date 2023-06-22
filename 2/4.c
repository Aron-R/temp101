#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to compute Fibonacci sequence
int fibonacci(int n) {
    if (n <= 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    pid_t pid;
    int n = 10;  // Fibonacci sequence length

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        // Error occurred while forking
        fprintf(stderr, "Fork failed.\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process: PID = %d\n", getpid());

        // Compute Fibonacci sequence in the child process
        printf("Child process: Fibonacci sequence up to %d:\n", n);
        for (int i = 0; i < n; i++) {
            int fib = fibonacci(i);
            printf("%d ", fib);
        }
        printf("\n");

        return 0;
    } else {
        // Parent process
        printf("Parent process: PID = %d\n", getpid());
        wait(NULL);  // Wait for the child process to complete

        printf("Parent process: Child process completed.\n");
    }

    return 0;
}

