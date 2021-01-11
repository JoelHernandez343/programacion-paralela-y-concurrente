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

int *A, *B, *C;

void multiply_by_blocks(int thread){
    int block = N / THREADS;
    int begin = thread * block;
    int end = begin + block;

    for (int i = begin; i < end; ++i){
        C[i] = A[i] * B[i];
    }
}

void alternate_multiplication(int thread){
    for (int i = thread; i < N; i += THREADS){
        C[i] = A[i] * B[i];
    }
}

void *child_process(void *args){
    int thread = ((int *)args)[0];

    alternate_multiplication(thread);
    // multiply_by_blocks(thread);

    return NULL;
}

int main(){

    printf("%d", N);

    A = memory_allocation();
    B = memory_allocation();
    C = memory_allocation();

    fill_array(A);
    fill_array(B);

    printf("A:");
    show_array(A);

    printf("B:");
    show_array(B);
    
    for (int i = 0; i < THREADS; ++i){
        arguments[i] = i;
        pthread_create(&(threads[i]), NULL, child_process, &(arguments[i]));
    }

    for (int i = 0; i < THREADS; ++i){
        pthread_join(threads[i], NULL);
    }

    show_array(C);

    free(A);
    free(B);
    free(C);

    return 0;
}