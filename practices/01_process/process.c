#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "processing.h"
#include "defs.h"

void child_process(int np, int * data){
    int result = np == 0 ?
                 searchHighest(data) :
                 np == 1 ?
                 searchLowest(data) :
                 np == 2 ?
                 average(data) :
                 howManyPairs(data);

    exit(result);
}

void parent_process(){
    register int i;
    pid_t pid;
    int status, result;

    for (i = 0; i < NUMBER_OF_PROCS; ++i){
        pid = wait(&status);
        result = status >> 8;

        printf("The process w/ pid %d has finished. Result: %d\n", pid, result);
    }
}