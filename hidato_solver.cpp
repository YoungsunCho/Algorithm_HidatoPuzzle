#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <malloc.h>
using namespace std;

class Point{
private:
  int x, y;

public:
  //생성자
  Point() : x(0) , y(0){

  }

  Point(int _x , int _y) : x(_x) , y(_y){

  }

  void setX(int _x){
    x = _x;
  }
  void setY(int _y){
    y = _y;
  }

  int getX(){
    return x;
  }
  int getY(){
    return y;
  }
};

class Element{  //node
private :
  int value;
  Point direction[8];

public :

  //생성자
  Element(){

    Point n(0,-1);  //N
    Point ne(1,-1);  //NE
    Point e(1,0);  //E
    Point se(1,1);  //SE
    Point s(0,1);  //S
    Point sw(-1,1);  //SW
    Point w(-1,0);  //W
    Point nw(-1,-1);  //NW

    direction[0] = n;
    direction[1] = ne;
    direction[2] = e;
    direction[3] = se;
    direction[4] = s;
    direction[5] = sw;
    direction[6] = w;
    direction[7] = nw;

  }

 void setValue(int _value){
   value = _value;
 }

 int getValue(){
   return value;
 }

};// end class Element


class HidatoSolver{
private:
  // 넓이, 높이, max
  int height, width, max;

  Element* array;
  // 이미 숫자가 배치되어있는지 여부
  bool* existed;

public:
  //생성자
  HidatoSolver();

  void preprocessing(int puzz[], int _height ,int _width);

};


HidatoSolver::HidatoSolver(){

}

//solveIt() 전까지
void HidatoSolver::preprocessing(int puzz[], int _height ,int _width){

  height = _height;
  width = _width;

  int len = height * width;

  int index = 0;
  int max = 0;

  array = new Element[len];
  memset( array, 0, len * sizeof(Element));

  existed = new bool[len + 1];
  memset( existed, 0, len + 1 );

  for (int i = 0; i < len; ++i){
    array[i].setValue(puzz[i]);

    if (puzz[i] > 0)
      existed[puzz[i]] = true;

    if(puzz[i] > max)
      max = puzz[i];
  }

  cout << max << endl;


  cout << "existed Test" << endl;
  //existed 출력 테스트
  for (int i = 0; i < len; ++i){
    if (existed[i] == true)
      cout << 1 << " ";
    else
      cout << 0 << " ";

    if ((i+1) % width == 0)
      cout << endl;
  }
  cout << endl;

  cout << "Element array" << endl;
  //Element type array 출력 테스트
  for (int i = 0; i < len; ++i){
    cout << array[i].getValue()<< " ";
    if ((i+1) % width == 0)
      cout << endl;
  }
  cout << endl;

}




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

    HidatoSolver solver;
    solver.preprocessing(puzz, h, w);

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
