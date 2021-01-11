/**
 * Joel Hernández @ 2020
 * Github JoelHernandez343
 */

#include <math.h>

#include "defs.h"

void fill_hann_window(float *hann){
    register int n;

    for (n = 0; n < N; ++n){
        hann[n] = (1 - cosf(2 * M_PI * n / (N - 1))) * 0.5;
    }
}

void multiply_alternately(float *a, float *b, float *r, int begin, int jump){
    register int i;

    for (i = begin; i < N; i += jump){
        r[i] = a[i] * b[i];
    }
}

void multiply_by_blocks(float *a, float *b, float *r, int begin, int end){
    register int i;

    for (i = begin; i < end; ++i){
        r[i] = a[i] * b[i];
    }
}

int autocorrelation_sum(float *x, int l){
    int result = 0;
    
    register int n;
    for (n = l; n < N; ++n){
        result += x[n] * x [n - l];
    }

    return result;
}

void autocorrelation_alternately(float *x, float *rxx, int begin, int jump){
    register int l;

    for (l = begin; l < N; l += jump){
        rxx[l] = autocorrelation_sum(x, l);
    }
}

void autocorrelation_by_blocks(float *x, float *rxx, int begin, int end){
    register int l;

    for (l = begin; l < end; ++l){
        rxx[l] = autocorrelation_sum(x, l);
    }
}