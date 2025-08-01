TARGET = s21_matrix
CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
SRC = s21_matrix.c
TEST = ./matrix_test/*.c
LIBRARY = s21_matrix.a
S21_DECIMAL=-L. s21_matrix.a
#DEBUG =-g
SRC = $(wildcard  _*.c s21*.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
CHECK:=$(shell pkg-config --cflags --libs check)

ifeq ($(shell uname -s), Linux)
      TEST_FLAGS = -lcheck -lm -lpthread -lrt -lsubunit
else
      TEST_FLAGS = -lcheck -lm
endif



all: $(LIBRARY)

$(LIBRARY): $(SRC)
	$(CC) $(FLAGS) -c $(SRC)
	ar rc $(LIBRARY) $(OBJ)
	ranlib $(LIBRARY)
	rm -f $(OBJ)

$(TARGET) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(TARGET)


%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@


test : $(LIBRARY)
	$(CC) $(FLAGS) --coverage $(TEST) $(TEST_FLAGS) $(LIBRARY) -o test
	./test

gcov_report: clean $(LIBRARY)
	$(CC) --coverage $(FLAGS) $(TEST_FLAGS) $(TEST) s21*.c -o test $(CHECK) $(S21_DECIMAL)
	./test
	mkdir report
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html
	rm -rf *.gcda *.gcno *.out

clean:
	rm -rf *.o *.a *.gcno *.gcda test test.info *.out report


style:
	clang-format -style=google -i *.c *.h
	clang-format -style=google -i matrix_test/*.c matrix_test/*.h
	clang-format -style=google -n *.c *.h
	clang-format -style=google -n matrix_test/*.c matrix_test/*.h

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

leaks: clean test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test
