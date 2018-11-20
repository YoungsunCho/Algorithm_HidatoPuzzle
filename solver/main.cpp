#include <iostream>
#include <cstring>

#include "PuzzleManager.h"
#include "HidatoSolver.h"

#include <chrono>
using namespace std;

int main() {

	// 시간 성능 측정 시작
	chrono::system_clock::time_point StartTime = chrono::system_clock::now();

	PuzzleManager puzzManager("input.txt");

	// 시간 성능 측정 종료
	chrono::system_clock::time_point EndTime = chrono::system_clock::now();
	chrono::nanoseconds nano = EndTime - StartTime;

	// 시간 성능 보여주기
	cout << "time taken : " << nano.count() << " nano seconds" << endl;

  return 0;
}
