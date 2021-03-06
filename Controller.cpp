#include <iostream>
#include <ncurses.h>
#include <ctime>
#include "Cell.h"
#include "Controller.h"
#include "constants.h"


using namespace constants;
using namespace std;



void Controller::manageItems(Cell **map){
  clock_t roundTime = clock();

  for (int i = 0; i < items.size(); i++)
  {
    Position pos = items[i];
    int tmp = (int)(roundTime - map[pos.row][pos.col].getCreatedAt()) / CLOCKS_PER_SEC;
    if (tmp > 10)
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

void Controller::openGate(Cell **map){
  // choose 2 walls from all walls

  srand(time(0));
  int wall_size = walls.size();

  int first = rand() % (wall_size - 1);
  int second = rand() % (wall_size);

  if (second == first){
    second++;
  }

  Position gate1 = walls[first];
  Position gate2 = walls[second];

  map[gate1.row][gate1.col].setValue(GATE);
  map[gate2.row][gate2.col].setValue(GATE);

  gates.push_back(gate1);
  gates.push_back(gate2);

  gateOpen = true;
  gateOpenAt = clock();
}

void Controller::closeGate(Cell **map, Snake &snake){
  double gateOpened = (double)(clock() - gateOpenAt) / CLOCKS_PER_SEC;
  for (auto it = gates.begin(); it != gates.end(); it++)
  {
    
    if ((*it).row == snake.getHead().row && (*it).col == snake.getHead().col){
      return;
    }
    else {
      vector<Position> body = snake.getBody();
      for(auto body_it = body.begin(); body_it != body.end(); body_it++) {
        if ((*body_it).row == (*it).row && (*body_it).col == (*it).col) {
          return;
        }
      }
    }

  }
  
  if (gateOpened > 10)
  {
    for(auto it = gates.begin(); it != gates.end(); it++) {
      map[(*it).row][(*it).col].setValue(WALL);
    }
    gates.clear();
    gateOpen = false;
  }
}

void Controller::snakemapRefresh(Cell **map, WINDOW *snake_map)
{
  walls.clear();
  for (int i = 0; i < MAP_X; i++)
  {
    for (int j = 0; j < MAP_Y; j++)
    {
      int cellStatus = map[i][j].getValue();
      Position pos(i, j);
      switch (cellStatus)
      {
      case EMPTY:
        // ??? ??????
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
        // ????????? ????????? ?????? ??????

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
        mvwprintw(snake_map, i, j, "@");
        wattroff(snake_map, COLOR_PAIR(CLR_GATE));
        break;
      default:
        // throw exception
        break;
      }
    }
  }
}


bool Controller::isGameOver(bool result){
  return result;
}
