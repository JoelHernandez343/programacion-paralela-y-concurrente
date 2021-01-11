#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void child_process(int);

int main() {
    float num1 = 45, num2 = 12, sub;
    pid_t pid;
    int status;

    register int np = 0;

    printf("Example of process\n");

    pid = fork();
    
    if (pid == -1) {
        perror("Error creating process!\n");
        exit(EXIT_FAILURE);
    }
    if (!pid) {
        child_process(np);
    }
    else {
        printf("Parent process executing with pid %d!\n", getpid());
        sub = num1 - num2;
        printf("The substraction is: %f\n", sub);
        pid = wait(&status);

        printf("The child process terminated is: %d with status: %d\n", pid, status);
        exit(EXIT_SUCCESS);
    }
}

void child_process(int np) {
    exit(np);
}