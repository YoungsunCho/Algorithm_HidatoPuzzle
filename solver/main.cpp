#include <iostream>
#include <cstring>

#include "PuzzleManager.h"
#include "HidatoSolver.h"

#include <chrono>
using namespace std;

int main() {
	//10 번 돌려서 시간을 출력.
	for(int i=0; i<10; ++i)
	{
		// 시간 성능 측정 시작
		chrono::system_clock::time_point StartTime = chrono::system_clock::now();

		PuzzleManager puzzManager("input.txt");

		// 시간 성능 측정 종료
		chrono::system_clock::time_point EndTime = chrono::system_clock::now();
		chrono::nanoseconds nano = EndTime - StartTime;
		// 시간 성능 보여주기
		printf("%d time taken : %d nanoseconds\n", i, nano.count() );
	}
	return 0;
}
