#include <ncurses.h>

int main(){
  WINDOW* win1; // snake map
  WINDOW* win2; // score board
  WINDOW* win3; // username board

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

  win1 = newwin(23, 23, 3, 3);
  wattron(win1, COLOR_PAIR(1));
  wborder(win1, '|', '|', '-', '-', '+', '+', '+', '+');
  mvwprintw(win1, 0, 8, "SNAKE");
  wattroff(win1, COLOR_PAIR(1));
  
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 8; j++){
      switch(testArr[i][j]){
        case 1:
          wattron(win1, COLOR_PAIR(5));
          mvwprintw(win1, i+1, j+1, " ");
          wattroff(win1, COLOR_PAIR(5));
          break;
        case 2:
          wattron(win1, COLOR_PAIR(2));
          mvwprintw(win1, i+1, j+1, " ");
          wattroff(win1, COLOR_PAIR(2));
          break;
        case 3:
          wattron(win1, COLOR_PAIR(3));
          mvwprintw(win1, i+1, j+1, " ");
          wattroff(win1, COLOR_PAIR(3));
          break;
        case 4:
          wattron(win1, COLOR_PAIR(4));
          mvwprintw(win1, i+1, j+1, " ");
          wattroff(win1, COLOR_PAIR(4));
          break;
      }
    }
  }

  win2 = newwin(4, 10, 5, 38);
  wattron(win2, COLOR_PAIR(1));
  mvwprintw(win2, 1, 1, "SCORE : ");
  mvwprintw(win2, 2, 1, "0");
  wborder(win2, '|', '|', '-', '-', '+', '+', '+', '+');

  refresh();
  wrefresh(win1);
  wrefresh(win2);

  getch();
  endwin();

  return 0;
}
