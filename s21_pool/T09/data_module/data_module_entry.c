#include "data_process.h"
#include "../data_libs/data_io.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    double *data;
    int n;

    //  Don`t forget to allocate memory !
    data = (double*) malloc(10 * sizeof(double));
    n = 10;


    input(data, n);

    if (normalization(data, n))
        output(data, n);
    else
        printf("ERROR");

    free(data);

    return 0;
}
