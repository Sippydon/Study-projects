all: state_sort

state_sort: state_sort.c
	gcc -Wall -Werror -Wextra state_sort.c -o ../build/Quest_1

state_search: state_search.c
	gcc -Wall -Werror -Wextra state_search.c -o ../build/Quest_2

clear_state: clear_state.c
	gcc -Wall -Werror -Wextra clear_state.c -o ../build/Quest_3
run_1:
	./../build/Quest_1

run_2:
	./../build/Quest_2

run_3:
	./../build/Quest_3

clean:
	rm -rf ../build/Quest*

rebuild:
	$(MAKE) clean
	$(MAKE) all
	$(MAKE) tests

python:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extensions=c state_sort.c
	python3 ../materials/linters/cpplint.py --extensions=c state_search.c
	python3 ../materials/linters/cpplint.py --extensions=c clear_state.c
	rm CPPLINT.cfg

leaks:
	leaks -atExit -- ../build/Quest_1
	leaks -atExit -- ../build/Quest_2
	leaks -atExit -- ../build/Quest_3

tests:
	$(MAKE) python
	$(MAKE) leaks