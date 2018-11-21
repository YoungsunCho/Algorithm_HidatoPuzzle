#include "HidatoSolver.h"
#include <cstring>

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
	delete existed;
	delete E_array;
}

// 시작점 찾고 start_point에 값 설정해주고
// 못찾으면 false리턴
bool HidatoSolver::findStart(Point& start_point) {
	//앞에서 한 번 찾아주고
	for (int i = 0; i < len/2; i++) {
		if (E_array[i].value == 1) {
			// start_point를 (x, y)로 설정하고 함수종료
			// x가 height인거고 y가 width인거임
			start_point.x = (i % width);
			start_point.y = (i / width);
			return true;
		}
		// 뒤에서부터 포인터 넘기기
	  if (E_array[len-i-1].value == 1) {
	      start_point.x = ((len-1-i) % width);
	      start_point.y = ((len-1-i) / width);
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

	// current_element 레퍼런스로 선언
	Element* current_element = &E_array[p.x + width * p.y];
	if(current_element->neighbors[9]==false) getNeighbors(p);
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
	(*current_element).neighbors[8] = true;
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
