#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREADS 4

int num1 = 20, num2 = 4;

void * thread_func(void * args);

int main() {
    int *results[THREADS], arguments[THREADS];
    pthread_t tids[THREADS];

    printf("Example of threads\n");

    int i;

    for (i = 0; i < THREADS; ++i){
        arguments[i] = i;
        pthread_create(&tids[i], NULL, thread_func, (void *)&arguments[i]);
    }

    for (i = 0; i < THREADS; ++i){
        pthread_join(tids[i], (void **) &(results[i]));
        printf("The result is %d\n", *results[i]);
        free(results[i]);
    }

    // free(r_sum);

    return 0;
}

void * thread_func(void * args){
    int n = ((int *) args)[0];

    printf("Thread number %d\n", n);
    int * result = (int *)malloc(sizeof(int));
    result[0] = n == 0 ?
                 num1 + num2 :
                 n == 1 ?
                 num1 - num2 :
                 n == 2 ?
                 num1 * num2 :
                 num1 / num2;
    
    pthread_exit((void *) result);
}