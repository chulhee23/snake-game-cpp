CC = gcc
CXX = g++
CXXFLAGS = -Wall -std=c++11
INCLUDES =
LFLAGS =
LIBS = -lncurses
SRCS = main.cpp Controller.cpp Snake.cpp Cell.cpp snake_game.cpp
OBJS = $(SRCS:.cpp=.o)
MAIN = main.out

.PHONY : depend clean

all : $(MAIN)
	rm -rf *.o

$(MAIN) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

%o : %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES)  -c $<  -o $@

clean :
	$(RM) *.o *~ $(MAIN)
