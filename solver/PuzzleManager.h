//PuzzleManager
#include <cstring>

#ifndef _PUZZLEMANAGER_H_
#define _PUZZLEMANAGER_H_

using namespace std;

class PuzzleManager {

public :

PuzzleManager(string txtFile);

int* inputPuzz(ifstream& input, int &height, int& width);
void printWall(int w);
void displayPuzz(int puzz[], int w);

};

#endif
