/*
    Search module for the desired value from data array.

    Returned value must be:
        - "even"
        - ">= mean"
        - "<= mean + 3 * sqrt(variance)"
        - "!= 0"

        OR

        0
*/
#include <stdio.h>
#include <math.h>
#define NMAX 30

void input(int *a, int *n, int *flag);
void validNumber(int *a, int n, int flag);
double mean(int *a, int n);
int even(int x);
int tSigm(int *a, int n, int x);

int main() {
    int n, data[NMAX];
    int flag = 0;
    input(data, &n, &flag);
    validNumber(data, n, flag);

    return 0;
}

void input(int *a, int *n, int *flag) {
    int size;
    int d;
    char c;

    scanf("%d", &size);
    scanf("%c", &c);

    if ((c == '\n' || c == ' ') && size > 0 && size < 31) {
        *n = size;

        for (int *p = a; p - a < *n; p++) {
            scanf("%d", &d);
            *p = d;
        }

        scanf("%c", &c);

        if (c != '\n' && c != ' ') {
            printf("n/a");
            *flag = 1;
        }
    } else {
        printf("n/a");
        *flag = 1;
    }
}

void validNumber(int *a, int n, int flag) {
    for (int *p = a; p - a < n; p++) {
        if (*p != 0 && even(*p) == 1 && mean(a, n) <= *p && tSigm(a, n, *p) == 1 && flag != 1) {
            printf("%d", *p);
            break;
        }

        if ((p - a) == (n - 1) &&  flag == 0) {
            printf("0");
        }
    }
}

double mean(int *a, int n) {
    double m = 0;

    for (int *p = a; p - a < n; p++) {
        m += *p;
    }

    return (m / n);
}

int even(int x) {
    int e;

    if ((x % 2) == 0) {
        e = 1;
    } else {
        e = 0;
    }

    return e;
}

int tSigm(int *a, int n, int x) {
    int flag;
    double mean_v = mean(a, n);
    int s = sqrt(mean_v);
    int s1, s2;

    s1 = s * 3 + mean_v;
    s2 = mean_v - s * 3;

    if (s2 < x && x < s1) {
        flag = 1;
    } else {
        flag = 0;
    }

    return flag;
}
