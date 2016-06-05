CC = g++ -std=c++11 
CFLAGS = -g -Wall -c 

all: Matrix-Calculator 

Matrix-Calculator: main.o Determinant.o Gauss.o
	$(CC) main.o Determinant.o Gauss.o -o Matrix-Calculator

main.o: main.cpp 
	$(CC) $(CFLAGS) main.cpp

Determinant.o: Determinant.cpp	Determinant.h
	$(CC) $(CFLAGS) Determinant.cpp

Gauss.o: Gauss.cpp Gauss.h
	$(CC) $(CFLAGS) Gauss.cpp

clean:
		rm *o






