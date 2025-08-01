#include <stdio.h>
#define NMAX 10

void input(int *mass, int *n, int *flag);
void sort(int *mass, int n);
void print_output(int *mass, int n);
void swap(int *mass, int i, int j);

int main() {
    int n, mass[NMAX], flag;
    flag = 0;

    input(mass, &n, &flag);
    if (flag == 0) {
        sort(mass, n);
        print_output(mass, n);
    } else {
        printf("n/a");
    }

    return 0;
}

void input(int *mass, int *n, int *flag) {
    char c;

    for (int i = 0; i < NMAX; i++) {
        scanf("%d", (mass + i));
        *n = i;
    }

    *n += 1;
    scanf("%c", &c);

    if (*n > NMAX ||  c != '\n') {
        *flag = 1;
    }
}

void sort(int *mass, int n) {
    int i = 0;
    int j = n - 1;

    int mid = mass[n/ 2];

    do {
        while (mass[i] < mid) {
            i++;
        }

        while (mass[j] > mid) {
            j--;
        }

        if (i <= j) {
            swap(mass, i, j);

            i++;
            j--;
        }
    } while (i <= j);

    if (j > 0) {
        sort(mass, j + 1);
    }
    if (i < n) {
        sort(&mass[i], n - i);
    }
}

void swap(int *mass, int i, int j) {
    int tmp = mass[i];
    mass[i] = mass[j];
    mass[j] = tmp;
}

void print_output(int *mass, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", mass[i]);
        if (i < (n - 1)) {
            printf(" ");
        }
    }
}
