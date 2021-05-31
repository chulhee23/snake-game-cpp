CC = g++

all:
	$(CC) -std=c++11 -o snakeMap snakeMap.cpp -lncursesw

mac:
	$(CC) -std=c++11 -o snakeMap snakeMap.cpp -lncurses


main: Cell.o Snake.o
	$(CC) -o main.out main.cpp -lncursesw $^

mac_main: Cell.o Snake.o Controller.o
	$(CC) -std=c++11 -o main.out main.cpp -lncurses $^

Controller.o:
	$(CC) -c Controller.h Controller.cpp

Cell.o:
	$(CC) -c Cell.h Cell.cpp


Snake.o:
	$(CC) -c Snake.h Snake.cpp Position.h


clean:
	rm -f *.o
