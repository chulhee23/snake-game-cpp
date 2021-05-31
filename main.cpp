
#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include <ctime>

#include "Cell.h"
#include "Snake.h"
#include "Position.h"
#include "Controller.h"

#define CLOCKS_PER_SEC 1000
// CLOCKS_PER_SEC 이 잘못 불러짐..... 1000000

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

const int CLR_EMPTY = CLR_EMPTY;
const int CLR_WALL = WALL;
const int CLR_IMMUNE_WALL = IMMUNE_WALL;
const int CLR_SNAKE_HEAD = SNAKE_HEAD;
const int CLR_SNAKE_BODY = SNAKE_BODY;
const int CLR_POISON_ITEM = POISON_ITEM;
const int CLR_GROW_ITEM = GROW_ITEM;
const int CLR_GATE = GATE;

using namespace std;


Controller controller;


int main(int argc, char const *argv[])
{
  // map 설정 시작 ===================
  srand(time(NULL));

  const int init_map[MAP_X][MAP_Y] =
      {{2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 4, 4, 4, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2}};

  setlocale(LC_ALL, "");
  addch(ACS_LTEE);
  addch(ACS_RTEE);
  addch(ACS_HLINE);
  initscr();
  start_color();
  init_pair(CLR_EMPTY, COLOR_BLACK, COLOR_BLACK);
  init_pair(CLR_WALL, COLOR_BLACK, COLOR_WHITE);
  init_pair(CLR_IMMUNE_WALL, COLOR_WHITE, COLOR_RED);
  init_pair(CLR_SNAKE_HEAD, COLOR_WHITE, COLOR_BLUE);
  init_pair(CLR_SNAKE_BODY, COLOR_WHITE, COLOR_CYAN);

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
  controller.snakemapRefresh(map, snake_map);

  // map 설정 종료 ===================

  // Game Start

  clock_t gameStartTime = clock();
  bool duringGame = true;
  int ch, d = 0;

  keypad(stdscr, TRUE);
  timeout(500);

  while (duringGame)
  {
    long double duration = 0;
    clock_t roundTime = clock();

    ch = getch();
    if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_RIGHT || ch == KEY_LEFT)
    {
      switch (ch)
      {
      case KEY_UP:
        d = UP;
        break;
      case KEY_DOWN:
        d = DOWN;
        break;
      case KEY_RIGHT:
        d = RIGHT;
        break;
      case KEY_LEFT:
        d = LEFT;
        break;
      }
    }

    snake.move(d, map);

    // item 관리 ===============================================
    controller.manageItems(map);
    // item 관리 끝 ===============================================

    // gate open =======================================
    
    
    // if (snake.getLength() > 5)
    double tmp = (double)(clock() - gameStartTime) / CLOCKS_PER_SEC;
    if (tmp > 3)
    {
      // gate_open
      cout << "gate open!!!!!!!!!" << endl;
      // Position gate_candidate = controller.walls[rand() % controller.walls.size()];

    }
    // controller.walls.sample
    // if(0){

    //   map[gate_candidate.x][gate_candidate.y].setValue(GATE);
    // }

    // gate end ================
    controller.snakemapRefresh(map, snake_map);
    wrefresh(snake_map);
  }

  getch();
  endwin();

  return 0;
  }
