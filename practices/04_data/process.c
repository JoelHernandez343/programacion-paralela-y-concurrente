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

extern float *data;
extern float *hann_data;
extern float *result;

void proc_child_process(int process, int pipe[]){
    int block = N / THREADS;
    int begin = process * block;
    int end = begin + block;

    close(pipe[0]);

    register int i;

    for (i = begin; i < end; ++i){
        result[i] = data[i] * hann_data[i];
    }

    write(pipe[1], result + begin, sizeof(float) * block);
    close(pipe[1]);

    free(data);
    free(hann_data);
    free(result);

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

    int block = N / PROCESS, process, begin;

    for (i = 0; i < PROCESS; ++i){
        wait(&process);
        process >>= 8;

        close(pipes[process][1]);
        begin = process * block;
        read(pipes[process][0], result + begin, sizeof(float) * block);
        close(pipes[process][0]);

        printf(DONE_OUT" Process %d finished.\n", process);
    }
}