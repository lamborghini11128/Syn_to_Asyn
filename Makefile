all: Cycle.h Cycle_list.h find_cycle.cpp main.cpp DG.h DG.cpp module.h module.cpp
	g++ -c DG.h Cycle.h Cycle_list.h find_cycle.cpp
	g++ -c DG.h DG.cpp
	g++ -c -std=c++11 module.h module.cpp
	g++ -c main.cpp 
	g++ -o syn_to_asyn main.o DG.o find_cycle.o module.o

clean:
	rm -f *.o 
