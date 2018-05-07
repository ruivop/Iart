#include "stdafx.h"
#include "TestWon.h"

using namespace std;

bool** visited = new bool*[BSIZE];
unsigned char** unvisited = new unsigned char*[BSIZE * BSIZE];
int unvisitedPivot = 0;
int unvisitedLast = 0;

void initilizeTestWon()
{
	for (int i = 0; i < BSIZE; ++i)
		visited[i] = new bool[BSIZE];

	for (int i = 0; i < BSIZE * BSIZE; ++i)
		unvisited[i] = new unsigned char[2];

	initilizeVisited();
	initilizeUnvisited();
}

void initilizeVisited()
{
	for (size_t i = 0; i < BSIZE; i++)
	{
		for (size_t j = 0; j < BSIZE; j++)
		{
			visited[i][j] = false;
		}
	}
}

void initilizeUnvisited(){
	for (size_t i = 0; i < BSIZE * BSIZE; i++)
	{
		if(unvisited[i][0] != 4)
		{
			unvisited[i][0] = 4;
			unvisited[i][1] = 4;
		}
	}
	unvisitedPivot = 0;
	unvisitedLast = 0;
}

void reInUnvisited() {
	unvisitedPivot = 0;
	unvisitedLast = 0;
}


bool checkIfHas(unsigned char y, unsigned char x) {
	return visited[y][x];
}

bool findReach(unsigned char** board, unsigned char y, unsigned char x) {
	bool hasTop = false;
	bool hasBotom = false;
	bool hasRigth = false;
	bool hasLeft = false;

	unvisited[unvisitedPivot][0] = y;
	unvisited[unvisitedPivot][1] = x;
	visited[y][x] = true;

	//unvisitedLast + 1 is the size of the unvisited
	while (unvisitedPivot != unvisitedLast + 1) {
		unsigned char* a = unvisited[unvisitedPivot];

		if (a[0] + 1 < BSIZE && !checkIfHas(a[0] + 1, a[1]) && board[a[0] + 1][a[1]] == board[y][x]) {
			visited[a[0]+1][a[1]] = true;
			unvisitedLast++;
			unvisited[unvisitedLast][0] = a[0] + 1;
			unvisited[unvisitedLast][1] = a[1];
		}
		if (a[0] - 1 >= 0 && !checkIfHas(a[0] - 1, a[1]) && board[a[0] - 1][a[1]] == board[y][x]) {
			visited[a[0] -1][a[1]] = true;
			unvisitedLast++;
			unvisited[unvisitedLast][0] = a[0] - 1;
			unvisited[unvisitedLast][1] = a[1];
		}
		if (a[1] + 1 < BSIZE && !checkIfHas(a[0], a[1] + 1) && board[a[0]][a[1] + 1] == board[y][x]) {
			visited[a[0]][a[1]+1] = true;
			unvisitedLast++;
			unvisited[unvisitedLast][0] = a[0];
			unvisited[unvisitedLast][1] = a[1] + 1;
		}
		if (a[1] - 1 >= 0 && !checkIfHas(a[0], a[1] - 1) && board[a[0]][a[1] - 1] == board[y][x]) {
			visited[a[0]][a[1]-1] = true;
			unvisitedLast++;
			unvisited[unvisitedLast][0] = a[0];
			unvisited[unvisitedLast][1] = a[1] - 1;
		}
		if (a[0] == 0) 
			hasTop = true;
		else if (a[0] == BSIZE - 1)
			hasBotom = true;
		if (a[1] == 0)
			hasLeft = true;
		else if (a[1] == BSIZE - 1)
			hasRigth = true;
		unvisitedPivot++;
	}
	return board[y][x] == BLACKS ? hasBotom && hasTop : hasRigth && hasLeft;
}

bool hasWon(unsigned char** board, unsigned char piece) {
	for (size_t i = 0; i < BSIZE; i++) {
		for (size_t j = 0; j < BSIZE; j++) {
			if (board[i][j] == piece && !checkIfHas(i, j)) {
				if(findReach(board, static_cast<unsigned char>(i), static_cast<unsigned char>(j))) {
					initilizeVisited();
					reInUnvisited();
					return true;
				}
				reInUnvisited();
			}
		}
	}
	initilizeVisited();
	reInUnvisited();
	return false;
}




