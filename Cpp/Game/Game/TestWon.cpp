#include "stdafx.h"
#include "TestWon.h"

using namespace std;

vector<int*>* visitedaa = new vector<int*>(BSIZE*BSIZE);

bool checkIfHas(vector<int*>* v, unsigned char y, unsigned char x) {
	for (size_t i = 0; i < v->size(); i++) {
		if ((*v)[i][0] == y && (*v)[i][1] == x) {
			return true;
		}
	}
	return false;
}

vector<int*>* findReach(unsigned char** board, unsigned char y, unsigned char x) {
	//alocate memory for the visited
	vector<int*>* visited = new vector<int*>();


	queue<unsigned char*> unvisited;
	unsigned char* ss = new unsigned char[2];
	ss[0] = y;
	ss[1] = x;

	unvisited.push(ss);

	while (!unvisited.empty()) {
		unsigned char* a = unvisited.front();

		if (!checkIfHas(visited, a[0] + 1, a[1]) && a[0] + 1 < BSIZE && board[a[0] + 1][a[1]] == board[y][x]) {
			unsigned char* sss = new unsigned char[2];
			sss[0] = a[0] + 1;
			sss[1] = a[1];
			unvisited.push(sss);
		}
		if (!checkIfHas(visited, a[0] - 1, a[1]) && a[0] - 1 >= 0 && board[a[0] - 1][a[1]] == board[y][x]) {
			unsigned char* sss = new unsigned char[2];
			sss[0] = a[0] - 1;
			sss[1] = a[1];
			unvisited.push(sss);
		}
		if (!checkIfHas(visited, a[0], a[1] + 1) && a[1] + 1 < BSIZE && board[a[0]][a[1] + 1] == board[y][x]) {
			unsigned char* sss = new unsigned char[2];
			sss[0] = a[0];
			sss[1] = a[1] + 1;
			unvisited.push(sss);
		}
		if (!checkIfHas(visited, a[0], a[1] - 1) && a[1] - 1 >= 0 && board[a[0]][a[1] - 1] == board[y][x]) {
			unsigned char* sss = new unsigned char[2];
			sss[0] = a[0];
			sss[1] = a[1] - 1;
			unvisited.push(sss);
		}
		int* e = new int[2];
		e[0] = a[0];
		e[1] = a[1];
		visited->push_back(e);
		delete[] a;
		unvisited.pop();
	}
	return visited;
}

bool hasTopToBotom(vector<int*>* visited)
{
	bool hastop = false;
	bool hasbotom = false;
	for (size_t i = 0; i < visited->size(); i++)
	{
		if ((*visited)[i][0] == 0)
		{
			hastop = true;
		}
		else if ((*visited)[i][0] == BSIZE - 1)
		{
			hasbotom = true;
		}
	}
	if (hasbotom && hastop)
		return true;
	else
		return false;
}

bool hasWon(unsigned char** board, unsigned char piece)
{
	vector<int*>* visited = new vector<int*>();
	for (size_t i = 0; i < BSIZE; i++) {
		for (size_t j = 0; j < BSIZE; j++) {
			if (board[i][j] == piece && !checkIfHas(visited, i, j)) {
				vector<int*>* ve = findReach(board, static_cast<unsigned char>(i), static_cast<unsigned char>(j));
				visited->insert(visited->end(), ve->begin(), ve->end());
				if (hasTopToBotom(ve))
					return true;
				delete ve;
			}
		}
	}
	delete visited;
	return false;
}