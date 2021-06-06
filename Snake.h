#ifndef __SNAKE__
#define __SNAKE__

#include <vector>
#include "Cell.h"
#include "Position.h"
#include "Controller.h"
using namespace std;

#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define UP 4

class Controller;


class Snake
{
  int direction;
  Position head;
  vector<Position> body;

public:
  Snake(){direction = 3; head = Position(15, 18); body.push_back(Position(15, 19)); body.push_back(Position(15, 20));body.push_back(Position(15, 21));}
  Position getHead(){return head;};
  vector<Position> getBody(){return body;};
  bool move(int d, Cell** map, Controller &controller);
  void moveHead(Cell** map, Controller &controller);
  Position changeCoordinate(int d, Position p);
  void append_body(Position pos){body.push_back(pos);}
  bool checkWall(Cell** map, int d, Position p);
  void checkItem(Cell **map, Controller &controller, Position tail);
  void setSnakeMap(Cell **map, Position tail);
  void setHead(Position pos){head = pos;}
  void setDirection(int d){direction = d;}
  int getDirection(){return direction;}
  int getLength(){return body.size();}

};

#endif
