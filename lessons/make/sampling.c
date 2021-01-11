#include <stdio.h>

#include "files.h"
#include "processing.h"
#include "defs.h"

int main() {
    float sin[SAMPLES];

    gen_sin(sin);
    save_data(sin);

    return 0;
}