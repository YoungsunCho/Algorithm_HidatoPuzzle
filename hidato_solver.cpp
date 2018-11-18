#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <malloc.h>
using namespace std;

// (x, y)점을 나타내기위한 Point 클래스
class Point {

public:
	int x, y;

	//생성자
	Point() : x(0), y(0) { }

	Point(int _x, int _y) : x(_x), y(_y) { }
}; // Point class end


// value와 neighbors의 유무를 갖고 있는 Element 클래스
class Element {

public:
	// 해당점의 값이다.
	int value;
	// 이웃들은 최대 8개를 가질 수 있으며 초기설정은 전부 0으로 해준다.
	bool neighbors[8] = { 0, };

	// 생성자
	Element() { }

}; // Element class end


// 히다토 퍼즐을 풀기위한 HidatoSolver 클래스
class HidatoSolver {
private:
	// 높이, 넓이, 총 길이 : width * height
	// max = 퍼즐마지막 값을 저장하기 위함
	int height, width, len, max;

	// Element를 담을 배열 선언
	Element* E_array;

	// 이미 숫자가 배치되어있는지 여부
	bool* existed;

	// 8가지 방향 나타내기 위한 direction배열
	Point direction[8];

public:
	// 생성자
	HidatoSolver();

	// 솔버가 가지고 있는 method들이고 설명은 밑에서 하겠다.
	// 여기서 메인에서 불리는건 preprocessing, solve, checkSolution
	// 나머지 3개는 private으로 가도 상관없다.
	// 일단은 보기 편하게 한군데에 모아두겠다.
	void preprocessing(int puzz[], int _height, int _width);
	void solve(int puzz[]);
	bool findStart(Point& p);
	bool search(Point p, int order);
	void getNeighbors(Point p);
	void checkSolution(int puzz[]);
};

