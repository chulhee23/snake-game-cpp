#ifndef __CONTROLLER__
#define __CONTROLLER__
#include <vector>
#include <ncurses.h>

#include "Position.h"
#include "Cell.h"

using namespace std;

class Controller
{
public:

  vector<Position> items;
  vector<Position> walls;
  
  vector<Position> gates;
  bool gateOpen = false;
  clock_t gateOpenAt = clock();

  void manageItems(Cell **map);
  void openGate(Cell **map);
  void closeGate(Cell **map);

  void snakemapRefresh(Cell **map, WINDOW *snake_map);
};

#endif