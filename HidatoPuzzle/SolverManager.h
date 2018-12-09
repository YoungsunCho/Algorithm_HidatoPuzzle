//SolverManager
#include <cstring>

#ifndef _SOLVERMANAGER_H_
#define _SOLVERMANAGER_H_

using namespace std;

class SolverManager {

public :

SolverManager(string txtFile);

int* inputPuzz(ifstream& input, int &height, int& width);
void printWall(int w);
void displayPuzz(int puzz[], int w);

};

#endif
