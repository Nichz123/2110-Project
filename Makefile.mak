all: simcity

simcity: main.o InitSim.o City.o CellBlock.o Polution.o
	g++ main.o InitSim.o City.o CellBlock.o Polution.o -o simcity
	
main.o: main.cpp
	g++ -c main.cpp
	
Cellblock.o: CellBlock.cpp CellBlock.h
	g++ -c CellBlock.cpp
	
InitSim.o: InitSim.cpp InitSim.h CellBlock.h
	g++ -c InitSim.cpp
	
City.o: City.cpp City.h CellBlock.o
	g++ -c City.cpp

Polution.o: City.o Cellblock.o Polution.cpp polution.h
	g++ -c Polution.cpp
	
clean: 
	rm -rf *.o hello
