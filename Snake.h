#ifndef __SNAKE__
#define __SNAKE__

#include <vector>
#include "Cell.h"

using namespace std;

#define RIGHT 1;
#define DOWN 2;
#define LEFT 3;
#define UP 4;

struct Position
{
  Position():row(0), col(0){};
  Position(int _row, int _col) : row(_row), col(_col){};
  int row, col;
};


class Snake
{
  int direction;
  Position head;
  vector<Position> body;

public:
  Snake(){direction = 3; head = Position(15, 18); body.push_back(Position(15, 19)); body.push_back(Position(15, 20));}

  void move(int d, Cell** map);
  void append_body(Position pos){body.push_back(pos);}
  void setHead(Position pos){head = pos;}
  void setDirection(int d){direction = d;}
  int getLength(){return body.size();}

};

#endif
