/**
 * Joel Hernández @ 2020
 * Github JoelHernandez343
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "defs.h"
#include "helper.h"
#include "threads.h"

pthread_t threads[THREADS];
int *array;
float average;
int pairs, primes;

pthread_mutex_t lock;

int main(){

    array = memory_allocation();
    fill_array(array);
    
    printf("Original array: ");
    show_array(array);

    pthread_mutex_init(&lock, NULL);
    
    for (int i = 0; i < THREADS; ++i){
        pthread_create(&(threads[i]), NULL, child_process, NULL);
    }

    parent_process();

    free(array);
    pthread_mutex_destroy(&lock);

    return 0;
}