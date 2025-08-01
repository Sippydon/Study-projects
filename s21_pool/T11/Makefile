COMP = gcc -Wall -Werror -Wextra

all: door_struct list_test

door_struct: dmanager_module.c door_struct.h
	$(COMP) dmanager_module.c -o ../build/Quest_1

list_test: list.h list.c list_test.c
	$(COMP) list.c list_test.c -o ../build/Quest_2

clean:
	rm ../build/Q*