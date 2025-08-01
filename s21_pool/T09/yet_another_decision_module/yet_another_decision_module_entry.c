#include "decision.h"
#include <stdio.h>
#include <stdlib.h>
#include "../data_libs/data_io.h"

int main() {
    double *data;
    int n;

    data = (double*) malloc(10 * sizeof(double));
    n = 10;

    input(data, n);

    if (make_decision(data, n))
        printf("YES");
    else
        printf("NO");

    free(data);

    return 0;
}
