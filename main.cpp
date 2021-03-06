#include <iostream>
#include <vector>
#include <ncurses.h>
#include <ctime>
#include <chrono>
#include <thread>

#include "Cell.h"
#include "Snake.h"
#include "Position.h"
#include "Controller.h"
#include "snake_game.h"
#include "constants.h"

using namespace constants;
using namespace std;


int main(int argc, char const *argv[])
{
  setlocale(LC_ALL, "");
  srand(time(NULL));
  int stageNumber = -1;
  int gameMode = INITIAL_MODE;
  while(true){
    stageNumber = selectGame(gameMode);
    switch (stageNumber)
    {
    case 4:
      // end game
      endwin();
      return 0;

    default:
      break;
    }

    int MAX_SNAKE_LENGTH = goals[stageNumber][0];
    int GOAL_ITEM = goals[stageNumber][1];
    int GOAL_POISON_ITEM = goals[stageNumber][2];
    int GOAL_GATE = goals[stageNumber][3];

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
        map[i][j].setValue(maps[stageNumber][i][j]);
      }
    }

    Controller controller;

    // snake ??? ?????? ?????? ??????
    Snake snake;
    refresh();
    controller.snakemapRefresh(map, snake_map);

    // map ?????? ?????? ===================

    // Game Start

    clock_t gameStartTime = clock();
    bool duringGame = true;
    int ch = 0;

    keypad(stdscr, TRUE);
    timeout(WAIT_SECONDS);
    curs_set(0);
    noecho();

    while (duringGame)
    {
      int d = 0;
      clock_t roundTime = clock();
      int gameTime = (int)(roundTime - gameStartTime) / CLOCKS_PER_SEC;
      ch = getch();
      if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_RIGHT || ch == KEY_LEFT)
      {
        std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_SECONDS - (clock() - roundTime)));
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
        default:
          break;
        }
      }
      // snake.move(d, map, controller.items);
      bool moveResult = snake.move(d, map, controller);

      // item ?????? ===============================================
      controller.manageItems(map);

      // gate open =======================================

      // if (snake.getLength() > 5)

      if (gameTime > 10)
      {
        if (controller.gateOpen == false)
        {
          // gate_open
          controller.openGate(map);
        }
        else
        {
          controller.closeGate(map, snake);
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

      mvwprintw(mission_board, 2, 2, ("B :" + to_string(MAX_SNAKE_LENGTH) + " ( )").c_str());
      mvwprintw(mission_board, 3, 2, ("+ :" + to_string(GOAL_ITEM) + " ( )").c_str());
      mvwprintw(mission_board, 4, 2, ("- :" + to_string(GOAL_POISON_ITEM) + " ( )").c_str());
      mvwprintw(mission_board, 5, 2, ("G :" + to_string(GOAL_GATE) + " ( )").c_str());

      if (snake.getLength() >= MAX_SNAKE_LENGTH)
      {
        mvwprintw(mission_board, 2, 2, ("B :" + to_string(MAX_SNAKE_LENGTH) + " (V)").c_str());
      }
      if (controller.ateGrowItemCount >= GOAL_ITEM)
      {
        mvwprintw(mission_board, 3, 2, ("+ :" + to_string(GOAL_ITEM) + " (V)").c_str());
      }
      if (controller.atePoisonItemCount >= GOAL_POISON_ITEM)
      {
        mvwprintw(mission_board, 4, 2, ("- :" + to_string(GOAL_POISON_ITEM) + " (V)").c_str());
      }
      if (controller.useGateCount >= GOAL_GATE)
      {
        mvwprintw(mission_board, 5, 2, ("G :" + to_string(GOAL_GATE) + " (V)").c_str());
      }

      duringGame = controller.isGameOver(moveResult);
      if(duringGame == false){
        gameMode = FAILED;
      }
      if (snake.getLength() >= MAX_SNAKE_LENGTH && controller.ateGrowItemCount >= GOAL_ITEM && controller.atePoisonItemCount >= GOAL_POISON_ITEM&& controller.useGateCount >= GOAL_GATE)
      {
        duringGame = false;
        gameMode = COMPLETE;
      }

      wrefresh(score_board);
      wrefresh(mission_board);

      flushinp();

      // ??? ?????? ????????? ???????
      // if(duringGame){
      // duringGame = !isGameOver();
      // }
    }

    getch();
    endwin();
    // while true end
  }

  // map ?????? ?????? ===================

  return 0;
}
