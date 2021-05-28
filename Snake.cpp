#include "Snake.h"
using namespace std;

void Snake::move(int d){
  // opposite direction
  if(d == direction + 2 || d == direction - 2) game_over();

  // same direction
  if(d == direction) return;

  // make new_head
  Position new_head = head;
  switch(d){
    case 1: // right -> x+1, y
      new_head.x++;
      break;
    case 2: // down -> x, y+1
      new_head.y++;
      break;
    case 3: // left -> x-1, y
      new_head.x--;
      break;
    case 4: // up -> x, y-1
      new_head.y--;
      break;
  }

  // make new_body
  vector<Position> new_body;
  new_body.push_back(head);
  for(int i = 0; i < body.size() - 1; i++){
    new_body.push_back(body[i]);
  }

  head = new_head;

}
