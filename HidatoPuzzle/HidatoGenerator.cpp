#include "HidatoGenerator.h"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <malloc.h>

using namespace std;

HidatoGenerator::HidatoGenerator() {

	// Point 클래스를 사용하여 각 방향 잡아주기
	// 0 ~ 8 : nw ~ se 시계방향으로 direction배열에 저장
	Point nw(-1, -1);  // NW
	Point n(-1, 0);    // N
	Point ne(-1, 1);   // NE
	Point w(0, -1);    // W
	Point e(0, 1);     // E
	Point sw(1, -1);   // SW
	Point s(1, 0);     // S
	Point se(1, 1);    // SE

	direction[0] = nw;
	direction[1] = n;
	direction[2] = ne;
	direction[3] = w;
	direction[4] = e;
	direction[5] = sw;
	direction[6] = s;
	direction[7] = se;
}

// 빈 퍼즐 선언 크기를 랜덤으로 만들기 위함
void HidatoGenerator::setPuzzleSize(int w, int h) {

	// 기존에 크기도 랜덤으로 만들었을 때 썻던 코드들 현재 코드는 입력받아 생성하기 때문에 주석처리 하였다.
  // // 1 ~ max 숫자 생성
  // int temp = rand() % MAX_SIZE + 1;
  // // min과 max사이의 숫자로 하기위해
  // // min보다 작으면 min더하기
  // if(temp < MIN_SIZE) temp += MIN_SIZE;

	width = w;
	height = h;
	len = width * height;

  // len만큼의 puzz배열 할당
  puzz = new int[len];
  memset(puzz, 0, len);

  // 시작점 랜덤으로 설정하고 puzzle을 -1로 초기화
  initializePuzzle();
}


// 전부 -1(벽)로 초기화 해준다음에 시작점 랜덤으로 정해주는 함수
void HidatoGenerator::initializePuzzle() {

	// 전부 벽으로 초기화
	for(int i = 0; i < len; i++){
    puzz[i] = -1;
  }

	// 시작점 랜덤으로 위치 정해주고 1로 설정
	startPoint.x = rand() % width;
  startPoint.y = rand() % height;

  puzz[startPoint.x + width * startPoint.y] = 1;
}


// 난이도에 따라 랜덤한 차이를 생성하기 위함
int HidatoGenerator::getRandomDiff(int level){

	int diff;
	switch(level){
		// easy 난이도 1 ~ 3
		// 숫자간의 차이가 2 ~ 3 가 되게 설정 해줌
		case 1:{
				diff = rand() % 3 + 2;
				break;
		}
		// medium 난이도 4 ~ 7
		case 2:{
				diff = rand() % 4 + 4;
				break;
		}
		// hard 난이도 8 ~ 10
		case 3:{
				diff = rand() % 2 + 8;
				break;
		}
	}

	return diff;
}


// 퍼즐 만드는 함수 여기가 메인
void HidatoGenerator::makePuzzle(int level){

	// difficulty에 따른 숫자간의 차이를 설정하기 위한 변수
	int diff = getRandomDiff(level);

  // 만들수 없는 경우 세기위한 변수
  // count는 매트릭스를 넘어가거나 이미 숫자 표시한곳이면 ++
  int count = 0;

  // 1은 시작점으로 저장해 두었으니  2부터 ++ 해가며 저장
  int order = 2;

  // 처음 좌표와 옮겼을 때의 좌표를 표현하기 위한 변수들
  Point p, moved_p;
  p = startPoint;

  // d :  방향을 랜덤으로 만들기 위한 변수  (0 ~ 7)
  // 임시로 이동한 좌표의 value값 저장하기위한 temp변수
  int d, temp;

	int limit = len * len;

  // 이 알고리즘의 문제점 완벽히 막힐경우는 어떻게 해결할 것인가 그것만 해결하면될듯
  // 일단은 count제한을 두어 해결 너무 작게 만들어지면 다시만들면 되니까!

  // 최대는 len까지고 count가 일정수준 넘어가면 stop
  while(order < len && count < limit){

    // 기존에 있는 숫자거나 매트릭스를 넘어가는 경우는 방향을 다시설정해준다.
    while(count < limit){
      d = rand() % 8;
      moved_p.x = p.x + direction[d].x;
      moved_p.y = p.y + direction[d].y;
      temp = puzz[moved_p.x + width * moved_p.y];

      // 매트릭스를 벗어나는 경우
    	if (moved_p.x < 0 || moved_p.y < 0 || moved_p.x >= width || moved_p.y >= height){
        count++;
        continue;
      }
      // 매트릭스 안
      else{
        // 기존에 있는 숫자인 경우
				if(temp != -1){
	        if(temp < order) {
	            count++;
	            continue;
	        }
				}
				// 추가해줘야 할 경우
        else break;
      }
    }

		// 다음숫자를 어디에 늘지 랜덤으로 찾고나서
		// 숫자를 추가해줘야 하는 경우
		if(count < limit){
	    puzz[moved_p.x + width * moved_p.y] = order;
	    p = moved_p;

			// 숫자를 설정해준다음에 난이도에 따라 랜덤으로 받은 diff를 사용하여
			// 처음에 숫자 1로 시작하기 때문에 (order-1)로 바꿔줬다.
			// 빈칸(0) 으로 설정해준다.
			if((order-1) % diff != 0) puzz[moved_p.x + width * moved_p.y] = 0;

			//maxPoint의 위치를 갱신해준다.
			maxPoint.x = moved_p.x;
			maxPoint.y = moved_p.y;

	   	order ++;
		}

  }

	// max(마지막 숫자)를 저장해줫다가 마지막 숫자는 표시해준다.
	max = MAX(order - 1, max);
	puzz[maxPoint.x + width * maxPoint.y] = max;

  // 만약에 퍼즐크기의 반보다 숫자들이 작게 생성 되면 퍼즐을 다시 생성
  if(order < len/2){
    initializePuzzle();
    makePuzzle(level);
	}

}
