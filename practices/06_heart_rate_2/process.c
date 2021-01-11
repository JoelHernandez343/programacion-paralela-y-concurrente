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
#include "processing.h"

extern float *data;
extern float *hann_data;
extern float *windowed_data;
extern float *rxx;

void calculate_windowed_data(int process, int pipe[]){
    int block = N / PROCESS;
    int begin = process * block;
    int end = begin + block;

    close(pipe[0]);

    multiply_by_blocks(data, hann_data, windowed_data, begin, end);

    write(pipe[1], windowed_data + begin, sizeof(float) * block);
    close(pipe[1]);

    free(data);
    free(hann_data);
    free(windowed_data);
    free(rxx);

    exit(process);
}

void calculate_rxx(int process, int pipe[]){
    int block = N / PROCESS;
    int begin = process * block;
    int end = begin + block;

    close(pipe[0]);

    autocorrelation_by_blocks(windowed_data, rxx, begin, end);

    write(pipe[1], rxx + begin, sizeof(float) * block);
    close(pipe[1]);

    free(data);
    free(hann_data);
    free(windowed_data);
    free(rxx);

    exit(process);
}

void execute_process(float *sgn,char *message, void (*child_function)(int process, int pipe[])){
    int pipes[PROCESS][2];
    register int i;

    int block = N / PROCESS, process, begin;

    printf("%s\n", message);
    for (i = 0; i < PROCESS; ++i){
        pipe(pipes[i]);

        if (!fork()){
            child_function(i, pipes[i]);
        }
    }

    for (i = 0; i < PROCESS; ++i){
        wait(&process);
        process >>= 8;

        close(pipes[process][1]);
        begin = process * block;
        read(pipes[process][0], sgn + begin, sizeof(float) * block);
        close(pipes[process][0]);

        printf(DONE_OUT" Process %d finished.\n", process);
    }
}

void proc_parent_process(){
    execute_process(windowed_data, "Calculating windowed data:", calculate_windowed_data);
    execute_process(rxx, "Calculating rxx:", calculate_rxx);
}