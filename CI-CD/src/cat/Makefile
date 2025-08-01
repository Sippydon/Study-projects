all: s21_cat

s21_cat: cat_func.o cat_parser.o cat_main.o
	gcc -o s21_cat *.o

cat_func.o: cat_func.c cat_func.h cat_flags.h
	gcc -c cat_func.c

cat_parser.o: cat_parser.c cat_parser.h
	gcc -c cat_parser.c

cat_main.o: cat_main.c
	gcc -c cat_main.c

rebuild: s21_cat

clean:
	rm -rf *.o s21_cat