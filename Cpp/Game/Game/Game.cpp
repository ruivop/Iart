#include "stdafx.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

#define BSIZE 14
#define MAXDEPTH 3
#define MAXMIZEPLAYER 1
#define MINIMIZEPLAYER 2
#define EMPTY 0

const int MAX = 1000;
const int MIN = -1000;

struct Move
{
	int i, j;
};


int avalia(unsigned char board[BSIZE][BSIZE], unsigned char piece);

// Returns optimal value for current player (Initially called
// for root and maximizer)
int minimax(int depth, bool maximizingPlayer,
	unsigned char board[BSIZE][BSIZE], int alpha, int beta)
{
	// Terminating condition. i.e leaf node is reached
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


Move* choseNextPlay(unsigned char board[BSIZE][BSIZE]) {
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
				bestValue = max(bestValue, val);
				alpha = max(alpha, bestValue);

				// Alpha Beta Pruning
				if (beta <= alpha)
					break;
			}
			if (beta <= alpha)
				break;
		}
	}
	return m;
}

void mostrar(unsigned char board[BSIZE][BSIZE]) {
	cout << endl << "    ";
	for (size_t i = 0; i < BSIZE; i++) {
		cout << "|"<< setw(3) << i;
	}
	for (size_t i = 0; i < BSIZE; i++) {
		cout << endl << setw(3) << i;
		for (size_t j = 0; j < BSIZE; j++) {
			cout << " | "<< (int)board[i][j];
		}
	}
	cout << endl;
}

int avalia(unsigned char board[BSIZE][BSIZE], unsigned char piece) {
	int ret = 0;

	for (size_t i = 0; i < BSIZE-1; i++) {
		for (size_t j = 0; j < BSIZE; j++) {
			if (board[i][j] == piece && board[i][j] == board[i+1][j]) {
				ret++;
			}
		}
	}
	return ret;
}

// Driver Code
int main()
{
	/*
	0 e vazio
	1 e preto
	2 e branco
	*/
	unsigned char board[BSIZE][BSIZE] =
	{{ 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0 },
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
	{ 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 }};
	Move* m = choseNextPlay(board);
	cout << "The optimal value is: "
		<< m->i << ":" << m->j << endl;
	mostrar(board);

	cout << "a valiacao e " << avalia(board, 1) << endl;
	string a;
	cin >> a;
	return 0;
}