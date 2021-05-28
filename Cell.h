#ifndef __CELL__
#define __CELL__

#include <string>
#include <ctime>

using namespace std;

class Cell{
protected:
  int value;
  clock_t createdAt;

public:
  Cell(int v = 0){value = v;};

  void setValue(int v){value = v;}
  int getValue(){return value;}
  void setCreatedAt(int time){createdAt = time;}
  clock_t getCreatedAt() const;
  
};

class Wall: public Cell {
  int status;

public:
  Wall(int value = 1);
  int getStatus() { return status; }
};

#endif