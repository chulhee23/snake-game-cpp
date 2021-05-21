#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>

#include "Cell.h"
#include "Snake.h"


#define MAP_X 21
#define MAP_Y 31

const int CLR_YB = 1;
const int CLR_WR = 2;
const int CLR_RW = 3;
const int CLR_BY = 4;
const int CLR_BG = 5;

using namespace std;



int main(int argc, char const *argv[])
{
  // map 설정 시작 ===================

  const int init_map[MAP_X][MAP_Y] =
      {{2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2}};

  setlocale(LC_ALL, "");

  initscr();
  start_color();
  init_pair(CLR_YB, COLOR_YELLOW, COLOR_BLACK);
  init_pair(CLR_WR, COLOR_WHITE, COLOR_RED);
  init_pair(CLR_RW, COLOR_RED, COLOR_WHITE);
  init_pair(CLR_BY, COLOR_BLACK, COLOR_YELLOW);
  init_pair(CLR_BG, COLOR_BLACK, COLOR_GREEN);

  border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  WINDOW *snake_map;
  snake_map = newwin(MAP_X + 2, MAP_Y + 2, 3, 3);

  wborder(snake_map, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

  mvprintw(1, 1, "SNAKE GAME");

  Cell **map;
  map = new Cell*[MAP_X];
  for(int i = 0; i < MAP_X; i++){
    map[i] = new Cell[MAP_Y];
  }

  for(int i = 0; i < MAP_X; i++){
    for(int j = 0; j < MAP_Y; j++){
      map[i][j].setValue(init_map[i][j]);
    }
  
  }

  // snake 의 경우 따로 관리
  Snake snake;

  for (int i = 0; i < MAP_X; i++) {
    for (int j = 0; j < MAP_Y; j++) {
      int cellStatus = map[i][j].getValue();

      switch (cellStatus){
        case 0:
          // 빈 공간
          break;

        case 1:
          // wall
          wattron(snake_map, COLOR_PAIR(CLR_BG));
          map[i][j].setValue(1);
          mvwprintw(snake_map, i + 1, j + 1, "W");
          wattroff(snake_map, COLOR_PAIR(CLR_BG));
          break;

        case 2:
          // immune wall
          wattron(snake_map, COLOR_PAIR(CLR_WR));
          mvwprintw(snake_map, i + 1, j + 1, "I");
          wattroff(snake_map, COLOR_PAIR(CLR_WR));
          map[i][j].setValue(2);
          break;

        case 3:
          // snake head
          Position pos;
          pos.x = i; pos.y = j;
          // snake.setHead(pos);
          break;
        
        case 4:
          // snake body
          // snake.append_body()
          // 방향에 따라서 바로 고정
          break;
        default:
          
          // throw exception
          break;
      }
    }


  }
  
  
  // map 설정 종료 ===================

  refresh();
  wrefresh(snake_map);


  getch();
  endwin();


  return 0;
}
