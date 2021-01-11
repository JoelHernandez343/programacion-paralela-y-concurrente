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
#include "processing.h"
#include "files.h"

#include "process.h"
#include "threads.h"

float *data;
float *hann_data;
float *result;

void check_args(int argc, char *argv[]);

int main(int argc, char *argv[]){
    check_args(argc, argv);

    data = memory_allocation();
    hann_data = memory_allocation();
    result = memory_allocation();

    read_data(data, "PulseSensor.dat");
    fill_hann_window(hann_data);

    if (!strcmp(argv[1], "THREAD")){
        thread_parent_process();
    }
    else {
        proc_parent_process();
    }

    save_data(hann_data, "hann.data");
    save_data(result, "result.data");

    free(data);
    free(hann_data);
    free(result);

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