CC = g++
FLAGS = -std=c++17 -Wall -Wextra -Werror
FUNC = s21_matrix_struct.cc s21_matrix_operations.cc s21_matrix_operators.cc
FUNC_O = s21_matrix_struct.o s21_matrix_operations.o s21_matrix_operators.o
TEST = Test/Test.cc

all: test

clean:
	rm -rf *.o report *.info *.gcda *.gcno *.gcov *.gch *.out *.a *.txt test

test: clean s21_matrix_oop.a
	$(CC) $(FLAGS) -fprofile-arcs -ftest-coverage $(TEST) s21_matrix_oop.a -lgtest -o test
	./test

s21_matrix_oop.a:
	gcc $(FLAGS) -c $(FUNC)
	ar rc s21_matrix_oop.a $(FUNC_O)
	ranlib s21_matrix_oop.a
	rm -rf *.o

gcov_report: clean
	$(CC) $(FLAGS) -fprofile-arcs -ftest-coverage $(FUNC) $(TEST) -lgtest -o test
	./test
	gcov --no-output $(TEST)
	lcov --no-external --capture --directory . --output-file coverage.info
	genhtml coverage.info -o report
	open ./report/index.html

style:
	clang-format -style=google -n *.cc *.h Test/*.cc

refactor:
	clang-format -style=google -i *.cc *.h Test/*.cc

valgrind:
	valgrind --leak-check=full -s --track-origins=yes --log-file=valgrind-out.txt ./test

.PHONY: s21_matrix_oop.a test
