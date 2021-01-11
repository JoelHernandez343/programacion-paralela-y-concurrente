/**
 * Joel Hernández @ 2020
 * Github JoelHernandez343
 */

#include <stdio.h>
#include <stdlib.h>

#include "defs.h"

float *memory_allocation(){
    float *mem = (float *)malloc(N * sizeof(float));

    if (!mem) {
        perror(ERR_OUT" Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }

    return mem;
}

void show_array(float *array){
    register int i;

    for (i = 0; i < N; ++i){
        if (!(i % 16)) printf("\n");

        printf("%2.5f ", array[i]);
    }

    printf("\n");
}