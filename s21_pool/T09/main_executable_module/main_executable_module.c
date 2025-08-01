#include <stdio.h>
#include <stdlib.h>
#include "../data_libs/data_io.h"
#include "../data_module/data_process.h"
#include "../yet_another_decision_module/decision.h"

void sort(double *data, int n);

void main() {
    double *data;
    int n;

    data = (double*) malloc(10 * sizeof(double));
    n = 10;

    printf("LOAD DATA...\n");
    input(data, n);

    printf("RAW DATA:\n\t");
    output(data, n);

    printf("\nNORMALIZED DATA:\n\t");
    if (normalization(data, n))
        output(data, n);
    else
        printf("ERROR");

    printf("\nSORTED NORMALIZED DATA:\n\t");
    sort(data, n);
    output(data, n);

    printf("\nFINAL DECISION:\n\t");
    if (make_decision(data, n))
        printf("YES");
    else
        printf("NO");

    free(data);
}

void sort(double *data, int n) {
    int tmp;

    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j > i; j--) {
            if (data[j - 1] > data[j]) {
                tmp = data[j - 1];
                data[j - 1] = data[j];
                data[j] = tmp;
            }
        }
    }
}
