all: main

main: data_io.o data_process.o decision.o data_stat.o main_executable_module.o
	gcc data_io.o data_process.o decision.o data_stat.o main_executable_module.o -o ../../build/Quest_3

data_io.o: ../data_libs/data_io.c ../data_libs/data_io.h
	gcc -c ../data_libs/data_io.c

data_process.o: ../data_module/data_process.c ../data_module/data_process.h
	gcc -c ../data_module/data_process.c

decision.o: ../yet_another_decision_module/decision.c ../yet_another_decision_module/decision.h
	gcc -c ../yet_another_decision_module/decision.c

data_stat.o: ../data_libs/data_stat.c
	gcc -c ../data_libs/data_stat.c

main_executable_module.o: main_executable_module.c
	gcc -c main_executable_module.c

build_with_static: data_io.o data_process.o decision.o data_stat.o main_executable_module.o
	ar rcs data_stat.a data_stat.o
	gcc data_io.o data_process.o decision.o main_executable_module.o data_stat.a -o ../../build/Quest_5

build_with_dynamic: data_io.o decision.o main_executable_module.o data_stat.o
	gcc -shared -o data_process.so -c ../data_module/data_process.c
	gcc data_io.o decision.o data_stat.o main_executable_module.o data_process.so -o ../../build/Quest_6

clean:
	rm -rf *.o *.a *.so ../../build/Q*

rebuild: 
	$(MAKE) clean
	$(MAKE) all