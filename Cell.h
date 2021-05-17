#ifndef __CELL__
#define __CELL__

#include <string>

using namespace std;

class Cell{
protected:
  int value;
public:
  Cell(int v = 0){value = v;};

  void setValue(int v){value = v;}
  int getValue(){return value;}
  
};

class Wall: public Cell {
  int status;

public:
  Wall(int value = 1);
  int getStatus() { return status; }
};

#endif