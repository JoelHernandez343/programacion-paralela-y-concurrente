/**
 * Joel Hernández @ 2020
 * Github JoelHernandez343
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "defs.h"
#include "helper.h"

pthread_t threads[THREADS];
int arguments[THREADS];

pthread_mutex_t block;

int *A;
int average = 0;

// void multiply_by_blocks(int thread){
//     int block = N / THREADS;
//     int begin = thread * block;
//     int end = begin + block;

//     for (int i = begin; i < end; ++i){
//         C[i] = A[i] * B[i];
//     }
// }

void alternate_multiplication(int thread){
    int avg = 0;
    for (int i = thread; i < N; i += THREADS){
        avg += A[i];
    }

    pthread_mutex_lock(&block);
    average += avg;
    pthread_mutex_unlock(&block);
}

void *child_process(void *args){
    int thread = ((int *)args)[0];

    alternate_multiplication(thread);

    return NULL;
}

int main(){

    printf("%d", N);

    A = memory_allocation();
    fill_array(A);
    printf("A:");
    show_array(A);

    pthread_mutex_init(&block, NULL);
    
    for (int i = 0; i < THREADS; ++i){
        arguments[i] = i;
        pthread_create(&(threads[i]), NULL, child_process, &(arguments[i]));
    }

    for (int i = 0; i < THREADS; ++i){
        pthread_join(threads[i], NULL);
    }

    printf("The average is: %d\n", average >> 4);

    pthread_mutex_destroy(&block);

    free(A);

    return 0;
}