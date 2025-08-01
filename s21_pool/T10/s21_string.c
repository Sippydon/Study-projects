#include "s21_string.h"
#include <stdlib.h>
#include <stdio.h>

int s21_strlen(char *str);
int s21_strcmp(char *str, char *str2);
char* s21_strcpy(char *str, char *str2);
char* s21_strcat(char *str, char *str2);
int s21_strchr(char *str, char c);

int s21_strlen(char *str) {
    int size = 0;
    for ( ; str[size] != '\0'; size++) {
    }

    return size;
}

int s21_strcmp(char *str, char *str2) {
    int result = 0;

    if (s21_strlen(str) > s21_strlen(str2)) {
        result = 1;
    } else if (s21_strlen(str) < s21_strlen(str2)) {
        result = -1;
    } else if (s21_strlen(str) == s21_strlen(str2)) {
        int i = 0;
        while (str[i] != '\0' && result == 0 && str2[i]) {
                result = str[i] - str2[i];
                i++;
        }
    }

    return result;
}

char* s21_strcat(char *str, char *str2) {
    int i = 0, j = 0;
    char *cpy = malloc(sizeof(str) + sizeof(str2) + 1);

    while (str[i] != '\0') {
        cpy[i] = str[i];
        i++;
    }

    while (str2[j] != '\0') {
        cpy[i] = str2[j];
        i++;
        j++;
    }

    cpy[i] = '\0';

    return cpy;
}

char* s21_strcpy(char *str, char *str2) {
    if (sizeof(str) >= sizeof(str2)) {
        int i = 0;

        while (str2[i] != '\0') {
            str[i] = str2[i];
            i++;
        }

        str[i + 1] = '\0';
    }

    return str;
}

int s21_strchr(char *str, char c) {
    int pos, flag = 1;
    int i = 0;

    while (str[i] != '\0' && flag == 1) {
        if (str[i] == c) {
            pos = i + 1;
            flag = 0;
        }
        i++;
    }

    return pos;
}
