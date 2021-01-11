#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "defs.h"
#include "helper.h"

int *A, *B, *C;

void child_process(int np, int pipe[]);
void parent_process(int pipes[][2]);

int main(){
    A = memory_allocation();
    B = memory_allocation();
    C = memory_allocation();

    fill_array(A);
    fill_array(B);

    printf("A:");
    show_array(A);

    printf("B:");
    show_array(B);

    int pipes[PROCESS][2];
    register int i;
    
    for (i = 0; i < PROCESS; ++i){
        pipe(pipes[i]);

        if (!fork()){
            child_process(i, pipes[i]);
        }
    }

    parent_process(pipes);

    free(A);
    free(B);
    free(C);
}

void child_process(int np, int pipe[]){
    int block = N / PROCESS;
    int begin = np * block;
    int end = begin + block;

    close(pipe[0]);

    for (int i = begin; i < end; ++i){
        C[i] = A[i] * B[i];
    }

    write(pipe[1], C + begin, sizeof(int) * block);
    close(pipe[1]);

    free(A);
    free(B);
    free(C);

    exit(np);
}

void parent_process(int pipes[][2]){
    register int i;
    int block = N / PROCESS, process, begin;

    for (i = 0; i < PROCESS; ++i){
        wait(&process);
        process >>= 8;

        close(pipes[process][1]);
        begin = process * block;
        read(pipes[process][0], C + begin, sizeof(int) * block);
        close(pipes[process][0]);

        printf("Process %d finished.\n", process);
    }

    printf("C:");
    show_array(C);
}
