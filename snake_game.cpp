#include <ncurses.h>
#include <iostream>
#include "snake_game.h"



int selectGame(void)
{
  int c = 0, ch;
  initscr();
  erase();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);

  attron(A_STANDOUT);
  mvprintw(5, 5, " Play Game MAP - 1");
  attroff(A_STANDOUT);
  mvprintw(6, 5, " Play Game MAP - 2");
  mvprintw(7, 5, " Play Game MAP - 3");
  mvprintw(8, 5, " Play Game MAP - 4");
  mvprintw(9, 5, " Exit");
  
  while (1)
  {
    ch = getch();
    if (ch == '\n')
    {
      return c;
      // 0 1 2 3 4중 택 1
    }
    else if (ch == KEY_UP)
    {
      if (c > 0)
      {
        c--;
      }
      else
      {
        c = 4;
      }
    }
    else if (ch == KEY_DOWN)
    {
      if (c < 4)
      {
        c++;
      }
      else
      {
        c = 0;
      }
    }
    switch (c)
    {
    case 0:
      erase();
      attron(A_STANDOUT);
      mvprintw(5, 5, " Play Game MAP - 1");
      attroff(A_STANDOUT);
      mvprintw(6, 5, " Play Game MAP - 2");
      mvprintw(7, 5, " Play Game MAP - 3");
      mvprintw(8, 5, " Play Game MAP - 4");
      mvprintw(9, 5, " Exit");
      break;
    case 1:
      erase();
      mvprintw(5, 5, " Play Game MAP - 1");
      attron(A_STANDOUT);
      mvprintw(6, 5, " Play Game MAP - 2");
      attroff(A_STANDOUT);
      mvprintw(7, 5, " Play Game MAP - 3");
      mvprintw(8, 5, " Play Game MAP - 4");
      mvprintw(9, 5, " Exit");
      break;
    case 2:
      erase();
      mvprintw(5, 5, " Play Game MAP - 1");
      mvprintw(6, 5, " Play Game MAP - 2");
      attron(A_STANDOUT);
      mvprintw(7, 5, " Play Game MAP - 3");
      attroff(A_STANDOUT);
      mvprintw(8, 5, " Play Game MAP - 4");
      mvprintw(9, 5, " Exit");
      break;
    case 3:
      erase();
      mvprintw(5, 5, " Play Game MAP - 1");
      mvprintw(6, 5, " Play Game MAP - 2");
      mvprintw(7, 5, " Play Game MAP - 3");
      attron(A_STANDOUT);
      mvprintw(8, 5, " Play Game MAP - 4");
      attroff(A_STANDOUT);
      mvprintw(9, 5, " Exit");
      break;
    case 4:
      erase();
      mvprintw(5, 5, " Play Game MAP - 1");
      mvprintw(6, 5, " Play Game MAP - 2");
      mvprintw(7, 5, " Play Game MAP - 3");
      mvprintw(8, 5, " Play Game MAP - 4");
      attron(A_STANDOUT);
      mvprintw(9, 5, " Exit");
      attroff(A_STANDOUT);
      break;
    }
  }
}



