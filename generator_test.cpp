#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <malloc.h>
#include <time.h>
using namespace std;

#define MAX_SIZE 10
#define MIN_SIZE 5

// (x, y)점을 나타내기위한 Point 클래스
class Point {

public:
	int x, y;

	//생성자
	Point() : x(0), y(0) { }

	Point(int _x, int _y) : x(_x), y(_y) { }
}; // Point class end

// 히다토 퍼즐을 풀기위한 HidatoGenerator 클래스
class HidatoGenerator {
private:

	// 8가지 방향 나타내기 위한 direction배열
	Point direction[8];

public:
  // 높이, 넓이, 총 길이 : width * height
	// max = 퍼즐마지막 값을 저장하기 위함
	int height, width, len, max;

  int* puzz;

  Point startPoint;

	// 생성자
	HidatoGenerator();

	// 제너레이터가 가지고있는 메소드들
	void setPuzzleSize();
  void setStartPoint();
  void initializePuzzle();
  void setWall();
  void makePuzzle();

  void fillBlankInPuzzle(int level);

};

// 생성자
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
// 일단 n x n 사이즈로 정한다.
void HidatoGenerator::setPuzzleSize() {

  // 1 ~ max 숫자 생성
  int temp = rand() % MAX_SIZE + 1;
  // min과 max사이의 숫자로 하기위해
  // min보다 작으면 min더하기
  if(temp < MIN_SIZE) temp += MIN_SIZE;
  width = height = temp;
  len = width * height;

  // len만큼의 puzz배열 할당
  puzz = new int[len];
  memset(puzz, 0, len);

  // 시작점 랜덤으로 설정하고 puzzle을 제일큰 숫자로 초기화
  initializePuzzle();
  setStartPoint();
}


// 시작점 정해주는 함수
void HidatoGenerator::setStartPoint() {
  startPoint.x = rand() % width;
  startPoint.y = rand() % height;
  cout << "startPoint : " << "(" << startPoint.x << ", " << startPoint.y << ")" << endl;
}


// 퍼즐 초기화 하는 함수
void HidatoGenerator::initializePuzzle(){
  for(int i = 0; i < len; i++){
    puzz[i] = 99;
  }
}


// 마지막에 임의로 크게 설정했던 숫자들을 벽으로 만들어주기
void HidatoGenerator::setWall() {
  for(int i = 0; i < len; i++){
    if(puzz[i] == 99) puzz[i]= -1;
  }
}


// 퍼즐 만드는 함수 여기가 메인
void HidatoGenerator::makePuzzle() {
  // 시작점 1로 설정
  puzz[startPoint.x * width + startPoint.y] = 1;

  // 만들수 없는 경우 세기위한 변수
  // count는 매트릭스를 넘어가거나 이미 숫자 표시한곳이면 ++
  int count = 0;

  // 2부터 ++ 해가며 저장
  int order = 2;

  // 처음 좌표와 옮겼을 때의 좌표를 표현하기 위한 변수들
  Point p, moved_p;
  p = startPoint;

  // 방향을 랜덤으로 만들기 위한 변수 (0 ~ 7)
  // 임시로 이동한 좌표의 value값 저장하기위한 temp변수
  int d, temp;


  // 이 알고리즘의 문제점 완벽히 막힐경우는 어떻게 해결할 것인가 그것만 해결하면될듯
  // 일단은 count제한을 두어 해결 너무작게만들어지면 다시만들면 되니까!

  // 최대는 len까지고 count가 일정수준 넘어가면 stop
  while(order < len && count < 100){
    // 기존에 있는 숫자거나 매트릭스를 넘어가는 경우는 방향을 다시설정해준다.
    while(count < 100){
      d = rand() % 8;
      moved_p.x = p.x + direction[d].x;
      moved_p.y = p.y + direction[d].y;
      temp = puzz[moved_p.x * width + moved_p.y];

      // 매트릭스를 벗어나는 경우
    	if (moved_p.x < 0 || moved_p.y < 0 || moved_p.x >= width || moved_p.y >= height){
        count++;
        continue;
      }
      // 매트릭스 안
      else{
        // 기존에 있는 숫자인 경우
        if(temp < order) {
            count++;
            continue;
        }
        else break;
      }
    }

    // 다음숫자 찾았으면
    puzz[moved_p.x * width + moved_p.y] = order;
    p = moved_p;
    cout << order << endl;
    order ++;
  }

  // 만약에 퍼즐크기의 반보다 숫자들이 작게 생성 되면 퍼즐을 다시 생성
  if(order < len/2){
    initializePuzzle();
    setStartPoint();
    makePuzzle();
  }

  cout << "max : " << order - 1<< endl;
  cout << width <<  "   " << height << endl;

  // 나머지 숫자들 벽으로 만들어주기
  setWall();
}

