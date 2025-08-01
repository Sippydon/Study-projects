#include <stdio.h>
# define NMAX 10

void input(int *buffer, int *length, int *flag, int *c);
void output(int *buffer, int length);
void shift(int *buffer, int *shift_arr, int length, int c);

int main() {
    int length, buffer[NMAX], flag, c, shift_arr[NMAX];

    input(buffer, &length, &flag, &c);

    if (flag == 0) {
        shift(buffer, shift_arr, length, c);
        output(shift_arr, length);
    } else {
        printf("n/a");
    }

    return 0;
}

void input(int *buffer, int *length, int *flag, int *c) {
    char ch;

    scanf("%d", length);
    scanf("%c", &ch);

    if (ch == '\n' && *length > 0 && *length < 11) {
        for (int i = 0; i < *length; i++) {
            scanf("%d", (buffer + i));
        }

        scanf("%c", &ch);

        if (ch != '\n') {
            *flag = 1;
        }

        scanf("%d", c);
        scanf("%c", &ch);

        if (ch != '\n') {
            *flag = 1;
        }

    } else {
        *flag = 1;
    }
}

void output(int *buffer, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d", buffer[i]);
        if (i < (length - 1)) {
            printf(" ");
        }
    }
}

void shift(int *buffer, int *shift_arr, int length, int c) {
    int j = 0;

    if (c < 0) {
        c *= -1;

        for (int i = (length - c); i < length; i++) {
            shift_arr[j] = buffer[i];
            j++;
        }

        for (int i = 0; i < (length - c); i++) {
            shift_arr[j] = buffer[i];
            j++;
        }
    } else if (c > 0) {
        for (int i = c; i < length; i++) {
            shift_arr[j] = buffer[i];
            j++;
        }

        for (int i = 0; i < c; i++) {
            shift_arr[j] = buffer[i];
            j++;
        }
    } else if (c == 0) {
        for (int i = 0; i < length; i++) {
            shift_arr[i] = buffer[i];
        }
    }
}
