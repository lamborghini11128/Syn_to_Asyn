all: Cycle.h Cycle_list.h find_cycle.cpp main.cpp DG.h DG.cpp module.h
	g++ -c DG.h Cycle.h Cycle_list.h find_cycle.cpp
	g++ -c DG.h DG.cpp
	g++ -c module.h
	g++ -c main.cpp 
	g++ -o syn_to_asyn main.o DG.o find_cycle.o

clean:
	rm -f *.o 
