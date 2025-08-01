#include "data_stat.h"

double max(double *data, int n);
double min(double *data, int n);
double mean(double *data, int n);
double variance(double *data, int n);

double max(double *data, int n) {
    double res = data[0];

    for (int i = 0; i < n; i++) {
        if (res < data[i]) {
            res = data[i];
        }
    }

    return res;
}

double min(double *data, int n) {
    double res = data[0];

    for (int i = 0; i < n; i++) {
        if (res > data[i]) {
            res = data[i];
        }
    }

    return res;
}

double mean(double *data, int n) {
    double sum = 0;
    double res;

    for (int i = 0; i < n; i++) {
        sum += data[i];
    }

    if (sum == 0) {
        res = 0;
    } else {
        res = sum / n;
    }

    return res;
}

double variance(double *data, int n) {
    double tmp[10];
    int m = mean(data, n);
    int res;

    for (int i = 0; i < n; i++) {
        tmp[i] = (data[i] - m) * (data[i] - m);
    }

    res = mean(tmp, n);

    return res;
}
