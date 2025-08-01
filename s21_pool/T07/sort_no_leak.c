#include <stdio.h>
#include <stdlib.h>

int input(int **a, int *n);
void output(int *a, int n);
void sort(int *a, int n);
void swap(int *a, int *b);

int main() {
    int *data;
    int n;
    int error = input(&data, &n);
    if (error < 1) {
        sort(data, n);
        output(data, n);
    } else {
        printf("n/a");
    }

    free(data);

    return 0;
}

void sort(int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                swap(&a[j], &a[j + 1]);
            }
        }
    }
}


void swap(int *a, int *b) {
    int z = *a;
    *a = *b;
    *b = z;
}

void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        printf("%d", *p);
        if (p - a < n - 1) {
            printf(" ");
        }
    }
}

int input(int **a, int *n) {
    int error = 1;
    int count = 0;
    count += scanf("%d", n);
    *a = (int*) malloc(*n * sizeof(int));
    if (*a == NULL) {
    } else {
        for (int *p = *a; p - *a < *n; p++) {
            count += scanf("%d", p);
        }
        int err = getchar();
        if (count == *n + 1 && (err == '\n' || err == '\0' || err == EOF)) {
            error = 0;
        }
    }
    return error;
}
