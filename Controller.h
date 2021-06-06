#ifndef __CONTROLLER__
#define __CONTROLLER__
#include <vector>
#include <ncurses.h>

#include "Position.h"
#include "Cell.h"
#include "Snake.h"

using namespace std;

class Controller
{
public:
  int ateGrowItemCount = 0;
  int atePoisonItemCount = 0;
  int useGateCount = 0;


  vector<Position> items;
  vector<Position> walls;
  
  vector<Position> gates;
  bool gateOpen = false;
  clock_t gateOpenAt = clock();

  void manageItems(Cell **map);
  void openGate(Cell **map);
  void closeGate(Cell **map, Snake snake);

  void snakemapRefresh(Cell **map, WINDOW *snake_map);
  bool isGameOver(bool result);
};

#endif