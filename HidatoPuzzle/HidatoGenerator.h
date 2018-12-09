//HidatoGenerator

#include "Element.h"
#include "Point.h"

#ifndef _HIDATOGENERATOR_H_
#define _HIDATOGENERATOR_H_

#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

class HidatoGenerator {
private:
	// 8가지 방향 나타내기 위한 direction배열
	Point direction[8];

public:
  // 높이, 넓이, 총 길이 : width * height
	int height, width, len;
	int max = 0;

  int* puzz;

  Point startPoint;
	Point maxPoint;

	// 생성자
	HidatoGenerator();

	// 제너레이터가 가지고있는 메소드들
	void setPuzzleSize(int w, int h);
  void initializePuzzle();
  void makePuzzle(int level);
	int getRandomDiff(int level);

};

#endif
