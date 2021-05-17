#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// #include "Cell.h"
// #include "Snake.h"
// #include "Position.h"

#define MAP_X 21
#define MAP_Y 21

using namespace std;

struct Position
{
  int x, y;
};


class Cell
{
protected:
  int value;

public:
  Cell(int v = 0){value = v;};

  void setValue(int v) { value = v; }
  int getValue() { return value; }
};

int main(int argc, char const *argv[])
{
  Cell cell(1);
  // Wall wall(2);

  cout << cell.getValue() << endl;
  // cout << wall.getValue() << endl;
  
  

  return 0;
}