void visitPos(unsigned char** board, const unsigned char y, const unsigned char x)
{
	const unsigned char piceToVisit = board[y][x];

	unvisited[unvisitedPivot][0] = y;
	unvisited[unvisitedPivot][1] = x;
	visited[y][x] = true;

	//unvisitedLast + 1 is the size of the unvisited
	while (unvisitedPivot != unvisitedLast + 1) {
		unsigned char* a = unvisited[unvisitedPivot];

		if (a[0] + 1 < BSIZE && !checkIfHas(a[0] + 1, a[1]) && board[a[0] + 1][a[1]] == piceToVisit) {
			visited[a[0] + 1][a[1]] = true;
			unvisitedLast++;
			unvisited[unvisitedLast][0] = a[0] + 1;
			unvisited[unvisitedLast][1] = a[1];
		}
		if (a[0] - 1 >= 0 && !checkIfHas(a[0] - 1, a[1]) && board[a[0] - 1][a[1]] == piceToVisit) {
			visited[a[0] - 1][a[1]] = true;
			unvisitedLast++;
			unvisited[unvisitedLast][0] = a[0] - 1;
			unvisited[unvisitedLast][1] = a[1];
		}
		if (a[1] + 1 < BSIZE && !checkIfHas(a[0], a[1] + 1) && board[a[0]][a[1] + 1] == piceToVisit) {
			visited[a[0]][a[1] + 1] = true;
			unvisitedLast++;
			unvisited[unvisitedLast][0] = a[0];
			unvisited[unvisitedLast][1] = a[1] + 1;
		}
		if (a[1] - 1 >= 0 && !checkIfHas(a[0], a[1] - 1) && board[a[0]][a[1] - 1] == piceToVisit) {
			visited[a[0]][a[1] - 1] = true;
			unvisitedLast++;
			unvisited[unvisitedLast][0] = a[0];
			unvisited[unvisitedLast][1] = a[1] - 1;
		}
		unvisitedPivot++;
	}
	
}

int evaluateReach(unsigned char** board, unsigned char y, unsigned char x) {
	unsigned char ytopest = BSIZE;
	unsigned char ybotomest = 0;
	unsigned char xrigthes = 0;
	unsigned char xleftest = BSIZE;
	bool hasTop = false;
	bool hasBotom = false;
	bool hasRigth = false;
	bool hasLeft = false;

	const unsigned char piceToVisit = board[y][x];

	unvisited[unvisitedPivot][0] = y;
	unvisited[unvisitedPivot][1] = x;
	visited[y][x] = true;

	//unvisitedLast + 1 is the size of the unvisited
	while (unvisitedPivot != unvisitedLast + 1) {
		unsigned char* a = unvisited[unvisitedPivot];

		if (a[0] + 1 < BSIZE && !checkIfHas(a[0] + 1, a[1]) && board[a[0] + 1][a[1]] == piceToVisit) {
			visited[a[0] + 1][a[1]] = true;
			unvisitedLast++;
			unvisited[unvisitedLast][0] = a[0] + 1;
			unvisited[unvisitedLast][1] = a[1];
		}
		if (a[0] - 1 >= 0 && !checkIfHas(a[0] - 1, a[1]) && board[a[0] - 1][a[1]] == piceToVisit) {
			visited[a[0] - 1][a[1]] = true;
			unvisitedLast++;
			unvisited[unvisitedLast][0] = a[0] - 1;
			unvisited[unvisitedLast][1] = a[1];
		}
		if (a[1] + 1 < BSIZE && !checkIfHas(a[0], a[1] + 1) && board[a[0]][a[1] + 1] == piceToVisit) {
			visited[a[0]][a[1] + 1] = true;
			unvisitedLast++;
			unvisited[unvisitedLast][0] = a[0];
			unvisited[unvisitedLast][1] = a[1] + 1;
		}
		if (a[1] - 1 >= 0 && !checkIfHas(a[0], a[1] - 1) && board[a[0]][a[1] - 1] == piceToVisit) {
			visited[a[0]][a[1] - 1] = true;
			unvisitedLast++;
			unvisited[unvisitedLast][0] = a[0];
			unvisited[unvisitedLast][1] = a[1] - 1;
		}
		ytopest = min(ytopest, a[0]);
		ybotomest = max(ybotomest, a[0]);
		xrigthes = max(xrigthes, a[1]);
		xleftest = min(xleftest, a[1]);

		unvisitedPivot++;
	}

	if (ytopest == 0)
		hasTop = true;
	if (ybotomest == BSIZE - 1)
		hasBotom = true;
	if (xleftest == 0)
		hasLeft = true;
	if (xrigthes == BSIZE - 1)
		hasRigth = true;

	int ret = 0;
	if (piceToVisit == BLACKS)
		ret = hasBotom && hasTop ? 2 * MAX : pow((ybotomest - ytopest)*FACTOROBJECTIVE + (xrigthes - xleftest)*FACTORNONOBJECTIVE, EXPFACTOR);
	else
		ret = hasRigth && hasLeft ? 2 * MIN : -(pow((ybotomest - ytopest)*FACTORNONOBJECTIVE + (xrigthes - xleftest)*FACTOROBJECTIVE, EXPFACTOR));
	return ret;
}


int avalia(unsigned char** board, unsigned char piece, int depth) {
	int acm = 0;
	for (size_t i = 0; i < BSIZE; i++) {
		for (size_t j = 0; j < BSIZE; j++) {
			if (board[i][j] != EMPTY && !checkIfHas(i, j)) {
				acm += evaluateReach(board, static_cast<unsigned char>(i), static_cast<unsigned char>(j));
				reInUnvisited();
			}
		}
	}
	initilizeVisited();
	reInUnvisited();
	if (piece == WHITES)
		acm = -acm;
	if (acm > MAX)
		return MAX - depth;
	if (acm < MIN)
		return MIN + depth;
	return acm;
}