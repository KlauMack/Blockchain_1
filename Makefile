CXXFLAGS=  -Wall -g

all: main.o functions.o
	g++  main.o functions.o -o main

main.o: main.cpp

funkcijos.o: functions.cpp

test:	all
	./main

clean:
	rm -f *.o main result.txt