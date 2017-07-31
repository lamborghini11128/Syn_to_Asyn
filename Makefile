all: Cycle.h Cycle_list.h find_cycle.cpp main.cpp DG.h DG.cpp
	g++ -c DG.h Cycle.h Cycle_list.h find_cycle.cpp
	g++ -c -g -std=c++11 DG.h DG.cpp
	g++ -c -g -std=c++11 main.cpp 
	g++ -o syn_to_asyn main.o DG.o find_cycle.o 

clean:
	rm -f *.o 
