#include <stdio.h>
#include <math.h>

#include "defs.h"

void gen_sin(float sin[]){
    float f = 1000, fs = 45000;
    register int n;

    for (n = 0; n < SAMPLES; ++n){
        sin[n] = sinf(2 * n * M_PI * f / fs);
    }
}