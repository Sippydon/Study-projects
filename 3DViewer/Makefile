CC = gcc
CFLAGS = -Werror -Wextra -Wall -std=c11
SOURCES =
LIBRARY =
OBJ_PROJECT =
TESTS =
UNAME = $(shell uname -s)
SOURCES = parser/parser.c athenian/athen.c
TESTS = $(wildcard parser/tests/*.c athenian/tests/*.c test.c)

ifeq ($(UNAME), Linux)
	LDFLAGS = -lcheck -lm -lrt -lpthread -lsubunit
	OPEN_CM = xdg-open
endif
ifeq ($(UNAME), Darwin)
	LDFLAGS = -lcheck -lm
	OPEN_CM = open
endif

.PHONY: all dvi dist

all: clean install

install: $(LIBRARY)
	mkdir build
	qmake -o build
	make -C build

uninstall:
	rm -rf build

test:$(TESTS) $(SOURCES)
	$(CC) $(CFLAGS) $(TESTS) $(SOURCES) $(LDFLAGS) -o test `pkg-config --cflags --libs check`
	./test

add_coverage:
	$(eval CFLAGS += --coverage)

gcov_report:
	$(CC) $(CFLAGS) --coverage $(SOURCES) $(TESTS) $(LDFLAGS) -o ./test
	./test
	mkdir report
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html
	rm -rf *.gcda *.gcno *.out

clean:
	rm -rf build
	rm -rf report
	rm -rf *.a *.o *.out *.info *.html *.gcno *.gcov *.gcda *.gch *.tgz *.css .clang_format src test
	cd parser; make clean

dvi:
	$(OPEN_CM) dvi/dvi.html

dist: clean
	mkdir dist_3d_viewer/
	cp Makefile $(SOURCES) $(HEADERS) -r parser/ QtGifImage/ dist_3d_viewer/
	tar -czvf s21_smartcalc.tgz ../src
	rm -rf dist_3d_viewer/

valgrind: test
	cd parser; make leaks
style:
	find . -name "*.cpp" -or -name "*.h" -or -name "*.c" | xargs clang-format -n
	cd parser; make style

edit_style:
	find . -name "*.cpp" -or -name "*.h" -or -name "*.c" | xargs clang-format -i
	cd parser; make reformat_code
