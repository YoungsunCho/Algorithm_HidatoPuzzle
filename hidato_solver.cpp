#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <malloc.h>
using namespace std;

// (x, y)���� ��Ÿ�������� Point Ŭ����
class Point {

public:
	int x, y;

	//������
	Point() : x(0), y(0) { }

	Point(int _x, int _y) : x(_x), y(_y) { }
}; // Point class end


// value�� neighbors�� ������ ���� �ִ� Element Ŭ����
class Element {

public:
	// �ش����� ���̴�.
	int value;
	// �̿����� �ִ� 8���� ���� �� ������ �ʱ⼳���� ���� 0���� ���ش�.
	bool neighbors[8] = { 0, };

	// ������
	Element() { }

}; // Element class end


// ������ ������ Ǯ������ HidatoSolver Ŭ����
class HidatoSolver {
private:
	// ����, ����, �� ���� : width * height
	// max = �������� ���� �����ϱ� ����
	int height, width, len, max;

	// Element�� ���� �迭 ����
	Element* E_array;

	// �̹� ���ڰ� ��ġ�Ǿ��ִ��� ����
	bool* existed;

	// 8���� ���� ��Ÿ���� ���� direction�迭
	Point direction[8];

public:
	// ������
	HidatoSolver();

	// �ֹ��� ������ �ִ� method���̰� ������ �ؿ��� �ϰڴ�.
	// ���⼭ ���ο��� �Ҹ��°� preprocessing, solve, checkSolution
	// ������ 3���� private���� ���� �������.
	// �ϴ��� ���� ���ϰ� �ѱ����� ��Ƶΰڴ�.
	void preprocessing(int puzz[], int _height, int _width);
	void solve(int puzz[]);
	bool findStart(Point& p);
	bool search(Point p, int order);
	void getNeighbors(Point p);
	void checkSolution(int puzz[]);
};

// ������
HidatoSolver::HidatoSolver() {

	// Point Ŭ������ ����Ͽ� �� ���� ����ֱ�
	// 0 ~ 8 : nw ~ se �ð�������� direction�迭�� ����
	Point nw(-1, -1);  // NW
	Point n(-1, 0);    // N
	Point ne(-1, 1);   // NE
	Point w(0, -1);    // W
	Point e(0, 1);     // E
	Point sw(1, -1);   // SW
	Point s(1, 0);     // S
	Point se(1, 1);    // SE

	direction[0] = nw;
	direction[1] = n;
	direction[2] = ne;
	direction[3] = w;
	direction[4] = e;
	direction[5] = sw;
	direction[6] = s;
	direction[7] = se;
}

// �ֺ��ϱ� ���ؼ� puzzle�� �츮�� ���ϴ� ���·� ��ȯ��Ű�� �����̴�.
void HidatoSolver::preprocessing(int puzz[], int _height, int _width) {

	// parameter�� �Ѱ��� �� ���� solver ��������� �ִ´�.
	height = _height;
	width = _width;
	len = height * width;

	int index = 0;
	max = 0;

	// len��ŭ�� Element��� ����
	E_array = new Element[len];
	memset(E_array, 0, len * sizeof(Element));

	// �ʱ� ������ ���� ������� �迭 ����
	existed = new bool[len + 1];
	memset(existed, 0, len + 1);

	// ������ �޾Ƽ� E_array�� ���, �̸� ������� ���ڴ� existed�� ���
	for (int i = 0; i < len; i++) {
		// ������ �״�� element�� �߰�
		E_array[i].value = puzz[i];

		// �̸� ������� ���ڸ�
		if (puzz[i] > 0)
			existed[E_array[i].value] = true;

		// �ƽ� �� change
		if (puzz[i] > max)
			max = puzz[i];
	}
}

// ������ ������ ������ ã�� search ����
void HidatoSolver::solve(int puzz[]) {
	Point start_point;
	// �������� ������
	if (findStart(start_point) == true)
		search(start_point, 2);
}

// ������ ã�� start_point�� �� �������ְ�
// ��ã���� false����
bool HidatoSolver::findStart(Point& start_point) {
	for (int i = 0; i < len; i++) {
		// ������ ã����
		// ������ ����ã��.. �ϴ� �˰��� �ؼ� �ð� �ٿ��� �ɵ�
		if (E_array[i].value == 1) {
			// start_point�� (x, y)�� �����ϰ� �Լ�����
			// x�� height�ΰŰ� y�� width�ΰ���
			start_point.x = (i % width);
			start_point.y = (i / width);
			return true;
		}
	}
	return false;
}

// order�� ����
bool HidatoSolver::search(Point p, int order) {

	// ������ ã���� ����
	if (order == max) return true;

	// �ش� ���� �̿�ã��
	// ���࿡ �̿��� �̹� ã������ ã���ʿ� ���� ���ʿ��� ������ �ϴ°��� - ���� �˰��� ���
	getNeighbors(p);

	// current_element ���۷����� ����
	Element* current_element = &E_array[p.x + width * p.y];
	Point moved_p;

	// �����ϴ� ������ ���
	if (existed[order]) {
		// 8 ����
		for (int i = 0; i < 8; i++) {
			// �̿��� �ִ��� Ȯ��
			if ((*current_element).neighbors[i]) {
				// �Ű��� ��ġ ����
				moved_p.x = p.x + direction[i].x;
				moved_p.y = p.y + direction[i].y;
				// �� �̿��� order(�̹��� �� ����)�� ������
				if (E_array[moved_p.x + width * moved_p.y].value == order) {
					// recursive�ϰ� ȣ�� �´� ���� ���ö� ����
					if (search(moved_p, order + 1))
						return true;
				}
			}
		}
		return false;
	}

	// �������� �ʴ� ������ ���
	for (int i = 0; i < 8; i++) {
		if ((*current_element).neighbors[i]) {
			// �Ű��� ��ġ ����
			moved_p.x = p.x + direction[i].x;
			moved_p.y = p.y + direction[i].y;
			// 0 ��, ��ĭ�� ���
			if (E_array[moved_p.x + width * moved_p.y].value == 0) {
				// �ϴ� order�� ������ �Ѵ��� recursive�ϰ� ����
				E_array[moved_p.x + width * moved_p.y].value = order;
				if (search(moved_p, order + 1)) return true;
				// recover�ϴ� �κ��̴�.
				E_array[moved_p.x + width * moved_p.y].value = 0;
			}
		}
	}
	return false;
}

