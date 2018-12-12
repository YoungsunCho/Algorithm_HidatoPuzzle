#include <iostream>
#include <cstring>
#include <stdlib.h>

#include "GeneratorManager.h"
#include "SolverManager.h"

using namespace std;

int main() {

	cout << endl <<"===============================Hidato Puzzle===============================" << endl << endl;

	cout <<"******************************Generator Start******************************" << endl;

	GeneratorManager generatorManager;

	cout << endl <<"*******************************Solver Start*******************************" << endl;

	SolverManager solverManager("input.txt");

	system("pause");
	return 0;
}
