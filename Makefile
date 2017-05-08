all: main.cpp DG.h DG.cpp 
	g++ -c DG.h DG.cpp
	g++ -c main.cpp
	g++ -o syn_to_asyn main.o DG.o

clean:
	rm -f *.o 
