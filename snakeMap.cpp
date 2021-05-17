#include <ncurses.h>

const int WINDOW_W = 30;
const int WINDOW_H = 100;


int main(){
  WINDOW* snake_map; // snake map
  WINDOW* score_board; // score board
  WINDOW* user_board; // username board

  int testArr[5][8] = {
    {2, 1, 1, 1, 1, 1, 1, 2},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 3, 4, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {2, 1, 1, 1, 1, 1, 1, 2}
  };

  initscr();
  resize_term(45, 50);
  start_color();

  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_RED);
  init_pair(3, COLOR_RED, COLOR_WHITE);
  init_pair(4, COLOR_BLACK, COLOR_YELLOW);
  init_pair(5, COLOR_GREEN, COLOR_GREEN);


  border('|', '|', '-', '-', '+', '+', '+', '+');
  attron(COLOR_PAIR(2));
  mvprintw(1, 1, "SNAKE GAME");
  attroff(COLOR_PAIR(2));

  snake_map = newwin(23, 23, 3, 3);
  wattron(snake_map, COLOR_PAIR(1));
  wborder(snake_map, '|', '|', '-', '-', '+', '+', '+', '+');
  mvwprintw(snake_map, 0, 8, "SNAKE");
  wattroff(snake_map, COLOR_PAIR(1));
  
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 8; j++){
      switch(testArr[i][j]){
        case 1:
          wattron(snake_map, COLOR_PAIR(5));
          mvwprintw(snake_map, i+1, j+1, " ");
          wattroff(snake_map, COLOR_PAIR(5));
          break;
        case 2:
          wattron(snake_map, COLOR_PAIR(2));
          mvwprintw(snake_map, i+1, j+1, " ");
          wattroff(snake_map, COLOR_PAIR(2));
          break;
        case 3:
          wattron(snake_map, COLOR_PAIR(3));
          mvwprintw(snake_map, i+1, j+1, " ");
          wattroff(snake_map, COLOR_PAIR(3));
          break;
        case 4:
          wattron(snake_map, COLOR_PAIR(4));
          mvwprintw(snake_map, i+1, j+1, " ");
          wattroff(snake_map, COLOR_PAIR(4));
          break;
      }
    }
  }

  score_board = newwin(4, 10, 5, 38);
  
  wattron(score_board, COLOR_PAIR(1));
  mvwprintw(score_board, 1, 1, "SCORE : ");
  mvwprintw(score_board, 2, 1, "0");
  wborder(score_board, '|', '|', '-', '-', '+', '+', '+', '+');

  refresh();
  wrefresh(snake_map);
  wrefresh(score_board);

  getch();
  endwin();

  return 0;
}
