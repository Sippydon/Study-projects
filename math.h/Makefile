CC = gcc -Wall -Werror -Wextra -std=c11 -g
UNAME:=$(shell uname -s)

ifeq ($(UNAME),Linux)
  LDFLAGS=-lcheck_pic -lsubunit -lm -lrt -lpthread  
  OPEN_CM=xdg-open
endif
ifeq ($(UNAME),Darwin)
  LDFLAGS=-lcheck -lm  
  OPEN_CM=open
endif

all: s21_math.a

s21_math.a: object
	ar rcs s21_math.a *.o
	ranlib s21_math.a
	rm *.o
object:
	$(CC) -c s21_*.c
clean:
	rm -rf *.o *.gcda *.gcno *.a *.out *.info *.dSYM report test

test: clean	s21_math.a
	$(CC) test.c  -L. s21_math.a $(LDFLAGS) -lpthread -o test
	./test

gcov_report: s21_math.a
	$(CC) --coverage *.c s21_math.a -L. s21_math.a -lcheck -lm -lpthread -o ./test.out
	./test.out
	mkdir report
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html
	rm -rf *.gcda *.gcno *.out

rebuild:
	$(MAKE) clean
	$(MAKE) test

style:
	clang-format -style=Google -n *.c *.h

leaks: clean test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test
