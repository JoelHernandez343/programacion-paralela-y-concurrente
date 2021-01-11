/**
 * Joel Hernández @ 2020
 * Github JoelHernandez343
 */

#include <stdio.h>
#include <stdlib.h>

#include "defs.h"

int *memory_allocation(){
    int *mem = (int *)malloc(N * sizeof(int));

    if (!mem) {
        perror(ERR_OUT" Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }

    return mem;
}

void fill_array(int *array){
    register int i;

    for (i = 0; i < N; ++i){
        array[i] = rand() % 256;
    }
}


void show_array(int *array){
    register int i;
    for (i = 0; i < N; ++i){

        if (!(i % 16)) printf("\n");
        if (!i) printf("(");

        printf("%3d%c ", array[i], (i < N - 1 ? ',' : 0));
    }

    printf(")\n");
}