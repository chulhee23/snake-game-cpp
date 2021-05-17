#ifndef _CELL
#define _CELL

#include <string>
using namespace std;

class Cell{
protected:
  int value;
public:
  Cell(int value = 0);

  void setValue(int v){value = v;}
  int getValue(){return value;}
};




#endif