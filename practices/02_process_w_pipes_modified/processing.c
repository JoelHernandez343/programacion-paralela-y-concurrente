/**
 * Joel Hernández @ 2020
 * Github JoelHernandez343
 */

#include "defs.h"

int searchHighest(int * data){
    int higher = data[0];
    register int i;

    for (i = 1; i < N; ++i){
        if (data[i] > higher){
            higher = data[i];
        }
    }

    return higher;
}

int searchLowest(int * data){
    int lower = data[0];
    register int i;

    for (i = 1; i < N; ++i){
        if (data[i] < lower){
            lower = data[i];
        }
    }

    return lower;
}

float average(int * data){
    int sum = 0;
    register int i;

    for (i = 0; i < N; ++i){
        sum += data[i];
    }

    return sum / (float) N;
}

int howManyPairs(int * data){
    int pairs = 0;
    register int i;

    for (i = 0; i < N; ++i){
        pairs += !(data[i] & 1);
    }

    return pairs;
}

void bubblesort(int * data){
    register int i, j;

    for (i = 0; i < N - 1; ++i){
        for (j = i + 1; j < N; ++j){
            if (data[i] > data[j]){
                int aux = data[i];
                data[i] = data[j];
                data[j] = aux;
            }
        }
    }
}

void multByConstant(int * data){
    register int i;

    for (i = 0; i < N; ++i){
        data[i] *= C;
    }
}