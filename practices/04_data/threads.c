/**
 * Joel Hernández @ 2020
 * Github JoelHernandez343
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "defs.h"

extern float *data;
extern float *hann_data;
extern float *result;

void *thread_child_process(void *args){
    int thread = ((int *)args)[0];
    register int i;

    for (i = thread; i < N; i += THREADS){
        result[i] = data[i] * hann_data[i];
    }

    return NULL;
}

void thread_parent_process(){
    pthread_t threads[THREADS];
    int arguments[THREADS];
    register int i;

    for (i = 0; i < THREADS; ++i){
        arguments[i] = i;
        pthread_create(&(threads[i]), NULL, thread_child_process, &(arguments[i]));
    }

    for (i = 0; i < THREADS; ++i){
        pthread_join(threads[i], NULL);
        printf(DONE_OUT" Thread w/ tid %lu finished.\n", threads[i]);
    }
}
