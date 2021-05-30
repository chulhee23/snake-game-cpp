# Snake Game

## 과제 수행


## 뱀 바디
snake tail 을 Head 의 아래?
- deque
    - push, pop

- vector 
    - push back 
    - push first




### 1단계
NCurses Library 함수들을 사용하여 2차원 배열로 된 Snake Map을 Game 화면으로 표시하는 프로그램을 완성한다

*주의*
- Wall 과 Immune Wall 을 구분할 것


### 2단계
1단계 맵 위에 Snake 표시하고, 화살표를 입력받아 Snake의 이동을 완성한다.


- 게이트
    - 디렉션 수정


- 벽 충돌, 0.5 초 제한
- 아이템 상호작용

- 게임 오버
    - duringGame false

- 스코어 보드
- 미션 보드


- 리팩토링


## Gate
- 2개 게이트가 한 쌍으로 Wall 위에서 등장
- Snake 진입 시 사라질 수 없다.
- 한 번에 한쌍만 등장
- 몸의 길이가 5를 넘으면, 게이트가 등장

- Gate가나타나는벽이가장자리에있을때
    - 항상 Map의 안쪽 방향으로 진출한다.(고정)
    - 상단벽=>아래방향
    - 하단벽=>위방향
    - 좌측벽=>오른쪽방향
    - 우측벽=>왼쪽방향

- Gate가 나타나는 벽이 Map의 가운데 있을 때 다음의 순서로 진출
    - 진입 방향과 일치하는 방향이 우선
    - 진입 방향의 시계방향으로 회전하는 방향
    - 진입 방향의 역시계방향으로 회전하는 방향
    - 진입 방향과 반대방향