#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <malloc.h>

#include "SolverManager.h"
#include "HidatoSolver.h"

using namespace std;

// 퍼즐 매니저
SolverManager::SolverManager(string txtFile)
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
		// 솔버가 퍼즐을 풀기위한 전처리 과정
		solver.preprocessing(puzz, h, w);
		// 퍼즐풀기
		// for(int i=0; i<100000; ++i)
		solver.solve(puzz);
		// 정답확인
		solver.checkSolution(puzz);

		// // 퍼즐 보여주기
		cout << "--------------------------------------------------------------------------" << endl;
		 cout << "                              Check Solution " << endl;
		 cout << "--------------------------------------------------------------------------" << endl;
		 displayPuzz(puzz, w);
	}

	delete puzz;
}

// 넓이와 높이를 갱신하고 퍼즐을 리턴해 줌.
int* SolverManager::inputPuzz(ifstream& input, int &height, int& width)
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
void SolverManager::printWall(int w) {
	int wall_count = (w * 3) + 1;
	while (wall_count--)
		cout << "##";
	cout << endl;
}

// 퍼즐과 넓이를 받아서 w x h 모양으로 퍼즐 출력
void SolverManager::displayPuzz(int puzz[], int w)
{
	int height = _msize(puzz) / sizeof(int);
	printWall(w);
	for (int i = 0; i < height; ++i)
	{
		// 값이 -1, 즉 벽일 경우의 출력
		if (puzz[i] == -1) {
			cout << "##";
			cout << "####";
			if (i % w == w - 1) {
				cout << "##" << endl;
				printWall(w);
			}
			continue;
		}
		// 시작 할 때 하나 찍어주기
		cout << "##";
		// 벽이 아니고 숫자일 경우 출력
		if (puzz[i] == 0) {
			cout << " ? " << " ";
		}
		else {
			// 백의 자리일 경우 출력 포멧
			if ((puzz[i] / 100) >= 1)
				cout << "" << puzz[i] << " ";
			// 십의 자리일 경우 출력 포멧
			else if ((puzz[i] / 10) >= 1)
				cout << " " << puzz[i] << " ";
			// 일의 자리일 경우 출력 포멧
			else
				cout << " " << puzz[i] << "  ";
		}
		// 마지막 width일 경우 출력
		if (i % w == w - 1){
			cout << "##";
			cout << endl;
			printWall(w);
		}
	}
}
