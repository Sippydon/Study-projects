all: s21_grep

s21_grep: grep_func.o grep_parser.o grep_main.o
	gcc -o s21_grep *.o

grep_func.o: grep_func.c grep_func.h flags.h
	gcc -c grep_func.c

grep_parser.o: grep_parser.c grep_parser.h
	gcc -c grep_parser.c

grep_main.o: grep_main.c
	gcc -c grep_main.c

rebuild: s21_grep

clean:
	rm -rf *.o s21_grep