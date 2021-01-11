/**
 * Joel Hernández @ 2020
 * Github JoelHernandez343
 */
#include <stdio.h>

#include "defs.h"

float average_calc(int *array){
    int sum = 0;
    register int i;

    for (i = 0; i < N; ++i){
        sum += array[i];
    }

    return sum / (float) N;
}

int count_pairs(int *array){
    int pairs = 0;
    register int i;

    for (i = 0; i < N; ++i){
        pairs += !(array[i] & 1);
    }

    return pairs;
}

void bubble_sort(int *array){
    register int i, j;

    for (i = 0; i < N - 1; ++i){
        for (j = i + 1; j < N; ++j){
            if (array[i] > array[j]){
                int aux = array[i];
                array[i] = array[j];
                array[j] = aux;
            }
        }
    }
}

int is_prime(int number){
    if (number < 2)
        return 0;

    if (number == 2)
        return 1;

    for (int i = 2; i * i <= number; ++i){
        if (!(number & 1))
            return 0;
        
        if (!(number % i))
            return 0;
    }

    return 1;
}

int count_primes(int *array){
    int primes = 0;
    register int i;
    
    for (i = 0; i < N; ++i){
        
        if (is_prime(array[i]))
            printf("\033[40;33m %d \033[0m", array[i]);

        primes += is_prime(array[i]);
    }

    return primes;
}