CXX = g++
CXXFLAGS = -Wall -g -std=c++11

main: main.o Numero.o
	$(CXX) $(CXXFLAGS) -o main main.o Numero.o

main.o: main.cpp Numero.o
	$(CXX) $(CXXFLAGS) -c main.cpp
	
Numero.o: Numero.h