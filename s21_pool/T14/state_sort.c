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

void print(char* path);
void sort(char* path);
void write(char* path);
int compare(struct my_data data1, struct  my_data data2);
void swap(FILE* fi, struct my_data* data1, struct my_data* data2, int index);

int main() {
    char* path = malloc(sizeof(char) * 300);
    int key;
    scanf("%s", path);
    scanf("%d", &key);
    int err = getchar();

    if (key == 0 && err == '\n') {
        print(path);
    } else if (key == 1 && err == '\n') {
        sort(path);
    } else if (key == 2 && err == '\n') {
        write(path);
    } else {
        printf("n/a");
    }
    free(path);
    return 0;
}

void print(char* path) {
    FILE* fi = fopen(path, "rb");
    if (fi != NULL) {
        struct my_data data;

        while (fread(&data, sizeof(struct my_data), 1, fi)) {
            printf("%d %d %d %d %d %d %d %d\n", data.year,
                   data.month, data.day, data.hour, data.minute, data.second, data.status, data.code);
        }
    } else {
        printf("n/a");
    }
    fclose(fi);
}

void sort(char* path) {
    FILE* fi = fopen(path, "rb");
    if (fi != NULL) {
        fclose(fi);
        FILE* fi = fopen(path, "r+b");
        fseek(fi, 0, SEEK_END);
        long long len;
        len  = ftell(fi) / sizeof(struct my_data);
        rewind(fi);
        struct my_data data1;
        struct my_data data2;
        for (int i = 0; i < len - 1; i++) {
            for (int j = 0; j < len - 1 - i; j++) {
                fseek(fi, sizeof(struct my_data) * j, SEEK_SET);
                fread(&data1, sizeof(struct my_data), 1, fi);
                rewind(fi);

                fseek(fi, sizeof(struct my_data) * (j + 1), SEEK_SET);
                fread(&data2, sizeof(struct my_data), 1, fi);
                rewind(fi);

                if (compare(data1, data2) == 1) {
                    swap(fi, &data1, &data2, j);
                }
            }
        }
        fclose(fi);
        print(path);
    } else {
        printf("n/a");
    }
    fclose(fi);
}

void write(char* path) {
    FILE* fi = fopen(path, "rb");
    int err;
    struct my_data tmp;

    if (fi != NULL) {
        fclose(fi);
        scanf("%d %d %d %d %d %d %d %d", &(tmp.year), &(tmp.month), &(tmp.day),
              &(tmp.hour), &(tmp.minute), &(tmp.second), &(tmp.status), &(tmp.code));
        err = getchar();
        if (err == '\n') {
            fi = fopen(path, "ab");
            err = fwrite(&tmp, sizeof(struct my_data), 1, fi);
            if (err == 1) {
                rewind(fi);
                sort(path);
                print(path);
            } else {
                printf("n/a");
            }
            fclose(fi);
        } else {
            printf("n/a");
        }
    } else {
        printf("n/a");
    }
}

int compare(struct my_data in1, struct my_data in2) {
    int res = -1;
    if (in1.year > in2.year) {
        res = 1;
    } else if (in1.year == in2.year) {
        if (in1.month > in2.month) {
            res = 1;
        } else {
            if (in1.month == in2.month) {
                if (in1.day > in2.day) {
                    res = 1;
                } else {
                    if (in1.day == in2.day) {
                        if (in1.hour > in2.hour) {
                            res = 1;
                        } else {
                            if (in1.hour == in2.hour) {
                                if (in1.minute > in2.minute) {
                                    res = 1;
                                } else {
                                    if (in1.minute == in2.minute) {
                                        if (in1.second > in2.second) {
                                            res = 1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        res = 0;
    }
    return res;
}

void swap(FILE* fi, struct my_data* data1, struct my_data* data2, int index) {
    fseek(fi, sizeof(struct my_data) * index, SEEK_SET);
    fwrite(data2, sizeof(struct my_data), 1, fi);
    fflush(fi);
    rewind(fi);

    fseek(fi, sizeof(struct my_data) * (index + 1), SEEK_SET);
    fwrite(data1, sizeof(struct my_data), 1, fi);
    fflush(fi);
    rewind(fi);
}

