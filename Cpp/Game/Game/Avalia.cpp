#include "stdafx.h"
#include "Avalia.h"

using namespace std;

bool** avisited = new bool*[BSIZE];
unsigned char** aunvisited = new unsigned char*[BSIZE * BSIZE];
int unvisitedPivot = 0;
int unvisitedLast = 0;

void AinitilizeAvalia()
{
	for (int i = 0; i < BSIZE; ++i)
		avisited[i] = new bool[BSIZE];

	for (int i = 0; i < BSIZE * BSIZE; ++i)
		aunvisited[i] = new unsigned char[2];

	AinitilizeVisited();
	AinitilizeUnvisited();
}

void AinitilizeVisited()
{
	for (size_t i = 0; i < BSIZE; i++)
	{
		for (size_t j = 0; j < BSIZE; j++)
		{
			if (avisited[i][j])
				avisited[i][j] = false;
		}
	}
}

void AinitilizeUnvisited() {
	for (size_t i = 0; i < BSIZE * BSIZE; i++)
	{
		if (aunvisited[i][0] != 4)
		{
			aunvisited[i][0] = 4;
			aunvisited[i][1] = 4;
		}
	}
	unvisitedPivot = 0;
	unvisitedLast = 0;
}

void AreInUnvisited() {
	for (size_t i = 0; i <= unvisitedLast; i++)
	{
		aunvisited[i][0] = 4;
		aunvisited[i][1] = 4;
	}
	unvisitedPivot = 0;
	unvisitedLast = 0;
}


bool AcheckIfHas(unsigned char y, unsigned char x) {
	return avisited[y][x];
}

int eveluateReach(unsigned char** board, unsigned char y, unsigned char x) {
	bool hasTop = false;
	bool hasBotom = false;

	aunvisited[unvisitedPivot][0] = y;
	aunvisited[unvisitedPivot][1] = x;
	avisited[y][x] = true;

	//unvisitedLast + 1 is the size of the unvisited
	while (unvisitedPivot != unvisitedLast + 1) {
		unsigned char* a = aunvisited[unvisitedPivot];

		if (a[0] + 1 < BSIZE && !AcheckIfHas(a[0] + 1, a[1]) && board[a[0] + 1][a[1]] == board[y][x]) {
			avisited[a[0] + 1][a[1]] = true;
			unvisitedLast++;
			aunvisited[unvisitedLast][0] = a[0] + 1;
			aunvisited[unvisitedLast][1] = a[1];
		}
		if (a[0] - 1 >= 0 && !AcheckIfHas(a[0] - 1, a[1]) && board[a[0] - 1][a[1]] == board[y][x]) {
			avisited[a[0] - 1][a[1]] = true;
			unvisitedLast++;
			aunvisited[unvisitedLast][0] = a[0] - 1;
			aunvisited[unvisitedLast][1] = a[1];
		}
		if (a[1] + 1 < BSIZE && !AcheckIfHas(a[0], a[1] + 1) && board[a[0]][a[1] + 1] == board[y][x]) {
			avisited[a[0]][a[1] + 1] = true;
			unvisitedLast++;
			aunvisited[unvisitedLast][0] = a[0];
			aunvisited[unvisitedLast][1] = a[1] + 1;
		}
		if (a[1] - 1 >= 0 && !AcheckIfHas(a[0], a[1] - 1) && board[a[0]][a[1] - 1] == board[y][x]) {
			avisited[a[0]][a[1] - 1] = true;
			unvisitedLast++;
			aunvisited[unvisitedLast][0] = a[0];
			unvisited[unvisitedLast][1] = a[1] - 1;
		}
		if (a[0] == 0)
			hasTop = true;
		if (a[0] == BSIZE - 1)
			hasBotom = true;
		unvisitedPivot++;
	}
	return hasBotom && hasTop;
}

int avalia(unsigned char** board, unsigned char piece) {
	int acm = 0;
	for (size_t i = 0; i < BSIZE; i++) {
		for (size_t j = 0; j < BSIZE; j++) {
			if (board[i][j] == piece && !AcheckIfHas(i, j)) {
				acm += eveluateReach(board, static_cast<unsigned char>(i), static_cast<unsigned char>(j));
				AreInUnvisited();
			}
		}
	}
	AinitilizeVisited();
	AreInUnvisited();
	return false;
}