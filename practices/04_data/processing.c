/**
 * Joel Hernández @ 2020
 * Github JoelHernandez343
 */

#include <math.h>

#include "defs.h"

#define A 1

void fill_hann_window(float *hann){
    register int n;

    for (n = 0; n < N; ++n){
        hann[n] = (1 - cosf(2 * M_PI * n / (N - 1))) * 0.5;
    }
}