// 퍼즐 초기화 하는 함수
void HidatoGenerator::fillBlankInPuzzle(int level){
  if(level == 1){
    cout << "fill blank level 1" << endl;
  }
}













// 반복되는 벽 print문 함수
void printWall(int w) {
	int wall_count = (w * 3) + 1;
	while (wall_count--)
		cout << "XX";
	cout << endl;
}

// 퍼즐과 넓이를 받아서 w x h 모양으로 퍼즐 출력
void displayPuzz(int puzz[], int w)
{
	int height = _msize(puzz) / sizeof(int);
	printWall(w);
	for (int i = 0; i < height; ++i)
	{
		// 값이 -1, 즉 벽일 경우의 출력
		if (puzz[i] == -1) {
			cout << "XX";
			cout << "XXXX";
			if (i % w == w - 1) {
				cout << "XX" << endl;
				printWall(w);
			}
			continue;
		}
		// 시작 할 때 하나 찍어주기
		cout << "XX";
		// 벽이 아니고  경우 출력
		if (puzz[i] == 0) {
			cout << " ? " << " ";
		}
		else {
			// 십의 자리일 경우 출력 포멧
			if ((puzz[i] / 10) >= 1)
				cout << " " << puzz[i] << " ";
			// 일의 자리일 경우 출력 포멧
			else
				cout << " " << puzz[i] << "  ";
		}
		// 마지막 width일 경우 출력
		if (i % w == w - 1){
			cout << "XX";
			cout << endl;
			printWall(w);
		}
	}
}


int main() {
  // RAND 함수 계속사용하기위해 메인부분에서 생성
  srand(time(NULL));

	HidatoGenerator Gen = HidatoGenerator();
  Gen.setPuzzleSize();
  Gen.makePuzzle();
  Gen.fillBlankInPuzzle(1);

  cout << "width : " << Gen.width << endl;
  displayPuzz(Gen.puzz ,Gen.width);

	return 0;
}

/*
1. min max 설정 어느정도로 할 건지?? 현재 min : 5, max : 10이라 6 ~ 10
이거에 따라 count도 얼마나 해줘야 할지, initializePuzzle하는 부분에서 99로 설정한것도 체인지 해줘야함

2. 중간에 끊기는거 왜인지 모르겠음....  row col 문제 같기도

3. n x n 사이즈인데 row col 변화시켰을 때 되는지... 확인좀..

4. 빈칸 구현함수 난이도에 따라 구현할 예정
  마지막에 난이도에 따라 0(빈칸)의 개수 정해주기
  1) easy 1 ~ 4
  2) medium 5 ~ 9
  3) hard : 숫자가 10 ~ 13 사이만큼 차이나게

5. 만든 퍼즐 기존 input.txt파일 형식으로 출력하기 row col 퍼즐

6. 모듈화 지금 다퍼블릭 아마 puzz startPoint는 변화없어도 될 것같고 point받아오고
direction solver랑 generator둘다 생성하는데 Point클래스에서 모듈화해보기


*/
