#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <malloc.h>

using namespace std;

//height == number of rows
//width == number of columns

//넓이와 높이를 갱신하고 퍼즐을 리턴해 줌.
int *inputPuzz(ifstream& input, int &height, int& width)
{
	int w, h, len;
	input >> h >> w;

	height = h;
	width = w;

	len = w * h;
	int *puzz = new int[len];
	for (int i = 0; i < len; ++i) input >> puzz[i];

	//1차원 배열 puzz를 리턴한다.
	return puzz;
}

//퍼즐과 넓이를 받아서 w x h 모양으로 퍼즐 출력
void displayPuzz(int puzz[], int w)
{
  int height = _msize(puzz)/sizeof(int);
	for(int i=0; i< height; ++i)
	{
		cout << puzz[i] << " ";
		if(i % w == w - 1) cout << endl;
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
		int h, w;
		puzz = inputPuzz(input, h, w);
		displayPuzz(puzz, w);
	}

	delete puzz;
}

int main(){

	puzzManager("input.txt");
	//이렇게하면 puzzManager에서 작업을 다 해야하는거 아닙니까
	//모든 경우를 테스트 하는건데
	//이러면 while문에서 모든 작업을 다해야함


	// width가 가로길이 - col개수 height가 세로길이 - row개수
  // 생각을 해봅시다
	// input을 row col받아서 row x col의 매트릭스를 만든다.
  // inputPuzz(input, row, col) : 매트릭스에 각각의 값을 넣기 - clear

	// displayPuzz(puzz, w) : 매트릭스 보여주기 - clear

	// findStart(puzz, w) : puzzle의 시작점 찾기(1 찾기)

	// 똑같이 1차원의 어레이로 선언해서 하면
	// 어레이의 타입이 struct나 클래스로 되야함
	// getNeighbors() : 해당 point의 이웃들 찾기

	// resultCheck() : 정답이랑 맞는지 체크

	// hidato puzzle(grid, puzzle), solver, generator
  // solver.solve(row, col, puzzle);

  // solver에는 findStart함수 필요
  // width, height,
  // 정답을 담고있는 배열 하나가 더 필요함 그러고 마지막에 채워주는 식으로?
  // solve(puzzle, width, height);

  return 0;
}
