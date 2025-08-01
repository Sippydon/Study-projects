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

void search_and_replace(char *path, int day1, int month1, int year1, int day2, int month2, int year2);
int compare(struct my_data data1, int day1, int month1, int year1, int day2, int month2, int year2);

int main() {
    int day1, day2, month1, month2, year1, year2;
    int err;
    char *path = malloc(sizeof(char) * 200);

    scanf("%s", path);
    scanf("%d.%d.%d", &day1, &month1, &year1);
    scanf("%d.%d.%d", &day2, &month2, &year2);
    err = getchar();

    if (err == '\n') {
        search_and_replace(path, day1, month1, year1, day2, month2, year2);
    } else {
        printf("n/a");
    }

    free(path);
    return 0;
}

void search_and_replace(char *path, int day1, int month1, int year1, int day2, int month2, int year2) {
    FILE *fi = fopen(path, "rb");
    struct my_data data;

    if (fi != NULL) {
        FILE *fi2 = fopen("tmp", "wb+");
        while (fread(&data, sizeof(struct my_data), 1, fi)) {
            if (!compare(data, day1, month1, year1, day2, month2, year2)) {
                fwrite(&data, sizeof(struct my_data), 1, fi2);
            }
        }
        rewind(fi2);
        fclose(fi);
        fi = fopen(path, "wb");
        while (fread(&data, sizeof(struct my_data), 1, fi2)) {
            fwrite(&data, sizeof(struct my_data), 1, fi);
            printf("%d %d %d %d %d %d %d %d\n", data.year,
                   data.month, data.day, data.hour, data.minute, data.second, data.status, data.code);
        }
        system("rm -rf tmp");
        fclose(fi2);
        fclose(fi);
    } else {
        printf("n/a");
    }
}

int compare(struct my_data data1, int day1, int month1, int year1, int day2, int month2, int year2) {
    int y = 0;
    int m = 0;
    int d = 0;

    if ((data1.year >= year1 && data1.year <= year2) || (data1.year >= year2 && data1.year <= year1)) {
        y = 1;
    }
    if ((data1.month >= month1 && data1.month <= month2) ||
        (data1.month >= month2 && data1.month <= month1)) {
        m = 1;
    }
    if ((data1.day >= day1 && data1.day <= day2) || (data1.day >= day2 && data1.day <= day1)) {
        d = 1;
    }

    return (y && m && d);
}
