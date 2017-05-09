all: main.cpp DG.h DG.cpp module.h
	g++ -c DG.h DG.cpp
	g++ -c module.h
	g++ -c main.cpp
	g++ -o syn_to_asyn main.o DG.o

clean:
	rm -f *.o 
