#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "defs.h"
#include "process.h"
#include "helper.h"

int main(){
    pid_t pid;
    int pipes [NUMBER_OF_PROCS][2];
    register int i;
    
    int * data = memoryAllocation();
    fillArray(data);
    showArray(data);

    for (i = 0; i < NUMBER_OF_PROCS; ++i){
        pipe(pipes[i]);

        pid  = fork();

        if (pid == -1) {
            perror("Error creating process!\n");
            exit(EXIT_FAILURE);
        }
        if (!pid){
            child_process(i, data, pipes[i]);
        }
    }

    parent_process(pipes);

    free(data);

    return 0;
}