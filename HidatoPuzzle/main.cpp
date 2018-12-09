#include <iostream>
#include <cstring>
#include <stdlib.h>

#include "GeneratorManager.h"
#include "SolverManager.h"

using namespace std;

int main() {

	cout <<"-----------------------------------------Hidato Puzzle Start!!!-----------------------------------------" << endl;

	cout <<"-----------------------------------------Generator Start-----------------------------------------" << endl;

	GeneratorManager generatorManager;

	cout <<"-----------------------------------------Solver Start-----------------------------------------" << endl;

	SolverManager solverManager("input.txt");

	system("pause");
	return 0;
}
