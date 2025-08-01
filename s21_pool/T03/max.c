#include <stdio.h>

int main() {
    int x;
    int y;
    char c;

    scanf("%d %d", &x, &y);
    scanf("%c", &c);

    if (c == '\n' || c == EOF) {
        if (x >= y) {
            printf("%d\n", x);
        } else {
            printf("%d\n", y);
        }
    } else {
        printf("n/a\n");
    }
}
