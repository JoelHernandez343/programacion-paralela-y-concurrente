#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "defs.h"
#include "processing.h"

void child_process(int np, int * data, int pipe []){
    close(pipe[0]);
    
    if (np != 2){
        int result = np == 0 ?
                     searchHighest(data) :
                     np == 1 ?
                     searchLowest(data) :
                     howManyPairs(data);
        
        write(pipe[1], &result, sizeof(int));
    }
    else {
        float result = average(data);

        write(pipe[1], &result, sizeof(float));
    }

    close(pipe[1]);
    exit(np);
}

void parent_process(int pipes [][2]){
    register int i;
    pid_t pid;
    int status, p;

    for (i = 0; i < NUMBER_OF_PROCS; ++i){
        pid = wait(&status);
        p = status >> 8;

        printf("Process %d w/ pid %d has finished\n", p, pid);

        char * message = (p == 0) ?
                         "The highest value is: " :
                         (p == 1) ?
                         "The lowest value is: " :
                         (p == 2) ?
                         "The average is: " :
                         "The number of pairs is: ";
        printf("%s", message);

        if (p != 2){
            int result;
            read(pipes[p][0], &result, sizeof(int));
            printf("%d\n", result);
        }
        else {
            float result;
            read(pipes[p][0], &result, sizeof(float));
            printf("%f\n", result);
        }
    }
}