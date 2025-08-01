#include <stdio.h>
#define NMAX 10

void input(int *a, int *n, int *flag);
void output(int *a, const int *n, const int *flag);
void squaring(int *a, const int *n);

int main() {
    int n;
    int data[NMAX];
    int flag = 0;

    input(data, &n, &flag);
    squaring(data, &n);
    output(data, &n, &flag);

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

void output(int *a, const int *n, const int *flag) {
    if (*flag != 1) {
        for (int i = 0; i < *n; i++) {
            printf("%d", *(a + i));
            if (i < (*n - 1)) {
                printf(" ");
            }
        }
    }
}

void squaring(int *a, const int *n) {
    for (int *p = a; p - a < *n; p++) {
        *p = *p * *p;
    }
}
