FLAGS = -Wall -Werror -Wextra

all: strlen_tests strcmp_tests strcpy_tests strcat_tests strchr_tests

strlen_tests: s21_string_test.c s21_string.h s21_string.c
	gcc $(FLAGS) -DTEST=1 -c s21_string_test.c s21_string.c
	gcc s21_string_test.o s21_string.o -o ../build/Quest_1

strcmp_tests: s21_string_test.c s21_string.h s21_string.c
	gcc $(FLAGS) -DTEST=2 -c s21_string_test.c s21_string.c
	gcc s21_string_test.o s21_string.o -o ../build/Quest_2

strcpy_tests: s21_string_test.c s21_string.h s21_string.c
	gcc $(FLAGS) -DTEST=3 -c s21_string_test.c s21_string.c
	gcc s21_string_test.o s21_string.o -o ../build/Quest_3

strcat_tests: s21_string_test.c s21_string.h s21_string.c
	gcc $(FLAGS) -DTEST=4 -c s21_string_test.c s21_string.c
	gcc s21_string_test.o s21_string.o -o ../build/Quest_4

strchr_tests: s21_string_test.c s21_string.h s21_string.c
	gcc $(FLAGS) -DTEST=5 -c s21_string_test.c s21_string.c
	gcc s21_string_test.o s21_string.o -o ../build/Quest_5

clean:
	rm -rf *.o ../build/Quest_*

rebuild:
	$(MAKE) clean
	$(MAKE)