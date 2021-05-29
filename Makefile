CC = g++

all:
	$(CC) -std=c++11 -o snakeMap snakeMap.cpp -lncursesw

mac:
	$(CC) -std=c++11 -o snakeMap snakeMap.cpp -lncurses


main: Cell.o Snake.o
	$(CC) -o main.out main.cpp -lncursesw $^

Cell.o:
	$(CC) -c Cell.h Cell.cpp
Snake.o:
	$(CC) -c Snake.h Snake.cpp


clean:
	rm -f *.o
