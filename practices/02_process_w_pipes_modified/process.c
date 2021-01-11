/**
 * Joel Hernández @ 2020
 * Github JoelHernandez343
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "defs.h"
#include "helper.h"
#include "processing.h"

void child_process(int np, int * data, int pipe []){
    close(pipe[0]);
    
    if (np == 0){
        bubblesort(data);
        write(pipe[1], data, sizeof(int) * N);
    }
    else if (np == 1){
        float result = average(data);
        write(pipe[1], &result, sizeof(float));
    }
    else if (np == 2){
        int result = howManyPairs(data);
        write(pipe[1], &result, sizeof(int));
    }
    else {
        multByConstant(data);
        write(pipe[1], data, sizeof(int) * N);
    }

    close(pipe[1]);
    free(data);
    exit(np);
}

void parent_process(int pipes [][2]){
    register int i;
    pid_t pid;
    int status, p;

    char * message[] = {
        "The sorted array is: ",
        "The average is: ",
        "The number of pairs is: ",
        "The multiplied array is: ",
    };

    for (i = 0; i < NUMBER_OF_PROCS; ++i){
        pid = wait(&status);
        p = status >> 8;

        printf("\033[40;32mProcess %d \033[0m w/ pid %d has finished\n", p, pid);
        printf("%s", message[p]);

        if (p == 0 || p == 3){
            int array[N];
            read(pipes[p][0], array, sizeof(int) * N);
    
            showArray(array);
        }
        else if (p == 1){
            float result;
            read(pipes[p][0], &result, sizeof(float));

            printf("%f\n", result);
        }
        else {
            int result;
            read(pipes[p][0], &result, sizeof(int));

            printf("%d\n", result);
        }

        close(pipes[p][0]);
        close(pipes[p][1]);
    }
}