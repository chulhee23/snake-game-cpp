#include <iostream>
#include <ctime>
#include "Cell.h"
#include "Controller.h"

#define CLOCKS_PER_SEC 1000

extern int EMPTY;
extern int WALL;
extern int IMMUNE_WALL;
extern int SNAKE_HEAD;
extern int SNAKE_BODY;
extern int GROW_ITEM;
extern int POISON_ITEM;
extern int GATE;

extern int MAP_X;
extern int MAP_Y;

using namespace std;


void Controller::manageItems(Cell **map){
  clock_t roundTime = clock();

  for (int i = 0; i < items.size(); i++)
  {
    Position pos = items[i];
    double tmp = (double)(roundTime - map[pos.row][pos.col].getCreatedAt()) / CLOCKS_PER_SEC;
    if (tmp > 5)
    {
      map[pos.row][pos.col].setValue(EMPTY);
      items.erase(items.begin() + i);
      i--;
    }

    // item create
  }

  while (items.size() < 3)
  {
    int row;
    int col;
    do
    {
      row = rand() % MAP_X;
      col = rand() % MAP_Y;
    } while (map[row][col].getValue() != 0);

    int itemType = rand() % 2 + GROW_ITEM;
    Position position;
    position.row = row;
    position.col = col;
    items.push_back(position);

    map[row][col].setValue(itemType);
    map[row][col].setCreatedAt(roundTime);
  }
}