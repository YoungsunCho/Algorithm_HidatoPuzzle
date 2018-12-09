#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <malloc.h>
#include <time.h>

#include "GeneratorManager.h"
#include "HidatoGenerator.h"

using namespace std;

GeneratorManager::GeneratorManager(){

  // RAND 함수 계속사용하기위해 메인부분에서 생성
  srand(time(NULL));
  int difficulty, width, height;
  // 난이도 선택 UI
  cout << "------------------------------------------" << endl;
  cout << "           Select Difficulty              " << endl;
  cout << "     Easy : 1,  Normal : 2,  Hard : 3     " << endl;
  cout << "------------------------------------------" << endl;

  cin >> difficulty;
  // 예외처리 여기서 중요하지 않기에 생략

  cout << "------------------------------------------" << endl;
  cout << "       Enter The Number Of Width          " << endl;
  cout << "------------------------------------------" << endl;
  cin >> width;
  cout << "------------------------------------------" << endl;
  cout << "       Enter The Number Of Height         " << endl;
  cout << "------------------------------------------" << endl;
  cin >> height;

  HidatoGenerator Gen = HidatoGenerator();
  Gen.setPuzzleSize(width, height);
  Gen.makePuzzle(difficulty);

  cout << endl;
  cout << "       " << Gen.width << " x " << Gen.height << " HidatoPuzzle Created       "<< endl;
  cout << "------------------------------------------" << endl;
  displayPuzz(Gen.puzz ,Gen.width);
  saveInputFile(Gen.puzz, Gen.width);
}


// 반복되는 벽 print문 함수
void GeneratorManager::printWall(int w) {
	int wall_count = (w * 3) + 1;
	while (wall_count--)
		cout << "XX";
	cout << endl;
}

// 퍼즐과 넓이를 받아서 w x h 모양으로 퍼즐 출력
void GeneratorManager::displayPuzz(int puzz[], int w)
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
		// 벽이 아니고 모르는 경우 출력
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

void GeneratorManager::saveInputFile(int puzz[], int w)
{
	ofstream fout;
	fout.open("input.txt");
	// 입출력 파일 갯수 고정으로 1이 될 것임 하나 만들 때 마다 풀어줄 것
	fout << 1 << endl << endl;
	// 행과 열이 몇개인지 써주기 위해, 줄 나누기를 위해 계산식
	int height = _msize(puzz) / sizeof(int);
	fout << (height/w) << " " << w << endl;
	for (int i = 0; i < height; ++i)
	{
		// 퍼즐에 담긴 값 하나씩 출력
		fout << puzz[i] << " ";
		// 마지막 값이라면 줄바꾸기 수행
		if (i % w == w - 1) {
			fout << endl;
		}
	}
	fout.close();
}
