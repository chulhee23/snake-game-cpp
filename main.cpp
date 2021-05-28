
#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include <ctime>

#include "Cell.h"
#include "Snake.h"

#define MAP_X 21
#define MAP_Y 31

const float tick = 0.5;
const int EMPTY = 0;
const int WALL = 1;
const int IMMUNE_WALL = 2;

const int GROW_ITEM = 5;
const int POISON_ITEM = 6;
const int GATE = 7;


const int CLR_WALL = WALL;
const int CLR_IMMUNE_WALL = IMMUNE_WALL;
const int CLR_POISON_ITEM = POISON_ITEM;
const int CLR_GROW_ITEM = GROW_ITEM;
const int CLR_GATE = GATE;

using namespace std;

struct Controller {
  vector<Position> items;
  vector<Position> walls;
  
  Position inGate;
  Position outGate;
};
Controller controller;

void snakemapRefresh(Cell **map, WINDOW *snake_map)
{
  for(int i = 0; i < MAP_X; i++){
    for (int j = 0; j < MAP_Y; j++){
      Position pos(i, j);
      int cellStatus = map[i][j].getValue();
      switch (cellStatus)
      {
      case EMPTY:
        // 빈 공간
        break;
      case WALL:
        wattron(snake_map, COLOR_PAIR(CLR_WALL));
        mvwprintw(snake_map, i, j, "W");
        wattroff(snake_map, COLOR_PAIR(CLR_WALL));
        controller.walls.push_back(pos);
        
        break;

      case IMMUNE_WALL:
        wattron(snake_map, COLOR_PAIR(CLR_IMMUNE_WALL));
        mvwprintw(snake_map, i, j, "I");
        wattroff(snake_map, COLOR_PAIR(CLR_IMMUNE_WALL));
        break;

      case 3:
        // snake head
        // snake.setHead(pos);
        break;

      case 4:
        // snake body
        // snake.append_body()
        // 방향에 따라서 바로 고정
        break;
      case GROW_ITEM:
          wattron(snake_map, COLOR_PAIR(CLR_GROW_ITEM));
          mvwprintw(snake_map, i, j, "G");
          wattroff(snake_map, COLOR_PAIR(CLR_GROW_ITEM));
        break;
      case POISON_ITEM:
          wattron(snake_map, COLOR_PAIR(CLR_POISON_ITEM));
          mvwprintw(snake_map, i, j, "P");
          wattroff(snake_map, COLOR_PAIR(CLR_POISON_ITEM));
        break;
      case GATE:
        wattron(snake_map, COLOR_PAIR(CLR_POISON_ITEM));
        mvwprintw(snake_map, i, j, "P");
        wattroff(snake_map, COLOR_PAIR(CLR_POISON_ITEM));
        break;
      default:
        // throw exception
        break;
      }
    }

  }
}

int main(int argc, char const *argv[])
{
  // map 설정 시작 ===================
  srand(time(NULL));
  const int init_map[MAP_X][MAP_Y] =
      {{2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2}};

  setlocale(LC_ALL, "");

  initscr();
  start_color();
  init_pair(CLR_WALL, COLOR_WHITE, COLOR_WHITE);
  init_pair(CLR_IMMUNE_WALL, COLOR_WHITE, COLOR_RED);
  init_pair(CLR_GROW_ITEM, COLOR_WHITE, COLOR_GREEN);
  init_pair(CLR_POISON_ITEM, COLOR_WHITE, COLOR_MAGENTA);
  init_pair(CLR_GATE, COLOR_WHITE, COLOR_YELLOW);

  border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  WINDOW *snake_map;
  snake_map = newwin(MAP_X, MAP_Y, 3, 3);

  wborder(snake_map, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

  mvprintw(1, 1, "SNAKE GAME");

  Cell **map;
  map = new Cell *[MAP_X];
  for (int i = 0; i < MAP_X; i++)
  {
    map[i] = new Cell[MAP_Y];
  }

  for (int i = 0; i < MAP_X; i++)
  {
    for (int j = 0; j < MAP_Y; j++)
    {
      map[i][j].setValue(init_map[i][j]);
    }
  }

  // snake 의 경우 따로 관리
  Snake snake;
  refresh();
  snakemapRefresh(map, snake_map);

  // map 설정 종료 ===================

  clock_t start = clock();
  long double duration = 0;
  bool duringGame = true;
  int i = 0;

  while (duringGame)
  {
    
    duration = 0;
    start = clock();
    while(true)
    {
      duration = (clock() - start) / (double)CLOCKS_PER_SEC;
      if (duration > 0.5)
      {
        // check 0.5 seconds
        break;
      }

    }
    
    // item 관리 ===============================================
    for(int i = 0; i < controller.items.size(); i++){
      Position pos = controller.items[i];
      
      int leftTime = (clock() - map[pos.x][pos.y].getCreatedAt()) / (double)CLOCKS_PER_SEC;
      if (leftTime > 5){
        map[pos.x][pos.y].setValue(0);
        mvwprintw(snake_map, pos.x, pos.y, " ");

        controller.items.erase(controller.items.begin() + i);
      }
    }

    if (controller.items.size() < 3){
      int row;
      int col;
      do {
        row = rand() % MAP_X;
        col = rand() % MAP_Y;
      } while (map[row][col].getValue() != 0);

      int itemType = rand() % 2 + GROW_ITEM;
      Position position;
      position.x = row; position.y = col; 
      controller.items.push_back(position);

      map[row][col].setValue(itemType);
      map[row][col].setCreatedAt(clock());
      

    }
    // item 관리 끝 ===============================================

    // gate open ===============

    // controller.walls.sample
    // if(0){
    //   Position gate_candidate = controller.walls[rand() % controller.walls.size()];
    //   map[gate_candidate.x][gate_candidate.y].setValue(GATE);
    // }
    
    // gate end ================
    snakemapRefresh(map, snake_map);

    wrefresh(snake_map);
  }

  getch();
  endwin();

  return 0;
}
