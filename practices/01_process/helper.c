#include <stdio.h>
#include <stdlib.h>

#include "defs.h"

int * memoryAllocation(){
    int * mem = (int *)malloc(N * sizeof(int));

    if (!mem) {
        perror("Error allocating memory...\n");
        exit(EXIT_FAILURE);
    }

    return mem;
}

void fillArray(int * array){
    register int i;

    for (i = 0; i < N; ++i){
        array[i] = rand() % 256;
    }
}

void showArray(int * array){
    register int i;

    for (i = 0; i < N; ++i){
        if (!(i % 16)) printf("\n");

        printf("%3d ", array[i]);
    }

    printf("\n");
}