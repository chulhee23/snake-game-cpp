#ifndef __CELL__
#define __CELL__

#include <string>
#include <ctime>

using namespace std;

class Cell{
protected:
  int value;
  double createdAt;

public:
  Cell(int v = 0){value = v;};

  void setValue(int v){value = v;}
  int getValue(){return value;}
  void setCreatedAt(clock_t time){createdAt = (double)time;}
  clock_t getCreatedAt() const;
  
};

class Wall: public Cell {
  int status;

public:
  Wall(int value = 1);
  int getStatus() { return status; }
};

#endif