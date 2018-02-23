#include "stdafx.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <vector>
#include <memory>

using namespace std;

#define BSIZE 14
#define MAXDEPTH 5
#define MAXMIZEPLAYER 1
#define MINIMIZEPLAYER 2
#define EMPTY 0

const int MAX = 1000;
const int MIN = -1000;

struct Move
{
	int i, j;
};
int numberOfNodes = 0;

int avalia(unsigned char** board, unsigned char piece);
bool hasWon(unsigned char** board, unsigned char piece);

// Returns optimal value for current player (Initially called
// for root and maximizer)
int minimax(int depth, bool maximizingPlayer,
	unsigned char** board, int alpha, int beta)
{
	numberOfNodes++;
	if(hasWon(board, MAXMIZEPLAYER))
	{
		return MAX-10;
	}
	if (depth >= MAXDEPTH) {
		unsigned char piece = MAXMIZEPLAYER;
		return avalia(board, piece);
	}

	if (maximizingPlayer) {
		int best = MIN;

		for (size_t i = 0; i < BSIZE; i++) {
			for (size_t j = 0; j < BSIZE; j++) {
				if (board[i][j] == EMPTY) {
					board[i][j] = MAXMIZEPLAYER;
					int val = minimax(depth + 1,
						false, board, alpha, beta);
					board[i][j] = EMPTY;
					best = max(best, val);
					alpha = max(alpha, best);

					// Alpha Beta Pruning
					if (beta <= alpha)
						break;
				}
			}
		}
		return best;
	}
	else {
		int best = MAX;

		for (size_t i = 0; i < BSIZE; i++) {
			for (size_t j = 0; j < BSIZE; j++) {
				if (board[i][j] == EMPTY) {
					board[i][j] = MINIMIZEPLAYER;
					int val = minimax(depth + 1,
						true, board, alpha, beta);
					board[i][j] = EMPTY;
					best = min(best, val);
					beta = min(beta, best);

					// Alpha Beta Pruning
					if (beta <= alpha)
						break;
				}
				if (beta <= alpha)
					break;
			}
		}
		return best;
	}
}


Move* choseNextPlay(unsigned char** board) {
	int bestValue = MIN;
	Move* m = new Move();
	int alpha = MIN;
	int beta = MAX;
	for (size_t i = 0; i < BSIZE - 1; i++) {
		for (size_t j = 0; j < BSIZE; j++) {
			if (board[i][j] == EMPTY) {
				board[i][j] = MAXMIZEPLAYER;
				int val = minimax(1, false, board, alpha, beta);
				board[i][j] = EMPTY;
				if (val > bestValue) {
					bestValue = val;
					m->i = i;
					m->j = j;
				}
				alpha = max(alpha, bestValue);

				// Alpha Beta Pruning
				if (beta <= alpha)
					break;
			}
			if (beta <= alpha)
				break;
		}
	}
	//cout << bestValue << endl;
	return m;
}

void mostrar(unsigned char** board) {
	cout << endl << "    ";
	for (size_t i = 0; i < BSIZE; i++) {
		cout << "|"<< setw(3) << i;
	}
	for (size_t i = 0; i < BSIZE; i++) {
		cout << endl << setw(3) << i;
		for (size_t j = 0; j < BSIZE; j++) {
			char c = board[i][j] == 0 ? ' ' : 'w';
			c = board[i][j] == 1 ? 'b' : c;
			cout << " | "<< c;
		}
	}
	cout << endl;
}

bool checkIfHas(vector<unsigned char*>* v, unsigned char y, unsigned char x) {
	for(size_t i = 0; i < v->size(); i++) {
		if ((*v)[i][0] == y && (*v)[i][1] == x) {
			return true;
		}
	}
	return false;
}

