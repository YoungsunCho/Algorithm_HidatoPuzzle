//GeneratorManager
#include <cstring>

#ifndef _GENERATORMANAGER_H_
#define _GENERATORMANAGER_H_

using namespace std;

class GeneratorManager {

public :

//생성자
GeneratorManager();

void printWall(int w);
void displayPuzz(int puzz[], int w);
void saveInputFile(int puzz[], int w);

};

#endif
