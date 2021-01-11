#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "defs.h"
#include "process.h"
#include "helper.h"

int main(void){
    pid_t pid;
    register int i;

    int * data = memoryAllocation();
    fillArray(data);
    showArray(data);

    for (i = 0; i < NUMBER_OF_PROCS; ++i){
        pid = fork();

        if (pid == -1){
            perror("Error creating process!\n");
            exit(EXIT_FAILURE);
        }
        if (!pid){
            child_process(i, data);
        }
    }

    parent_process();

    free(data);

    return 0;
}