// 생성자
HidatoSolver::HidatoSolver() {

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

// 솔브하기 위해서 puzzle을 우리가 원하는 형태로 변환시키는 과정이다.
void HidatoSolver::preprocessing(int puzz[], int _height, int _width) {

	// parameter로 넘겨져 온 것을 solver 멤버변수에 넣는다.
	height = _height;
	width = _width;
	len = height * width;

	int index = 0;
	max = 0;

	// len만큼의 Element어레이 선언
	E_array = new Element[len];
	memset(E_array, 0, len * sizeof(Element));

	// 초기 설정된 숫자 담기위한 배열 선언
	existed = new bool[len + 1];
	memset(existed, 0, len + 1);

	// 퍼즐을 받아서 E_array에 담고, 미리 만들어진 숫자는 existed에 담기
	for (int i = 0; i < len; i++) {
		// 퍼즐을 그대로 element에 추가
		E_array[i].value = puzz[i];

		// 미리 만들어진 숫자면
		if (puzz[i] > 0)
			existed[E_array[i].value] = true;

		// 맥스 값 change
		if (puzz[i] > max)
			max = puzz[i];
	}
}

// 퍼즐을 가져와 시작점 찾고 search 시작
void HidatoSolver::solve(int puzz[]) {
	Point start_point;
	// 시작점이 있으면
	if (findStart(start_point) == true)
		search(start_point, 2);
}

// 시작점 찾고 start_point에 값 설정해주고
// 못찾으면 false리턴
bool HidatoSolver::findStart(Point& start_point) {
	for (int i = 0; i < len; i++) {
		// 시작점 찾으면
		// 시작점 빨리찾기.. 하는 알고리즘 해서 시간 줄여도 될듯
		if (E_array[i].value == 1) {
			// start_point를 (x, y)로 설정하고 함수종료
			// x가 height인거고 y가 width인거임
			start_point.x = (i % width);
			start_point.y = (i / width);
			return true;
		}
	}
	return false;
}

// order의 순서
bool HidatoSolver::search(Point p, int order) {

	// 끝까지 찾으면 종료
	if (order == max) return true;

	// 해당 점에 이웃찾기
	// 만약에 이웃이 이미 찾았으면 찾을필요 없음 불필요한 연산을 하는거지 - 향후 알고리즘 향상
	getNeighbors(p);

	// current_element 레퍼런스로 선언
	Element* current_element = &E_array[p.x + width * p.y];
	Point moved_p;

	// 존재하는 숫자일 경우
	if (existed[order]) {
		// 8 방향
		for (int i = 0; i < 8; i++) {
			// 이웃이 있는지 확인
			if ((*current_element).neighbors[i]) {
				// 옮겨진 위치 설정
				moved_p.x = p.x + direction[i].x;
				moved_p.y = p.y + direction[i].y;
				// 그 이웃이 order(이번에 들어갈 숫자)와 같으면
				if (E_array[moved_p.x + width * moved_p.y].value == order) {
					// recursive하게 호출 맞는 답이 나올때 까지
					if (search(moved_p, order + 1))
						return true;
				}
			}
		}
		return false;
	}

	// 존재하지 않는 숫자일 경우
	for (int i = 0; i < 8; i++) {
		if ((*current_element).neighbors[i]) {
			// 옮겨진 위치 설정
			moved_p.x = p.x + direction[i].x;
			moved_p.y = p.y + direction[i].y;
			// 0 즉, 빈칸일 경우
			if (E_array[moved_p.x + width * moved_p.y].value == 0) {
				// 일단 order로 설정을 한다음 recursive하게 수행
				E_array[moved_p.x + width * moved_p.y].value = order;
				if (search(moved_p, order + 1)) return true;
				// recover하는 부분이다.
				E_array[moved_p.x + width * moved_p.y].value = 0;
			}
		}
	}
	return false;
}

// 해당 point의 이웃들을 찾아줘서 element의 neighbors에 저장하는 함수
void HidatoSolver::getNeighbors(Point p) {

	int x = p.x;
	int y = p.y;
	Point moved_p;

	// 이웃을 찾아야할 current_element, 레퍼런스로 받음
	Element* current_element = &E_array[x + width * y];
	//
	Element temp;

	// 8가지 방향
	for (int i = 0; i < 8; i++) {
		// 현재 점이 갈수 있는 곳의 위치
		moved_p.x = x + direction[i].x;
		moved_p.y = y + direction[i].y;
		// 위치에 해당하는 element
		temp = E_array[moved_p.x + width * moved_p.y];
		// 이웃이 매트릭스를 벗어나는 경우
		if (moved_p.x < 0 || moved_p.y < 0 || moved_p.x >= width || moved_p.y >= height) continue;
		// 매트릭스안이지만 벽인경우
		else if (temp.value < 0) continue;
		// 가능한 이웃이면 true로 설정
		else (*current_element).neighbors[i] = true;
	}
}


// 우리가 만든 솔루션 체크
void HidatoSolver::checkSolution(int puzz[]) {
	for (int i = 0; i < len; i++) {
		// 빈칸이면
		if (puzz[i] == 0) {
			// 해당 element의 값을 채워넣기
			puzz[i] = E_array[i].value;
		}
	}
}


// height == number of rows
// width == number of columns

// 넓이와 높이를 갱신하고 퍼즐을 리턴해 줌.
int *inputPuzz(ifstream& input, int &height, int& width)
{
	int w, h, len;
	input >> h >> w;

	height = h;
	width = w;

	len = w * h;
	int *puzz = new int[len];
	for (int i = 0; i < len; ++i) input >> puzz[i];

	// 1차원 배열 puzz를 리턴한다.
	return puzz;
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


// 퍼즐 매니저
void puzzManager(string txtFile)
{
	ifstream input;
	input.open(txtFile);

	int numOfPuzz;
	input >> numOfPuzz;
	int *puzz;

	while (numOfPuzz--)
	{
		// 일단 이 부분이 메인이다.
		int h, w;
		// input.txt로부터 입력 받기
		puzz = inputPuzz(input, h, w);

		// 솔버 생성
		HidatoSolver solver;
		// 문제 출력
		cout << "-----------------------------------------input puzzle-------------------------------------------------" << endl;
		displayPuzz(puzz, w);

		// 솔버가 퍼즐을 풀기위한 전처리 과정
		solver.preprocessing(puzz, h, w);
		// 퍼즐풀기
		solver.solve(puzz);
		// 정답확인
		solver.checkSolution(puzz);

		// 퍼즐 보여주기
		cout << "-----------------------------------------check solution-----------------------------------------------" << endl;
		displayPuzz(puzz, w);
	}

	delete puzz;
}

int main() {

	puzzManager("input.txt");

	return 0;
}

/*
1. findStart - 알고리즘 향상 방법
2. search - getNeighbors - 한번 했으면 다시 할 필요 없음 중복확인 방법
3. point, element, HidatoSolver, puzzlemanager 4개로 모듈화방법


4(해결) : 출력 예쁘게 하기 -1값 공백으로 처리하는 거랑
두자리숫자(22) 한자리숫자(5)크기 다른거 \t사용해셔 균일하게 출력
다르게 이쁘게 출력할 수 있으면 ㄱㄱ
ex)
---+---+---+
 1 | 22|  3|
---+---+---+
   | 5 |   |
---+---+---+
 4 | 9 | 7 |
---+---+---+
*/
