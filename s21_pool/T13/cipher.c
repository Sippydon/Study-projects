#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_buffer();

char* quest_1(FILE** fi, char* path);
void quest_2(FILE* fi, char* path);
void quest_3();
FILE* check(char *str, int q);

int main() {
    int err, key;
    FILE *fi = NULL;
    char *path;

    while (1) {
        scanf("%d", &key);
        err = getchar();

        if (key == -1) {
            break;
        } else if (key == 1 && err == '\n') {
            path = quest_1(&fi, path);
        } else if (key == 2 && err == '\n') {
            quest_2(fi, path);
        } else {
            printf("n/a\n");
            clear_buffer();
        }
    }

    return 0;
}

char* quest_1(FILE **fi, char* path) {
    path = malloc(sizeof(char) * 100);
    scanf("%s", path);

    *fi = check(path, 1);
    if (*fi != NULL) {
        int c = getc(*fi);
        while (c != EOF) {
            putc(c, stdout);
            c = getc(*fi);
        }
        free(path);
    } else {
        printf("n/a\n");
    }

    return path;
}

void quest_2(FILE* fi, char* path) {
    if (fi != NULL) {
        char *str = malloc(sizeof(char) * 1000);
        FILE *fi2 = fopen(path, "a");
        scanf("%s", str);

        fputs(str, fi2);
        fclose(fi2);
        fclose(fi);
        fi = fopen(path, "r");

        int c = getc(fi);
        while (c != EOF) {
            putc(c, stdout);
            c = getc(fi);
        }
        free(str);
    }
}

//  void quest_3() {
//    char* path = "/src/ai_modules";
//    int shift, err;
//
//    scanf("%d", &shift);
//    err = getchar();
//
//    if (err == '\n') {
//        system("ls -1 ../src/ai_modules/*.c > files.txt");
//        system("ls -1 ../src/ai_modules/*.h >> files.txt");
//        system("break");
//
//        FILE* files = fopen("files.txt", "r");
//        char* buff;
//
//        while(1) {
//            buff = malloc(sizeof(char) * 200);
//            fgets(buff, 150, files);
//
//            if (strstr(buff, ".c")) {
//
//            } else if (strstr(buff, ".h")) {
//                FILE *fp = fopen(buff, "a+");
//                fclose(fp);
//            }
//        }
//    }
//}

FILE* check(char *str, int q) {
    FILE *fi = NULL;
    if (q == 1) {
        fi = fopen(str, "r");
        if (fi != NULL) {
            int c = getc(fi);
            if (c == EOF) {
                fclose(fi);
                fi = NULL;
            }
        }
    }

    return fi;
}

void clear_buffer() {
    fflush(stdin);
}
