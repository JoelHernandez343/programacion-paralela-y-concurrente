/**
 * Joel Hernández @ 2020
 * Github JoelHernandez343
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "defs.h"
#include "helper.h"

#include "process.h"
#include "threads.h"

int *A, *B;
int result = 0;

void check_args(int argc, char *argv[]);

int main(int argc, char *argv[]){
    check_args(argc, argv);

    A = memory_allocation();
    B = memory_allocation();
    fill_array(A);
    fill_array(B);
    // printf("A:");
    // show_array(A);
    // printf("B:");
    // show_array(B);

    if (!strcmp(argv[1], "THREAD")){
        thread_parent_process();
    }
    else {
        proc_parent_process();
    }

    free(A);
    free(B);

    printf("The dot product is: %d\n", result);

    return 0;
}

void check_args(int argc, char *argv[]){
    if (argc != 2){
        printf(ERR_OUT" Number of arguments incorrect.\n");
        exit(EXIT_FAILURE);
    }

    char *argument = argv[1];
    for (int i = 0; i < strlen(argument); ++i){
        argument[i] = toupper(argument[i]);
    }

    if (strcmp(argument, "THREAD") && strcmp(argument, "PROCESS")){
        printf(ERR_OUT" Argument must be \"thread\" or \"process\".\n");
        exit(EXIT_FAILURE);
    }
}