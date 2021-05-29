
#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include <ctime>

#include "Cell.h"
#include "Snake.h"

#define MAP_X 21
#define MAP_Y 43

const float tick = 0.5;
const int EMPTY = 0;
const int WALL = 1;
const int IMMUNE_WALL = 2;

const int GROW_ITEM = 5;
const int POISON_ITEM = 6;
const int GATE = 7;

const int CLR_EMPTY = CLR_EMPTY;
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
        wattron(snake_map, COLOR_PAIR(CLR_EMPTY));
        mvwprintw(snake_map, i, j, " ");
        wattroff(snake_map, COLOR_PAIR(CLR_EMPTY));
        break;
      case WALL:
        wattron(snake_map, COLOR_PAIR(CLR_WALL));
        mvwprintw(snake_map, i, j, " ");
        wattroff(snake_map, COLOR_PAIR(CLR_WALL));
        controller.walls.push_back(pos);

        break;

      case IMMUNE_WALL:
        wattron(snake_map, COLOR_PAIR(CLR_IMMUNE_WALL));
        mvwprintw(snake_map, i, j, " ");
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
          mvwprintw(snake_map, i, j, " ");
          wattroff(snake_map, COLOR_PAIR(CLR_GROW_ITEM));
        break;
      case POISON_ITEM:
          wattron(snake_map, COLOR_PAIR(CLR_POISON_ITEM));
          mvwprintw(snake_map, i, j, " ");
          wattroff(snake_map, COLOR_PAIR(CLR_POISON_ITEM));
        break;
      case GATE:
        wattron(snake_map, COLOR_PAIR(CLR_POISON_ITEM));
        mvwprintw(snake_map, i, j, " ");
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
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2}};

  setlocale(LC_ALL, "");
  addch(ACS_LTEE);
  addch(ACS_RTEE);
  addch(ACS_HLINE);
  initscr();
  start_color();
  init_pair(CLR_EMPTY, COLOR_BLACK, COLOR_BLACK);
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
  bool duringGame = true;
  int ch, d = 0;

  keypad(stdscr, TRUE);
  timeout(500);
  
  while (duringGame)
  {
    long double duration = 0;

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
    snake.move(d);
    // cout << d << endl;
    // item 관리 ===============================================
    // destroy item after 5 sec
    for(int i = 0; i < controller.items.size(); i++){
      Position pos = controller.items[i];
      
      double leftTime = (clock() - map[pos.row][pos.col].getCreatedAt()) / CLOCKS_PER_SEC;

      if (leftTime > 5){
        map[pos.row][pos.col].setValue(0);
        map[pos.row][pos.col].setValue(0);
        controller.items.erase(controller.items.begin() + i);
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
      position.row = row; position.col = col;
      controller.items.push_back(position);

      map[row][col].setValue(itemType);
      map[row][col].setCreatedAt(clock());

    
    // item 관리 끝 ===============================================

    // gate open ===============
    if ((clock() - start) / (double)CLOCKS_PER_SEC > 5)
    {
      // gate_open
      cout << "testset" ;
      Position gate_candidate = controller.walls[rand() % controller.walls.size()];
    }
    // controller.walls.sample
    // if(0){
      
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
