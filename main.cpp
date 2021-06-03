
#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include <ctime>
#include <chrono>
#include <thread>

#include "Cell.h"
#include "Snake.h"
#include "Position.h"
#include "Controller.h"

#define CLOCKS_PER_SEC 1000

// CLOCKS_PER_SEC 이 잘못 불러짐..... 1000000


const int MAP_X = 21;
const int MAP_Y = 43;

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

const int MAX_SNAKE_LENGTH = 10;
const int GOAL_ITEM = 5;
const int GOAL_POISON_ITEM = 2;
const int GOAL_GATE = 1;

using namespace std;

int main(int argc, char const *argv[])
{
  nodelay(stdscr, FALSE); //blocking key input at screen
  int ch1 = getch();


  if(ch1 == 1){

  } else {
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
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 4, 4, 4, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
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
  init_pair(CLR_WALL, COLOR_BLACK, COLOR_WHITE);
  init_pair(CLR_IMMUNE_WALL, COLOR_WHITE, COLOR_RED);
  init_pair(CLR_SNAKE_HEAD, COLOR_WHITE, COLOR_BLUE);
  init_pair(CLR_SNAKE_BODY, COLOR_WHITE, COLOR_CYAN);

  init_pair(CLR_GROW_ITEM, COLOR_WHITE, COLOR_GREEN);
  init_pair(CLR_POISON_ITEM, COLOR_WHITE, COLOR_MAGENTA);
  init_pair(CLR_GATE, COLOR_BLACK, COLOR_YELLOW);

  border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  WINDOW *snake_map;

  snake_map = newwin(MAP_X, MAP_Y, 3, 3);

  wborder(snake_map, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

  mvprintw(1, 1, "SNAKE GAME");
  
  // score board =======
  WINDOW *score_board;
  score_board = newwin(15, 40, 3, MAP_Y + 4);
  mvwprintw(score_board, 1, 2, "SCORE BOARD");
  wborder(score_board, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  wbkgd(score_board, COLOR_PAIR(CLR_WALL));
  

  WINDOW *mission_board;
  mission_board = newwin(15, 40, 20, MAP_Y + 4);
  mvwprintw(mission_board, 1, 2, "MISSION BOARD");
  wbkgd(mission_board, COLOR_PAIR(CLR_WALL));
  wborder(mission_board, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  mvwprintw(snake_map, 18, 48, "#");
  

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
  Controller controller;

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
  curs_set(0);
  noecho();
  while(true){
    while (duringGame)
    {
      clock_t roundTime = clock();
      int gameTime = (int)(roundTime - gameStartTime) / CLOCKS_PER_SEC;
      ch = getch();
      if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_RIGHT || ch == KEY_LEFT)
      {
        std::this_thread::sleep_for(std::chrono::milliseconds(500 - (clock() - roundTime)));
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
      snake.move(d, map, controller.items);
      // duringGame = snake.move(d, map, controller.items);

      // item 관리 ===============================================
      controller.manageItems(map);

      // gate open =======================================
      
      
      // if (snake.getLength() > 5)

      if (gameTime > 3)
      {
        if ( controller.gateOpen == false)
        {
          // gate_open
          controller.openGate(map);
        } else {
          controller.closeGate(map);  
        }
      }

      // gate end ================
      controller.snakemapRefresh(map, snake_map);
      wrefresh(snake_map);
      
      mvwprintw(score_board, 2, 2, "B :    / 10");
      mvwprintw(score_board, 2, 5, to_string(snake.getLength()).c_str());
      mvwprintw(score_board, 3, 2, "+ : ");
      mvwprintw(score_board, 3, 5, to_string(controller.ateGrowItemCount).c_str());
      mvwprintw(score_board, 4, 2, "- : ");
      mvwprintw(score_board, 4, 5, to_string(controller.atePoisonItemCount).c_str());
      mvwprintw(score_board, 5, 2, "G : ");
      mvwprintw(score_board, 5, 5, to_string(controller.useGateCount).c_str());
      mvwprintw(score_board, 6, 2, "PLAY_TIME : ");
      mvwprintw(score_board, 6, 12, to_string((int)(clock() - gameStartTime) / CLOCKS_PER_SEC).c_str());
      
      
      mvwprintw(mission_board, 2, 2, ("B :" + to_string(MAX_SNAKE_LENGTH) + " ( )").c_str());
      mvwprintw(mission_board, 3, 2, ("+ :" + to_string(GOAL_ITEM) + " ( )").c_str());
      mvwprintw(mission_board, 4, 2, ("- :" + to_string(GOAL_POISON_ITEM) + " ( )").c_str());
      mvwprintw(mission_board, 5, 2, ("G :" + to_string(GOAL_GATE) + " ( )").c_str());
      

      if (snake.getLength() >= MAX_SNAKE_LENGTH){
        mvwprintw(mission_board, 2, 2, ("B :" + to_string(MAX_SNAKE_LENGTH) + " (V)").c_str());
      }
      if (controller.ateGrowItemCount >= GOAL_ITEM){
        mvwprintw(mission_board, 3, 2, ("+ :" + to_string(GOAL_ITEM) + " (V)").c_str());
      }
      if (controller.atePoisonItemCount >= GOAL_POISON_ITEM){
        mvwprintw(mission_board, 4, 2, ("- :" + to_string(MAX_SNAKE_LENGTH) + " (V)").c_str());
      }
      if (controller.useGateCount >= GOAL_GATE){
        mvwprintw(mission_board, 5, 2, ("G :" + to_string(MAX_SNAKE_LENGTH) + " (V)").c_str());
      }


      duringGame = controller.isGameOver(true);


      wrefresh(score_board);
      wrefresh(mission_board);

      flushinp();

      // 뱀 길이 마지막 측정?
      // if(duringGame){
        // duringGame = !isGameOver();
      // }

    }

    getch();
    endwin();

  }

  }


  

  return 0;
  }
