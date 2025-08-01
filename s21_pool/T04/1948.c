#include <stdio.h>
#include <math.h>

int division(int x, int y);
int rec(int x);


int main() {
    int x;
    char c;

    scanf("%d", &x);
    scanf("%c", &c);

    if (c == '\n') {
        printf("%d\n", rec(x));
    } else {
        printf("n/a\n");
    }

    return 0;
}

int division(int x, int y) {
    int result = 0;


    while (x >= y) {
        x -= y;
        result++;
    }
    if (x == 0)
        return result;
    else
        return -1;
}

int rec(int x) {
if (x < 0) {
        x *= -1;
}

int i, y;
i = 2;
y = x;
while (x != 1) {
    if (division(x, i) != -1) {
         y = i;
         x = division(x, i);
    } else if (i*i > x) {
        i = x;
    } else {
         i++;
    }
    }
    return y;
}
