#include <stdio.h>
#include <stdlib.h>

#include "defs.h"

void save_data(float data[]){
    FILE * file = fopen("sin.data", "w");
    register int n;

    if (!file){
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    for (n = 0; n < SAMPLES; ++n){
        fprintf(file, "%f \n", data[n]);
    }

    fclose(file);
}