/**
 * Joel Hernández @ 2020
 * Github JoelHernandez343
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "defs.h"
#include "helper.h"
#include "processing.h"

extern pthread_t threads[THREADS];
extern int *array;
extern float average;
extern int pairs;
extern int primes;

extern pthread_mutex_t lock;

void *child_process(void *args){

    pthread_t self = pthread_self();

    pthread_mutex_lock(&lock);

    if (pthread_equal(self, threads[THREAD_SORT])){
        bubble_sort(array);
    }
    else if (pthread_equal(self, threads[THREAD_AVERAGE])){
        average = average_calc(array);
    }
    else if (pthread_equal(self, threads[THREAD_PAIRS])){
        pairs = count_pairs(array);
    }
    else if (pthread_equal(self, threads[THREAD_PRIMES])){
        primes = count_primes(array);
    }

    pthread_mutex_unlock(&lock);

    return NULL;
}

void parent_process(){
    register int i;
    char *message[] = {
        "The sorted array is: ",
        "The average is: ",
        "The number of pairs is: ",
        "The number of primes is: ",
    };

    for (i = 0; i < THREADS; ++i){
        pthread_join(threads[i], NULL);

        printf("\033[40;32mThread %d \033[0m has finished\n", i);
        printf("%s", message[i]);

        if (i == THREAD_SORT){
            show_array(array);
        }
        else if (i == THREAD_AVERAGE){
            printf("%f\n", average);
        }
        else if (i == THREAD_PAIRS){
            printf("%d\n", pairs);
        }
        else if (i == THREAD_PRIMES) {
            printf("%d\n", primes);
        }
    }
}