#include "Snake.h"
#include "Position.h"
#include "Controller.h"
#include "constants.h"
#include <iostream>

using namespace constants;
using namespace std;

bool Snake::move(int d, Cell **map, Controller &controller){
  vector<Position> items = controller.items;
  // opposite direction

  if(d == 0) d = direction;
  if(d == direction + 2 || d == direction - 2) return false;

  // make new_head
  Position newHead = head;
  switch(d){
    case RIGHT:
      newHead.col++;
      break;
    case DOWN:
      newHead.row++;
      break;
    case LEFT:
      newHead.col--;
      break;
    case UP:
      newHead.row--;
      break;
  }

  if(map[newHead.row][newHead.col].getValue() == 1) return false;

  Position tail = body.back();

  auto it = body.begin();
  it = body.insert(it, head);
  body.pop_back();
  head = newHead;
  direction = d;

  for(auto it = controller.gates.begin(); it != controller.gates.end(); it++){
    if(head.col == (*it).col && head.row == (*it).row){
      moveHead(map, controller);
    }
  }

  checkItem(map, controller, tail);

  if(body.size() < 2) return false;

  for(auto it = body.begin(); it != body.end(); it++){
    if(head.col == (*it).col && head.row == (*it).row){
      return false;
    }
  }

  setSnakeMap(map, tail);

  return true;
}

//if head == gate
void Snake::moveHead(Cell** map, Controller &controller){
  vector<Position>& gates = controller.gates;
  Position inGate, outGate;
  if(gates[0].row == head.row && gates[0].col == head.col){
    inGate = gates[0];
    outGate = gates[1];
  }else{
    inGate = gates[1];
    outGate = gates[0];
  }
  controller.useGateCount++;

  // MAP_X MAP_Y
  Position newHead = outGate;
  if(outGate.row == 0 || outGate.col == 0 || outGate.row == MAP_X - 1 || outGate.col == MAP_Y - 1){
    switch (outGate.row) {
      case 0:
        direction = DOWN;
        newHead.row++;
        break;
      case (MAP_X -1):
        direction = UP;
        newHead.row--;
        break;
    }
    switch (outGate.col) {
      case 0:
        direction = RIGHT;
        newHead.col++;
        break;
      case (MAP_Y - 1):
        direction = LEFT;
        newHead.col--;
        break;
    }
  }else{
    if(!checkWall(map, direction, newHead)){
      newHead = changeCoordinate(direction, newHead);
    }else if(!checkWall(map, direction % 4 + 1, newHead)){
      direction = direction % 4 + 1;
      newHead = changeCoordinate(direction, newHead);
    }else if(!checkWall(map, direction == 1 ? 4 : direction - 1, newHead)){
      direction = direction == 1 ? 4 : direction - 1;
      newHead = changeCoordinate(direction, newHead);
    }else{
      direction = direction - 2 > 0 ? direction - 2 : direction + 2;
      newHead = changeCoordinate(direction, newHead);
    }
  }
  head = newHead;
}

Position Snake::changeCoordinate(int d, Position p){
  switch(d){
    case RIGHT:
      p.col++;
      break;
    case DOWN:
      p.row++;
      break;
    case LEFT:
      p.col--;
      break;
    case UP:
      p.row--;
      break;
  }
  return p;
}

bool Snake::checkWall(Cell** map, int d, Position p){
  p = changeCoordinate(d, p);
  if(map[p.row][p.col].getValue() == 1){
    return true;
  }
  return false;
}

void Snake::checkItem(Cell** map, Controller &controller, Position tail){
  vector<Position>& items = controller.items;

  if(map[head.row][head.col].getValue() == 5){
    body.push_back(tail);
    controller.ateGrowItemCount++;
  }else if(map[head.row][head.col].getValue() == 6){
    Position p = body.back();
    map[p.row][p.col].setValue(0);
    body.pop_back();
    controller.atePoisonItemCount++;
  }

  for(int i = 0; i < items.size(); i++){
    Position p = items[i];
    if(p.row == head.row && p.col == head.col){
      items.erase(items.begin() + i);
      i--;
    }
  }
}

void Snake::setSnakeMap(Cell **map, Position tail)
{
  map[head.row][head.col].setValue(3);
  map[tail.row][tail.col].setValue(0);

  for(int i = 0; i < body.size(); i++){
    map[body[i].row][body[i].col].setValue(4);
  }
}
