#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

unsigned long long factorial(unsigned int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

unsigned long long fibonacci(unsigned int n) {
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    pid_t child_pid;

    printf("Parent process: Enter a number to compute its Fibonacci sequence: ");
    unsigned int num_fib;
    scanf("%u", &num_fib);

    printf("Child process: Enter a number to compute its factorial: ");
    unsigned int num_fact;
    scanf("%u", &num_fact);

    child_pid = fork();

    if (child_pid < 0) {
        // Error occurred while forking
        fprintf(stderr, "Fork failed.\n");
        return 1;
    } else if (child_pid == 0) {
        // Child process
        unsigned long long result = factorial(num_fact);
        printf("Child process: Factorial of %u = %llu\n", num_fact, result);
    } else {
        // Parent process
        printf("Parent process: Fibonacci sequence:\n");
        for (unsigned int i = 0; i <= num_fib; i++) {
            unsigned long long result = fibonacci(i);
            printf("%llu ", result);
        }
        printf("\n");

        wait(NULL); // Wait for the child process to finish
    }

    return 0;
}

