#include <stdio.h>
#include <stdlib.h>

void input_key(int *key, int *err);
void input_size(int *m, int *n, int *err);
void output(int **arr, int m, int n, int err);
void output_static(int m, int n, int arr[][n], int err);
void input_din_str(int ***arr, int m, int n, int *err);
void input_static(int m, int n, int arr[][n], int *err);
void input_din_segment(int ***arr, int m, int n, int *err, int **ptr);
void input_din_arr(int ***arr, int m, int n, int *err);


int main() {
    int n, m, err, key;
    int **arr, *ptr;
    int static_arr[100][100];

    input_key(&key, &err);
    if (err == 0) {
        input_size(&m, &n, &err);
        if (err == 0) {
            switch (key) {
                case 1:
                    input_static(m, n, static_arr, &err);
                    output_static(m, n, static_arr, err);
                    break;
                case 2:
                    input_din_str(&arr, m, n, &err);
                    output(arr, m, n, err);
                    free(arr);
                    break;
                case 3:
                    input_din_segment(&arr, m, n, &err, &ptr);
                    output(arr, m, n, err);
                    free(ptr);
                    free(arr);
                    break;
                case 4:
                    input_din_arr(&arr, m, n, &err);
                    output(arr, m, n, err);
                    for (int i = 0; i < m; i++) {
                        free(arr[i]);
                    }
                    free(arr);
                    break;
            }
        } else {
            printf("n/a");
        }
    } else {
        printf("n/a");
    }

    return 0;
}

void input_key(int *key, int *err) {
    scanf("%d", key);
    *err = getchar();

    if (*err != '\n' && *err != '\0' && *err != EOF) {
        *err = 1;
    } else {
        *err = 0;
    }
}

void input_size(int *m, int *n, int *err) {
    scanf("%d %d", m, n);
    *err = getchar();
    if ((*err != '\n' && *err != '\0' && *err != EOF) || *m <= 0 || *n <= 0) {
        *err = 1;
    } else {
        *err = 0;
    }
}

void input_din_str(int ***arr, int m, int n, int *err) {
    int count = 0;
    *err = 0;
    int str;

    *arr = malloc((m) * (n) * sizeof(int) + m * sizeof(int*));
    if (*arr == NULL) {
        *err = 1;
    } else {
        int *ptr = (int*) (*arr + m);

        for (int i = 0; i < m; i++) {
            (*arr)[i] = ptr + n * i;
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &(*arr)[i][j]);
                count++;
            }

            str = getchar();

            if (count > n || (str != '\n' && str != '\0' && str != EOF)) {
                *err = 1;
                break;
            }
            count = 0;
        }
    }
}

void input_static(int m, int n, int arr[][n], int *err) {
    if (m <= 100 && n <= 100) {
        int count = 0;
        *err = 0;
        int str;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &arr[i][j]);
                count++;
            }

            str = getchar();

            if (count > n || (str != '\n' && str != '\0' && str != EOF)) {
                *err = 1;
                break;
            }
            count = 0;
        }
    } else {
        *err = 1;
    }
}

void input_din_segment(int ***arr, int m, int n, int *err, int **ptr) {
    int count = 0;
    *err = 0;
    int str;

    *arr = malloc(m * sizeof(int*));
    if (*arr == NULL) {
        *err = 1;
    } else {
        *ptr =(int*) malloc(m * n * sizeof(int));
        if (*ptr != NULL) {
            for (int i = 0; i < m; i++) {
                (*arr)[i] = *ptr + n * i;
            }

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    scanf("%d", &(*arr)[i][j]);
                    count++;
                }

                str = getchar();

                if (count > n || (str != '\n' && str != '\0' && str != EOF)) {
                    *err = 1;
                    break;
                }
                count = 0;
            }
        }
    }
}

void input_din_arr(int ***arr, int m, int n, int *err) {
    int count = 0;
    *err = 0;
    int str;

    *arr = malloc(m * sizeof(int*));

    if (*arr == NULL) {
        *err = 1;
    } else {
        for (int i = 0; i < m; i++) {
            (*arr)[i] = malloc(n * sizeof(int));
            if ((*arr)[i] == NULL) {
                *err = 1;
            }
        }

        if (*err != 1) {
            for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &(*arr)[i][j]);
                count++;
            }

            str = getchar();

            if (count > n || (str != '\n' && str != '\0' && str != EOF)) {
                *err = 1;
                break;
            }
            count = 0;
            }
        }
    }
}

void output(int **arr, int m, int n, int err) {
    if (err == 0) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d", arr[i][j]);
                if (j != n - 1) {
                    printf(" ");
                }
            }
            if (i != m - 1) {
                printf("\n");
            }
        }
    } else {
        printf("n/a");
    }
}

void output_static(int m, int n, int arr[][n], int err) {
    if (err == 0) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d", arr[i][j]);
                if (j != n - 1) {
                    printf(" ");
                }
            }
            if (i != m - 1) {
                printf("\n");
            }
        }
    } else {
        printf("n/a");
    }
}
