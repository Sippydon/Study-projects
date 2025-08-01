#include <stdio.h>

int main() {
    float x;
    float y;
    char c;

    scanf("%f %f", &x, &y);
    scanf("%c", &c);

    if (c == '\n') {
        if ((x*x + y*y) < 25) {
            printf("GOTCHA\n");
        } else {
            printf("MISS\n");
        }
    } else {
        printf("n/a\n");
    }

    return 0;
}
