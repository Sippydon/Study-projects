# include <stdio.h>

int main() {
    int name;
    char c;

    scanf("%d", &name);
    scanf("%c", &c);

    if (c == '\n' || c == EOF) {
        printf("Hello, %d!\n", name);
    } else {
        printf("n/a\n");
    }

    return 0;
}
