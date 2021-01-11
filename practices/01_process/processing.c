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

int average(int * data){
    int sum = 0;
    register int i;

    for (i = 0; i < N; ++i){
        sum += data[i];
    }

    return sum / N;
}

int howManyPairs(int * data){
    int pairs = 0;
    register int i;

    for (i = 0; i < N; ++i){
        pairs += !(data[i] & 1);
    }

    return pairs;
}