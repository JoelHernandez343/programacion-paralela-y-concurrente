#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "defs.h"
#include "helper.h"

int *A;
int average = 0;

void child_process(int np, int pipe[]);
void parent_process(int pipes[][2]);
void alternating_sum(int process);
void sum_by_block(int process);

int main(){
    A = memory_allocation();
    fill_array(A);
    printf("A:");
    show_array(A);

    int pipes[PROCESS][2];
    register int i;
    
    for (i = 0; i < PROCESS; ++i){
        pipe(pipes[i]);

        if (!fork()){
            child_process(i, pipes[i]);
        }
    }

    parent_process(pipes);

    printf("The average is: %d\n", average >> 4);

    free(A);
}

void sum_by_block(int process){
    int block = N / PROCESS;
    int begin = process * block;
    int end = begin + block;

    for (int i = begin; i < end; ++i){
        average += A[i];
    }
}

void alternating_sum(int process){
    for (int i = process; i < N; i += PROCESS){
        average += A[i];
    }
}

void child_process(int np, int pipe[]){
    close(pipe[0]);

    // sum_by_block(np);
    alternating_sum(np);

    write(pipe[1], &average, sizeof(int));
    close(pipe[1]);

    free(A);

    exit(np);
}

void parent_process(int pipes[][2]){
    register int i;
    int parcial_sum, process;

    for (i = 0; i < PROCESS; ++i){
        wait(&process);
        process >>= 8;

        close(pipes[process][1]);

        read(pipes[process][0], &parcial_sum, sizeof(int));
        close(pipes[process][0]);

        average += parcial_sum;

        printf("Process %d finished.\n", process);
    }
}
