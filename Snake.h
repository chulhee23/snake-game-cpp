#ifndef __SNAKE__
#define __SNAKE__

#include <vector>

using namespace std;

struct Position
{
  int x, y;
};


class Snake
{
  // 1 : right
  // 2 : down
  // 3 : left
  // 4 : up
  
  int direction;
  Position head;
  vector<Position> body;

public:
  void move(int d);
  void setHead(Position pos){head = pos;}
  int getLength(){return body.size();}

};

#endif
