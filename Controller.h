#ifndef __CONTROLLER__
#define __CONTROLLER__
#include <vector>
#include "Position.h"
#include "Cell.h"

using namespace std;

class Controller
{
public:
  vector<Position> items;
  vector<Position> walls;

  Position gates;

  void manageItems(Cell **map);
};

#endif