vector<unsigned char*>* findReach(unsigned char** board, unsigned char y, unsigned char x) {
	//alocate memory for the visited
	vector<unsigned char*>* visited = new vector<unsigned char*>();
	

	queue<unsigned char*> unvisited;
	unsigned char ss[2] = {y,x};
	unvisited.push(ss);

	while (!unvisited.empty()) {
		unsigned char* a = unvisited.front();

		if (!checkIfHas(visited, a[0] + 1,a[1]) && a[0] + 1 < BSIZE && board[a[0] + 1][a[1]] == board[y][x]) {
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
		if (!checkIfHas(visited, a[0], a[1]+1) && a[1] + 1 < BSIZE && board[a[0]][a[1] + 1] == board[y][x]) {
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
		visited->push_back(a);
		unvisited.pop();
	}

	return visited;
}

bool hasTopToBotom(vector<unsigned char*>* visited)
{
	bool hastop = false;
	bool hasbotom = false;
	for (size_t i =0; i < visited->size(); i++)
	{
		if((*visited)[i][0] == 0)
		{
			hastop = true;
		} else if((*visited)[i][0] == BSIZE-1)
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
	//return false;
	vector<unsigned char*>* visited = new vector<unsigned char*>();
	for (size_t i = 0; i < BSIZE - 1; i++) {
		for (size_t j = 0; j < BSIZE; j++) {
			if (board[i][j] == piece && !checkIfHas(visited, i, j)) {
				vector<unsigned char*>* ve = findReach(board, static_cast<unsigned char>(i), static_cast<unsigned char>(j));
				//tem que ter este comentario! hahaha
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

int avalia(unsigned char** board, unsigned char piece) {
	int ret = 0;

	for (size_t i = 0; i < BSIZE-1; i++) {
		for (size_t j = 0; j < BSIZE; j++) {
			if (board[i][j] == piece && board[i][j] == board[i + 1][j]) {
				ret++;
			}
		}
	}
	return ret;
}

void interfacePvC() {
	cout << "you are the whites" << endl;
	Move* m;

	unsigned char b[BSIZE][BSIZE] =
	{ { 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0 },
	{ 0, 0, 0, 1, 0, 0, 1, 1, 2, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 2, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 1, 2, 0, 0, 0, 0 },
	{ 0, 1, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 0 },
	{ 2, 0, 2, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2 },
	{ 2, 2, 2, 0, 0, 1, 0, 0, 1, 1, 2, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0 },
	{ 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
	{ 0, 2, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0 },
	{ 0, 0, 0, 1, 0, 0, 0, 0, 2, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 } };

	unsigned char** board = new unsigned char*[BSIZE];
	for (int i = 0; i < BSIZE; ++i)
		board[i] = new unsigned char[BSIZE];

	for (size_t i =0; i < BSIZE; i++)
	{
		for (size_t j =0; j < BSIZE; j++)
		{
			board[i][j] = b[i][j];
		}
	}

	cout << static_cast<int>(board[0][0]) << endl;
	mostrar(board);
	while (true) {
		int i = -1;
		int j = -1;
		cout << "write i:" << endl;
		cin >> i;
		cout << "write j:" << endl;
		cin >> j;
		board[i][j] = 2;

		cout << "you play:" << endl;
		mostrar(board);



		m = choseNextPlay(board);
		cout << "pc play i: " << m->i << ", j: " << m->j << endl;
		cout << "number of nodes was " << numberOfNodes << endl;
		numberOfNodes = 0;
		board[m->i][m->j] = 1;
		mostrar(board);
	}
}

// Driver Code
int main()
{
	/*
	0 e vazio
	1 e preto
	2 e branco
	*/
	/*unsigned char b[BSIZE][BSIZE] =
	{{ 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0 },
	{ 0, 0, 0, 1, 0, 0, 1, 1, 2, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 2, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 1, 2, 0, 0, 0, 0 },
	{ 0, 1, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 0 },
	{ 2, 0, 2, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2 },
	{ 2, 2, 2, 0, 0, 1, 0, 0, 1, 1, 2, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0 },
	{ 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 1, 0, 0 },
	{ 0, 2, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0 },
	{ 0, 0, 0, 1, 0, 0, 0, 0, 2, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 }};


	unsigned char** board = new unsigned char*[BSIZE];
	for (int i = 0; i < BSIZE; ++i)
		board[i] = new unsigned char[BSIZE];

	for (size_t i = 0; i < BSIZE; i++)
	{
		for (size_t j = 0; j < BSIZE; j++)
		{
			board[i][j] = b[i][j];
		}
	}*/

	interfacePvC();
	//mostrar(board);
	//VecCoods* v= findReach(board, 0, 6);
	//cout << hasWon(board,1) <<endl;
	string a;
	cin >> a;
	return 0;
}