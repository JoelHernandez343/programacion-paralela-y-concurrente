#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define PRC_NUMBER 4

void child_process(int, int []);
void parent_process(int []);

int main() {
    pid_t pid;
    register int np;
    int pipefd[2];

    printf("Example of process\n");

    pipe(pipefd);

    for (np = 0; np < PRC_NUMBER; ++np){
        pid = fork();

        if (pid == -1) {
            perror("Error creating process!\n");
            exit(EXIT_FAILURE);
        }
        if (!pid) {
            child_process(np, pipefd);
        }
    }

    parent_process(pipefd);

    return 0;
}

void child_process(int np, int pipe []) {
    int num1 = 20, num2 = 4, result;

    close(pipe[0]);

    if (np == 0){
        result = num1 + num2;
    }
    else if (np == 1){
        result= num1 - num2;
    }
    else if (np == 2){
        result = num1 * num2;
    }
    else if (np == 3){
        result = num1 / num2;
    }

    write(pipe[1], &result, sizeof(int));
    close(pipe[1]);

    exit(np);
}

void parent_process(int pipe []) {
    register int np;
    pid_t pid;
    int status, result;

    for (np = 0; np < PRC_NUMBER; ++np) {
        pid = wait(&status);
        np = status >> 8;
        read(pipe[0], &result, sizeof(int));
        printf("Process %d finished with pid: %d\n", np, pid);
        printf("The ");

    }
}