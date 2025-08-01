#include <stdio.h>
#include <stdlib.h>

struct my_data {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int status;
    int code;
};

void search(char *path);
int compare(struct my_data data1, int year, int month, int day);

int main() {
    char *path = malloc(sizeof(char) * 300);
    scanf("%s", path);

    search(path);

    free(path);

    return 0;
}

void search(char *path) {
    FILE *fi = fopen(path, "rb");
    struct my_data data;
    int day, month, year;

    if (fi != NULL) {
        scanf("%d.%d.%d", &day, &month, &year);
        int err = getchar();
        if (err == '\n') {
            while (fread(&data, sizeof(struct my_data), 1, fi)) {
                if (compare(data, year, month, day)) {
                    printf("%d", data.code);
                }
            }
        } else {
            printf("n/a");
        }
        fclose(fi);
    } else {
        printf("n/a");
    }
}

int compare(struct my_data data1, int year, int month, int day) {
    int y = 0;
    int m = 0;
    int d = 0;

    if (data1.year == year) {
        y = 1;
    }
    if (data1.month == month) {
        m = 1;
    }
    if (data1.day == day) {
        d = 1;
    }

    return (y && m && d);
}
