#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

void test_strlen();
void test_strcmp();
void test_strcpy();
void test_strcat();
void test_strchr();

int main() {
    #if TEST == 1
        test_strlen();
    #endif
    #if TEST == 2
        test_strcmp();
    #endif
    #if TEST == 3
        test_strcpy();
    #endif
    #if TEST == 4
        test_strcat();
    #endif
    #if TEST == 5
        test_strchr();
    #endif
    return 0;
}

void test_strlen() {
    int t;
    printf("TEST STRLEN...\n");

    printf("CASE 1...\n");
    t = s21_strlen("QWERT");
    if (t == 5) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    printf("CASE 2...\n");
    t = s21_strlen("");
    if (t == 0) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    printf("CASE 3...\n");
    t = s21_strlen("1234567890");
    if (t == 10) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    printf("EXIT TEST STRLEN");
}

void test_strcmp() {
        int t;
    printf("TEST STRCMP...\n");

    printf("CASE 1...\n");
    t = s21_strcmp("QWERT", "QWERTY");
    if (t == -1) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    printf("CASE 2...\n");
    t = s21_strcmp("qwert", "qwert");
    if (t == 0) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    printf("CASE 3...\n");
    t = s21_strcmp("qwerty", "qwert");
    if (t == 1) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    printf("EXIT TEST STRCMP");
}

void test_strcpy() {
    char str1[6];
    char *str = "123456 ";
    char *str2 = "world";
    str = s21_strcpy(str1, str2);

    printf("TEST STRCPY...\n");

    printf("CASE 1...\n");
    if (s21_strcmp(str, str2)) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    printf("CASE 2...\n");
    str = s21_strcpy(str, "wo");
    if (s21_strcmp(str, str2)) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    printf("CASE 3...\n");
    str = s21_strcpy(str, " ");
    if (s21_strcmp(str, str2)) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    printf("EXIT TEST STRCPY");
}

void test_strcat() {
    char *t;

    printf("TEST STRCAT...\n");

    printf("CASE 1...\n");
    t = s21_strcat("hell", "o world!");
    if (s21_strcmp(t, "hello world!") == 0) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
    free(t);

    printf("CASE 2...\n");
    t = s21_strcat("123", "woss");
    if (s21_strcmp(t, "123woss") == 0) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
    free(t);

    printf("CASE 3...\n");
    t = s21_strcat("hello ", "5321");
    if (s21_strcmp(t, "hello 5321") == 0) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
    free(t);

    printf("EXIT TEST STRCAT");
}

void test_strchr() {
    printf("TEST STRCHR...\n");

    printf("CASE 1...\n");
    if (s21_strchr("123456", '3') == 3) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    printf("CASE 2...\n");
    if (s21_strchr("qwertyu", 'w') == 2) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    printf("CASE 3...\n");
    if (s21_strchr("qwerty", 'y') == 6) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    printf("EXIT TEST STRCHR");
}
