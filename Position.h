#ifndef __POSITION__
#define __POSITION__


struct Position
{
  Position() : row(0), col(0){};
  Position(int _row, int _col) : row(_row), col(_col){};
  int row, col;
};

#endif