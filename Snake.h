#ifndef __SNAKE__
#define __SNAKE__

#include <vector>
#include "Cell.h"
#include "Position.h"
#include "Controller.h"
using namespace std;

class Snake
{
  int direction;
  Position head;
  vector<Position> body;

public:
  Snake(){direction = 3; head = Position(15, 18); body.push_back(Position(15, 19)); body.push_back(Position(15, 20));}

  bool move(int d, Cell** map, Controller& controller);
  void moveHead(Cell** map, vector<Position>& gates);
  Position changeCoordinate(int d, Position p);
  void append_body(Position pos){body.push_back(pos);}
  bool checkWall(Cell** map, int d, Position p);
  void checkItem(Cell** map, vector<Position>& items, Position tail);
  void setSnakeMap(Cell** map, Position tail);
  void setHead(Position pos){head = pos;}
  void setDirection(int d){direction = d;}
  int getLength(){return body.size();}

};

#endif
