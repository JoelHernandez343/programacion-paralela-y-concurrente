/**
 * Joel Hernández @ 2020
 * Github JoelHernandez343
 */

void fill_hann_window(float *hann);
void multiply_alternately(float *a, float *b, float *result, int begin, int jump);
void multiply_by_blocks(float *a, float *b, float *result, int begin, int end);
int autocorrelation_sum(float *x, int l);
void autocorrelation_alternately(float *x, float *rxx, int begin, int jump);
void autocorrelation_by_blocks(float *x, float *rxx, int begin, int end);