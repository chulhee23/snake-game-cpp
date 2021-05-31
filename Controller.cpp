#include <iostream>
#include <ncurses.h>
#include <ctime>
#include "Cell.h"
#include "Controller.h"

#define CLOCKS_PER_SEC 1000

const int MAP_X = 21;
const int MAP_Y = 43;
const float tick = 0.5;
const int EMPTY = 0;
const int WALL = 1;
const int IMMUNE_WALL = 2;
const int SNAKE_HEAD = 3;
const int SNAKE_BODY = 4;
const int GROW_ITEM = 5;
const int POISON_ITEM = 6;
const int GATE = 7;

const int CLR_EMPTY = EMPTY;
const int CLR_WALL = WALL;
const int CLR_IMMUNE_WALL = IMMUNE_WALL;
const int CLR_SNAKE_HEAD = SNAKE_HEAD;
const int CLR_SNAKE_BODY = SNAKE_BODY;
const int CLR_POISON_ITEM = POISON_ITEM;
const int CLR_GROW_ITEM = GROW_ITEM;
const int CLR_GATE = GATE;

using namespace std;



void Controller::manageItems(Cell **map){
  clock_t roundTime = clock();

  for (int i = 0; i < items.size(); i++)
  {
    Position pos = items[i];
    int tmp = (int)(roundTime - map[pos.row][pos.col].getCreatedAt()) / CLOCKS_PER_SEC;
    if (tmp > 5)
    {
      map[pos.row][pos.col].setValue(EMPTY);
      items.erase(items.begin() + i);
      i--;
    }

    // item create
  }

  while (items.size() < 2)
  {
    while(items.size() < 3){
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
}

void Controller::snakemapRefresh(Cell **map, WINDOW *snake_map)
{
  for (int i = 0; i < MAP_X; i++)
  {
    for (int j = 0; j < MAP_Y; j++)
    {
      Position pos(i, j);
      int cellStatus = map[i][j].getValue();
      switch (cellStatus)
      {
      case EMPTY:
        // 빈 공간
        wattron(snake_map, COLOR_PAIR(CLR_EMPTY));
        mvwprintw(snake_map, i, j, " ");
        wattroff(snake_map, COLOR_PAIR(CLR_EMPTY));
        break;
      case WALL:
        wattron(snake_map, COLOR_PAIR(CLR_WALL));
        mvwprintw(snake_map, i, j, "#");
        wattroff(snake_map, COLOR_PAIR(CLR_WALL));
        walls.push_back(pos);

        break;

      case IMMUNE_WALL:
        wattron(snake_map, COLOR_PAIR(CLR_IMMUNE_WALL));
        mvwprintw(snake_map, i, j, "I");
        wattroff(snake_map, COLOR_PAIR(CLR_IMMUNE_WALL));
        break;

      case SNAKE_HEAD:
        // snake head
        wattron(snake_map, COLOR_PAIR(CLR_SNAKE_HEAD));
        mvwprintw(snake_map, i, j, " ");
        wattroff(snake_map, COLOR_PAIR(CLR_SNAKE_HEAD));
        break;

      case SNAKE_BODY:
        // snake body
        wattron(snake_map, COLOR_PAIR(CLR_SNAKE_BODY));
        mvwprintw(snake_map, i, j, " ");
        wattroff(snake_map, COLOR_PAIR(CLR_SNAKE_BODY));
        // 방향에 따라서 바로 고정

        break;
      case GROW_ITEM:
        wattron(snake_map, COLOR_PAIR(CLR_GROW_ITEM));
        mvwprintw(snake_map, i, j, " ");
        wattroff(snake_map, COLOR_PAIR(CLR_GROW_ITEM));
        break;
      case POISON_ITEM:
        wattron(snake_map, COLOR_PAIR(CLR_POISON_ITEM));
        mvwprintw(snake_map, i, j, " ");
        wattroff(snake_map, COLOR_PAIR(CLR_POISON_ITEM));
        break;
      case GATE:
        wattron(snake_map, COLOR_PAIR(CLR_GATE));
        mvwprintw(snake_map, i, j, " ");
        wattroff(snake_map, COLOR_PAIR(CLR_GATE));
        break;
      default:
        // throw exception
        break;
      }
    }
  }
}
