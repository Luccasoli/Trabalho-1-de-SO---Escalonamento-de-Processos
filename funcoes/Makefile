CXX = g++
CXXFLAGS = -Wall -g

main: main.o Numero.o
	$(CXX) $(CXXFLAGS) -o main main.o Numero.o

main.o: main.cpp Numero.o
	$(CXX) $(CXXFLAGS) -c main.cpp
	
Numero.o: Numero.h