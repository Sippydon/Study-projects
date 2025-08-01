#include <stdio.h>

int sum(int x, int y);
int diff(int x, int y);
int multi(int x, int y);
int div(int x, int y);

int main() {
    int x;
    int y;
    char c;

    scanf("%d %d", &x, &y);
    scanf("%c", &c);

    if (c == '\n') {
        if (y != 0) {
            printf("%d %d %d %d\n", sum(x, y), diff(x, y), multi(x, y), div(x, y));
        } else {
            printf("%d %d %d n/a\n", sum(x, y), diff(x, y), multi(x, y));
        }
    } else {
        printf("n/a\n");
    }

    return 0;
}

int sum(int x, int y) {
    return (x + y);
}

int diff(int x, int y) {
    return (x - y);
}

int div(int x, int y) {
    return (x / y);
}

int multi(int x, int y) {
    return (x * y);
}
