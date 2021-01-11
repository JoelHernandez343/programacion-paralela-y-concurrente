/**
 * Joel Hernández @ 2020
 * Github JoelHernandez343
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "defs.h"

extern int *A;
extern int *B;
extern int result;

pthread_mutex_t lock;

void *thread_child_process(void *args){
    int thread = ((int *)args)[0];

    int block = N / THREADS;
    int begin = thread * block;
    int end = begin + block;

    register int i;
    int parcial_sum = 0;
    
    for (i = begin; i < end; ++i){
        parcial_sum += A[i] * B[i];
    }

    pthread_mutex_lock(&lock);
    result += parcial_sum;
    pthread_mutex_unlock(&lock);

    return NULL;
}

void thread_parent_process(){
    pthread_t threads[THREADS];
    int arguments[THREADS];
    register int i;

    pthread_mutex_init(&lock, NULL);

    for (i = 0; i < THREADS; ++i){
        arguments[i] = i;
        pthread_create(&(threads[i]), NULL, thread_child_process, &(arguments[i]));
    }

    for (i = 0; i < THREADS; ++i){
        pthread_join(threads[i], NULL);
        printf(DONE_OUT" Thread w/ tid %lu finished.\n", threads[i]);
    }

    pthread_mutex_destroy(&lock);
}
