/**
 * Joel Hernández @ 2020
 * Github JoelHernandez343
 */

#include <stdio.h>
#include <stdlib.h>

#include "defs.h"

void save_data(float data[], char *file_name){
    FILE *file = fopen(file_name, "w");
    register int i;

    if (!file){
        printf(ERR_OUT" Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < N; ++i){
        fprintf(file, "%2.5f\n", data[i]);
    }

    fclose(file);
}

void read_data(float data[], char *file_name){
    FILE *file = fopen(file_name, "r");
    register int i;

    if (!file){
        printf(ERR_OUT" Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < N; ++i){
        fscanf(file, "%f\n", &(data[i]));
        data[i] -= 2200;
    }

    fclose(file);
}