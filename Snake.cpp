#include "Snake.h"
#include "Position.h"
using namespace std;

void Snake::move(int d, Cell **map){
  // opposite direction
  // if(d == direction + 2 || d == direction - 2) game_over();

  // same direction
  // if(d == direction) return;

  if(d == 0) d = direction;

  // make new_head
  Position new_head = head;
  switch(d){
    case 1: // right -> x+1, y
      new_head.col++;
      break;
    case 2: // down -> x, y+1
      new_head.row++;
      break;
    case 3: // left -> x-1, y
      new_head.col--;
      break;
    case 4: // up -> x, y-1
      new_head.row--;
      break;
  }

  Position tail = body.back();

  auto it = body.begin();
  it = body.insert(it, head);
  body.pop_back();
  head = new_head;
  direction = d;

  // for(iterator it = item.begin(); it != item.end(); it++){
  //   if(it.row == head.row && it.col == head.col){
  //     if(it.val == 1){
  //       body.push_back(tail);
  //     }else if(it.val == -1){
  //       body.pop_back();
  //     }
  //   }
  // }

  //if(body.size() < 2) game_over();

  map[head.row][head.col] = 3;

  for(int i = 0; i < body.size(); i++){
    map[body[i].row][body[i].col] = 4;
  }
  map[tail.row][tail.col] = 0;
}
