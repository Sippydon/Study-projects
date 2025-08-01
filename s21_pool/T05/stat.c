#include <stdio.h>
#define NMAX 10

void input(int *a, int *n, int *flag);
void output(int *a, const int n, const int flag);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);
void squaring(int *a, const int n);

void output_result(int maxv, int minv, double meanv, double variancev, int flag);

int main() {
    int n, data[NMAX];
    int flag = 0;
    input(data, &n, &flag);
    output(data, n, flag);
    output_result(max(data, n), min(data, n), mean(data, n), variance(data, n), flag);

    return 0;
}

void input(int *a, int *n, int *flag) {
    int size;
    int d;
    char c;

    scanf("%d", &size);
    scanf("%c", &c);

    if (c == '\n' && size > 0 && size < 11) {
        *n = size;

        for (int *p = a; p - a < *n; p++) {
            scanf("%d", &d);
            *p = d;
        }

        scanf("%c", &c);

        if (c != '\n') {
            printf("n/a");
            *flag = 1;
        }
    } else {
        printf("n/a");
        *flag = 1;
    }
}

void output(int *a, const int n, const int flag) {
    if (flag != 1) {
        for (int i = 0; i < n; i++) {
            printf("%d", *(a + i));
            if (i < (n - 1)) {
                printf(" ");
            }
        }
    }

    printf("\n");
}

double mean(int *a, int n) {
    double m = 0;

    for (int *p = a; p - a < n; p++) {
        m += *p;
    }

    return (m / n);
}

double variance(int *a, int n) {
    double mean_v = mean(a, n);
    double variance;
    int x[10];

    for (int i = 0; i < n; i++) {
        x[i] = *(a + i);
    }

    for (int i = 0; i < n; i++) {
        x[i] -= mean_v;
    }

    squaring(x, n);

    variance = mean(x, n);

    return variance;
}

void squaring(int *a, const int n) {
    for (int *p = a; p - a < n; p++) {
        *p = *p * *p;
    }
}

void output_result(int maxv, int minv, double meanv, double variancev, int flag) {
    if (flag != 1) {
        printf("%d %d %.6lf %.6lf", maxv, minv, meanv, variancev);
    }
}

int max(int *a, int n) {
    int max = *a;

    for (int *p = a; p - a < n; p++) {
        if (max < *p) {
            max = *p;
        }
    }

    return max;
}

int min(int *a, int n) {
    int min = *a;

    for (int *p = a; p - a < n; p++) {
        if (min > *p) {
            min = *p;
        }
    }

    return min;
}
