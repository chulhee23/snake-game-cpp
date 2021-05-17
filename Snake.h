#ifndef _SNAKE
#define _SNAKE
#include <vector>
#include "Position.h"

using namespace std;

class Snake
{
  int direction;
  Position head;
  vector<Position> body;

public:
  void move();
  void setHead(Position pos){head = pos;}
  int getLength(){return body.size();}

};

#endif