CC = g++

all:
	$(CC) -std=c++11 -o snakeMap snakeMap.cpp -lncursesw

mac:
	$(CC) -std=c++11 -o snakeMap snakeMap.cpp -lncurses


main:
	$(CC) -o main.out main.cpp


clean:
	rm -f *.o