CC = gcc
CFLAG = -Wall -Wextra -Werror -std=c11
APP = smart_calc
BACKEND_FILES = stack.c polish.c calculate.c
BACKEND_FILES_O = stack.o polish.o calculate.o

GCOVFLAGS = -L. --coverage
TEST_FLAGS = -lcheck

ifeq ($(shell uname), Linux)
	TEST_FLAGS += -lpthread -lrt -lsubunit -lm
endif


all: install

build:
	mkdir build
	cd ./build/ && qmake ../ && make

install: build
	mv build/$(APP) $(HOME)/Desktop/

uninstall:
	rm -rf $(HOME)/Desktop/$(APP)
	make clean

dvi:
	open readme.html

dist:
	rm -rf Distribut_SmartCalc_v1.0/
	mkdir Distribut_SmartCalc_v1.0/
	mkdir Distribut_SmartCalc_v1.0/src
	cp Makefile *.c *.h *.pro *.cpp *.ui Distribut_SmartCalc_v1.0/src/
	tar czf Distribut_SmartCalc_v1.0.tgz Distribut_SmartCalc_v1.0/
	mv Distribut_SmartCalc_v1.0.tgz $(HOME)/Desktop/
	rm -rf Distribut_SmartCalc_v1.0/

s21_calc.a:
	$(CC) $(CFLAG) $(BACKEND_FILES) -c
	ar rc s21_calc.a $(BACKEND_FILES_O)
	rm *.o

test: s21_calc.a
	$(CC) $(CFLAG) tests.c s21_calc.a $(TEST_FLAGS) -o test
	./test


check-style:
	clang-format -n -style=google *.c
	clang-format -n -style=google *.cpp
	clang-format -n -style=google *.h


style:
	clang-format -i -style=google *.c
	clang-format -i -style=google *.cpp
	clang-format -i -style=google *.h


gcov_report: s21_calc.a test
	$(CC) $(CFLAG) tests.c $(BACKEND_FILES) s21_calc.a $(TEST_FLAGS) $(GCOVFLAGS) -o test
	./test
	lcov -t tests.c -o test.info -c -d .
	genhtml -o test_html test.info
	#open ./test_html/index.html

clean:
	rm -rf *.o *.a
	rm -rf *.gcda *.gcno *.info
	rm -rf s21_test report
	rm -rf s21_calc s21_test
	rm -rf ./build*
	rm -rf ../build
	rm -rf test
	rm -rf test_html
	rm -rf *.pro.user


rebuild: clean all
