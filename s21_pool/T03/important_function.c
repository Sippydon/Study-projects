#include <stdio.h>
#include <math.h>

int main() {
    char c;
    float res;
    float x;

    scanf("%f", &x);
    scanf("%c", &c);

    if (c == '\n') {
        res = 0.007 * pow(x, 4) + ((22.8 * cbrt(x) - 1000.0) * x + 3.0)
            / (x * x / 2.0) - x * pow((10.0 + x), (2.0/x)) - 1.01;
        printf("%.1f\n", res);
    } else {
        printf("n/a \n");
    }

    return 0;
}
