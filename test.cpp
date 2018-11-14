#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <malloc.h>

using namespace std;


 //넓이와 높이를 갱신하고 퍼즐을 리턴해 줌.
int *inputPuzz(ifstream& input, int &width, int& height)
{
	int w, h, len;
	input >> h>> w;
	width=w;
	height=h;
	len = w * h;
	int *puzz = new int[len];
	for (int i = 0; i < len; ++i) input >> puzz[i];

	return puzz;
}

 //퍼즐과 넓이를 받아서 w x h 모양으로 퍼즐 출력
void displayPuzz(int puzz[], int w)
{
	for(int i=0; i<_msize(puzz)/sizeof(int); ++i)
	{
		cout << puzz[i] << " ";
		if(i%w==w-1) cout << endl;
	}
	cout << endl;
}


//퍼즐 매니저
void puzzManager(char* txtFile)
{
	ifstream input;
	input.open(txtFile);

	int numOfPuzz;
	input >> numOfPuzz;
	int *puzz;

	while (numOfPuzz--)
	{
		int w, h;
		puzz = inputPuzz(input, w, h);
		displayPuzz(puzz, w);
	}

	delete puzz;
}

int main(){

	puzzManager("input.txt");

  // 생각을 해봅시다
  // input을 row col받아서 row x col의 매트릭스를 만든다.
  // 매트릭스에 각각의 값을 넣기
  // hidato puzzle(grid, puzzle), solver, generator
  // solver.solve(row, col, puzzle);

  // solver에는 findStart함수 필요
  // width, height,
  // 정답을 담고이쓴ㄴ 배열 하나가 더 필요함 그러고 마지막에 채워주는 식으로?
  // solve(puzzle, width, height);

  return 0;
}