// �ش� point�� �̿����� ã���༭ element�� neighbors�� �����ϴ� �Լ�
void HidatoSolver::getNeighbors(Point p) {

	int x = p.x;
	int y = p.y;
	Point moved_p;

	// �̿��� ã�ƾ��� current_element, ���۷����� ����
	Element* current_element = &E_array[x + width * y];
	//
	Element temp;

	// 8���� ����
	for (int i = 0; i < 8; i++) {
		// ���� ���� ���� �ִ� ���� ��ġ
		moved_p.x = x + direction[i].x;
		moved_p.y = y + direction[i].y;
		// ��ġ�� �ش��ϴ� element
		temp = E_array[moved_p.x + width * moved_p.y];
		// �̿��� ��Ʈ������ ����� ���
		if (moved_p.x < 0 || moved_p.y < 0 || moved_p.x >= width || moved_p.y >= height) continue;
		// ��Ʈ������������ ���ΰ��
		else if (temp.value < 0) continue;
		// ������ �̿��̸� true�� ����
		else (*current_element).neighbors[i] = true;
	}
}


// �츮�� ���� �ַ�� üũ
void HidatoSolver::checkSolution(int puzz[]) {
	for (int i = 0; i < len; i++) {
		// ��ĭ�̸�
		if (puzz[i] == 0) {
			// �ش� element�� ���� ä���ֱ�
			puzz[i] = E_array[i].value;
		}
	}
}


// height == number of rows
// width == number of columns

// ���̿� ���̸� �����ϰ� ������ ������ ��.
int *inputPuzz(ifstream& input, int &height, int& width)
{
	int w, h, len;
	input >> h >> w;

	height = h;
	width = w;

	len = w * h;
	int *puzz = new int[len];
	for (int i = 0; i < len; ++i) input >> puzz[i];

	// 1���� �迭 puzz�� �����Ѵ�.
	return puzz;
}

// �ݺ��Ǵ� �� print�� �Լ�
void printWall(int w) {
	int wall_count = (w * 3) + 1;
	while (wall_count--)
		cout << "XX";
	cout << endl;
}

// ����� ���̸� �޾Ƽ� w x h ������� ���� ���
void displayPuzz(int puzz[], int w)
{
	int height = _msize(puzz) / sizeof(int);
	printWall(w);
	for (int i = 0; i < height; ++i)
	{
		// ���� -1, �� ���� ����� ���
		if (puzz[i] == -1) {
			cout << "XX";				
			cout << "XXXX";
			if (i % w == w - 1) {
				cout << "XX" << endl;
				printWall(w);
			}
			continue;
		}
		// ���� �� �� �ϳ� ����ֱ�
		cout << "XX";
		// ���� �ƴϰ�  ��� ���
		if (puzz[i] == 0) {
			cout << " ? " << " ";
		}
		else {
			// ���� �ڸ��� ��� ��� ����
			if ((puzz[i] / 10) >= 1)               
				cout << " " << puzz[i] << " ";
			// ���� �ڸ��� ��� ��� ����
			else
				cout << " " << puzz[i] << "  ";
		}
		// ������ width�� ��� ���
		if (i % w == w - 1){
			cout << "XX";
			cout << endl;
			printWall(w);
		}
	}
}


// ���� �Ŵ���
void puzzManager(string txtFile)
{
	ifstream input;
	input.open(txtFile);

	int numOfPuzz;
	input >> numOfPuzz;
	int *puzz;

	while (numOfPuzz--)
	{
		// �ϴ� �� �κ��� �����̴�.
		int h, w;
		// input.txt�κ��� �Է� �ޱ�
		puzz = inputPuzz(input, h, w);

		// �ֹ� ����
		HidatoSolver solver;
		// ���� ���
		cout << "-----------------------------------------input puzzle-------------------------------------------------" << endl;
		displayPuzz(puzz, w);

		// �ֹ��� ������ Ǯ������ ��ó�� ����
		solver.preprocessing(puzz, h, w);
		// ����Ǯ��
		solver.solve(puzz);
		// ����Ȯ��
		solver.checkSolution(puzz);

		// ���� �����ֱ�
		cout << "-----------------------------------------check solution-----------------------------------------------" << endl;
		displayPuzz(puzz, w);
	}

	delete puzz;
}

int main() {

	puzzManager("input.txt");

	return 0;
}

/*
1. findStart - �˰��� ��� ���
2. search - getNeighbors - �ѹ� ������ �ٽ� �� �ʿ� ���� �ߺ�Ȯ�� ���
3. point, element, HidatoSolver, puzzlemanager 4���� ���ȭ���


4(�ذ�). ��� ���ڰ� �ϱ� -1�� �������� ó���ϴ� �Ŷ�
���ڸ�����(22) ���ڸ�����(5)ũ�� �ٸ��� \t����ؼ� �����ϰ� ���
�ٸ��� �̻ڰ� ����� �� ������ ����
ex)
---+---+---+
 1 | 22|  3|
---+---+---+
   | 5 |   |
---+---+---+
 4 | 9 | 7 |
---+---+---+
*/
