/**
 * Joel Hernández @ 2020
 * Github JoelHernandez343
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "defs.h"
#include "processing.h"

extern float *data;
extern float *hann_data;
extern float *windowed_data;
extern float *rxx;


void *thread_calculate_windowed_data(void *args){
    int thread = ((int *)args)[0];

    multiply_alternately(data, hann_data, windowed_data, thread, THREADS);

    return NULL;
}

void *thread_calculate_rxx(void *args){
    int thread = ((int *)args)[0];

    autocorrelation_alternately(windowed_data, rxx, thread, THREADS);

    return NULL;
}

void execute_threads(void *(child_function)(void *args)){
    pthread_t threads[THREADS];
    int arguments[THREADS];
    register int i;

    for (i = 0; i < THREADS; ++i){
        arguments[i] = i;
        pthread_create(&(threads[i]), NULL, child_function, &(arguments[i]));
    }

    for (i = 0; i < THREADS; ++i){
        pthread_join(threads[i], NULL);
        printf(DONE_OUT" Thread w/ tid %lu finished.\n", threads[i]);
    }
}

void thread_parent_process(){
    execute_threads(thread_calculate_windowed_data);
    execute_threads(thread_calculate_rxx);
}
