#include "stdafx.h"
#include "Game.h"
#include "testAvalia.h"

using namespace std;

struct Move
{
	int i, j;
};
int numberOfNodes = 0;

int avalia(unsigned char** board, unsigned char piece);
void mostrar(unsigned char** board);

unsigned char* lastPlayed = new unsigned char[2];
int* FirstOrders = new int[MAXDEPTH];
extern int*** orders;

// Returns optimal value for current player (Initially called
// for root and maximizer)
int minimax(int depth, bool maximizingPlayer,
	unsigned char** board, int alpha, int beta)
{
	numberOfNodes++;
	if (hasWon(board, maximizingPlayer ? MINIMIZEPLAYER : MAXMIZEPLAYER))
	{
		return maximizingPlayer ? MIN + depth : MAX - depth;
	}
	if (depth >= MAXDEPTH) {
		unsigned char piece = MAXMIZEPLAYER;
		return avalia(board, piece);
	}

	if (maximizingPlayer) {
		int best = MIN;

		ordenate(board, depth, MAXMIZEPLAYER);
		int indiceVisitando = FirstOrders[depth];

		bool para = false;
		if (FirstOrders[depth] == -1)
			para = true;

		while (!para)
		{
			int i = indiceVisitando / BSIZE;
			int j = indiceVisitando % BSIZE;

			int val;
			board[i][j] = MAXMIZEPLAYER;
			val = minimax(depth + 1,
				false, board, alpha, beta);

			board[i][j] = EMPTY;
			best = max(best, val);
			alpha = max(alpha, best);

			if (beta <= alpha) { //ends the cicle
				break;
			}

			if (orders[depth][indiceVisitando / BSIZE][indiceVisitando%BSIZE] != -1)
				indiceVisitando = orders[depth][indiceVisitando / BSIZE][indiceVisitando%BSIZE];
			else
				para = true;
		}
		return best;
	}
	else {
		int best = MAX;

		ordenate(board, depth, MINIMIZEPLAYER);
		int indiceVisitando = FirstOrders[depth];

		bool para = false;
		if (FirstOrders[depth] == -1)
			para = true;

		while (!para)
		{
			int i = indiceVisitando / BSIZE;
			int j = indiceVisitando % BSIZE;

			board[i][j] = MINIMIZEPLAYER;
			int val = minimax(depth + 1,
				true, board, alpha, beta);
			board[i][j] = EMPTY;
			best = min(best, val);
			beta = min(beta, best);

			if (beta <= alpha) { //ends the cicle
				break;
			}

			if (orders[depth][indiceVisitando / BSIZE][indiceVisitando%BSIZE] != -1)
				indiceVisitando = orders[depth][indiceVisitando / BSIZE][indiceVisitando%BSIZE];
			else
				para = true;
		}
		return best;
	}
}



Move* choseNextPlay(unsigned char** board) {
	int bestValue = MIN;
	Move* m = new Move();
	int alpha = MIN;
	int beta = MAX;
	int cv = 0;

	ordenate(board, 0, MAXMIZEPLAYER);

	int indiceVisitando = FirstOrders[0];

	bool para = false;
	if (FirstOrders[0] == -1)
		para = true;
	while (!para)
	{
		cv++;

		int i = indiceVisitando / BSIZE;
		int j = indiceVisitando % BSIZE;
		board[i][j] = MAXMIZEPLAYER;
		int val = minimax(1, false, board, alpha, beta);
		board[i][j] = EMPTY;

		if (val > bestValue) {
			bestValue = val;
			m->i = i;
			m->j = j;
		}
		alpha = max(alpha, bestValue);
		cout << "feito i: " << i << " j: " << j << " com alfa de " << alpha << endl;
		//pruning nerver haps in the first node

		if (orders[0][indiceVisitando / BSIZE][indiceVisitando%BSIZE] != -1)
			indiceVisitando = orders[0][indiceVisitando / BSIZE][indiceVisitando%BSIZE];
		else
			para = true;
	}
	cout << "melhor valor: " << bestValue << endl;
	cout << "ram factor: " << cv << endl;
	return m;
}

void mostrar(unsigned char** board) {
	cout << endl << "    ";
	for (size_t i = 0; i < BSIZE; i++) {
		cout << "|" << setw(3) << i;
	}
	for (size_t i = 0; i < BSIZE; i++) {
		cout << endl << setw(3) << i;
		for (size_t j = 0; j < BSIZE; j++) {
			char c = board[i][j] == 0 ? ' ' : 'w';
			c = board[i][j] == 1 ? 'b' : c;
			cout << " | " << c;
		}
	}
	cout << endl;
}
/*
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
*/
void interfacePvC() {
	cout << "you are the whites" << endl;
	Move* m;

	unsigned char b[TESTBSIZE][TESTBSIZE] =
	{ { 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0 },
	{ 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0 },
	{ 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0 },
	{ 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
	{ 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0 },
	{ 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0 } };

	unsigned char** board = new unsigned char*[BSIZE];
	for (int i = 0; i < BSIZE; ++i)
		board[i] = new unsigned char[BSIZE];

	for (size_t i = 0; i < BSIZE; i++)
	{
		for (size_t j = 0; j < BSIZE; j++)
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

		if (hasWon(board, 2))
		{
			cout << "whites won" << endl;
			break;
		}


		m = choseNextPlay(board);
		cout << "pc play i: " << m->i << ", j: " << m->j << endl;
		cout << "number of nodes was " << numberOfNodes << endl;

		numberOfNodes = 0;
		board[m->i][m->j] = 1;
		mostrar(board);
		if (hasWon(board, 1))
		{
			cout << "blacks won" << endl;
			break;
		}
	}
}

// Driver Code
int main()
{
	for (int i = 0; i < MAXDEPTH; i++)
	{
		FirstOrders[i] = -1;
	}
	initializeOrdenate();
	initilizeTestWon();
	//testtestwon();
	testOrdenate();

	//testAvalia();
	interfacePvC();

	string a;
	cin >> a;
	return 0;
}