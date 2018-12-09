//HidatoSolver

#include "Element.h"
#include "Point.h"

#ifndef _HIDATOSOLVER_H_
#define _HIDATOSOLVER_H_


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
	void preprocessing(int puzz[], int _height, int _width);
	void solve(int puzz[]);
	bool findStart(Point& p);
	bool search(Point p, int order);
	void getNeighbors(Point p);
	void checkSolution(int puzz[]);
};

#endif
