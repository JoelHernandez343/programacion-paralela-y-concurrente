/**
 * Joel Hernández @ 2020
 * Github JoelHernandez343
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "defs.h"

extern int *A;
extern int *B;
extern int result;

void proc_child_process(int process, int pipe[]){
    close(pipe[0]);

    register int i;
    for (i = process; i < N; i += PROCESS){
        result += A[i] * B[i];
    }

    write(pipe[1], &result, sizeof(int));
    close(pipe[1]);

    free(A);
    free(B);

    exit(process);
}

void proc_parent_process(){
    int pipes[PROCESS][2];
    register int i;

    for (i = 0; i < PROCESS; ++i){
        pipe(pipes[i]);

        if (!fork()){
            proc_child_process(i, pipes[i]);
        }
    }

    int parcial_sum, process;

    for (i = 0; i < PROCESS; ++i){
        wait(&process);
        process >>= 8;

        close(pipes[process][1]);

        read(pipes[process][0], &parcial_sum, sizeof(int));
        close(pipes[process][0]);

        result += parcial_sum;

        printf(DONE_OUT" Process %d finished.\n", process);
    }
}