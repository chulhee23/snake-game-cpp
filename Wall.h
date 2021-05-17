
#include "Cell.h"


// snake 통과 불과
// snake head 와 충돌 시 실패

// gate 설정
// wall 은 gate로 변할 수 있음
// immune wall 은 Gate 로 변할 수 없음

// 1: wall
// 2: immune wall

class Wall: public Cell {
  int status;
public:
  Wall(int value = 1);
  int getStatus(){return status;}
  
};
