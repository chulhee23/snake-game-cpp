#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Cell.h"
#include "Wall.h"
#include "Snake.h"
#include "Position.h"

#define MAP_X 21
#define MAP_Y 21

using namespace std;

int main(int argc, char const *argv[])
{
  // graphic 설정 시작


  // graphic 설정 종료


  // map 설정 시작 ===================
  // txt 파일 읽어서 map 만들기
  ifstream fin("./maps/map.txt");
  
  if(!fin){
    cout << "map file error" << endl;
    return 0;
  }

  Cell **map;
  map = new Cell*[MAP_X];
  for(int i = 0; i < MAP_X; i++){
    map[i] = new Cell[MAP_Y];
  }

  // snake 의 경우 따로 관리
  Snake snake;

  string buffer;
  for (int i = 0; i < MAP_X; i++) {
    getline(fin, buffer);
    for (int j = 0; j < MAP_Y; j++) {
      int cellStatus = buffer[j] - '0';

      switch (cellStatus){
        case 0:
          // 빈 공간
          // map[i][j].setValue(buffer[j] - '0');
          break;

        case 1:
          // wall
          map[i][j] = Wall(1);
          break;

        case 2:
          // immune wall
          map[i][j] = Wall(2);
          
          break;

        case 3:
          // snake head
          Position pos;
          pos.x = i; pos.y = j;
          snake.setHead(pos);
          break;
        
        case 4:
          // snake body
          // snake.append_body()
          // 방향에 따라서 바로 고정


        default:
          
          // throw exception
          break;
      }
      
    }
    cout << endl;
  }

  for (int i = 0; i < MAP_X; i++) {
    for (int j = 0; j < MAP_Y; j++) {
      cout << map[i][j].getValue();
    }
    cout << endl;
  }
  
  
  // map 설정 종료 ===================

  
  return 0;
}
