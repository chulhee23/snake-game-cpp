#ifndef __CELL__
#define __CELL__

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
  void setCreatedAt(clock_t time){createdAt = time;}
  clock_t getCreatedAt() const;
  
};

#endif