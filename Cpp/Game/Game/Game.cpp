#include "stdafx.h"
#include "Game.h"
#include "testAvalia.h"
#include <thread>

using namespace std;

int numberOfNodes = 0;

int avalia(unsigned char** board, unsigned char piece);
void mostrar(unsigned char** board);
extern Play** orders;
extern int ordersIndex[MAXMAXDEPTH];
int MAXDEPTH = 2;
unsigned char* lastPlayed = new unsigned char[2];
Play* FirstOrders[MAXMAXDEPTH];
Play* LastOrders[MAXMAXDEPTH];
float secondsOrdenate = 0;
float secondsAvalia = 0;
unsigned char pcColor = MINIMIZEPLAYER;
unsigned char playerColor = MAXMIZEPLAYER;
float secnds = 0;
int cv = 0;
int confidance = 0;
int numMaxFacRam = 50;


int getFacRam(int i)
{
	//if (i < 10)
		return 1;
	//else
	//	return MAXDEPTH;
}

int minimax(int depth, bool maximizingPlayer,
	unsigned char** board, int alpha, int beta)
{
	numberOfNodes++;
	if (hasWon(board, maximizingPlayer ? playerColor : pcColor))
	{
		return maximizingPlayer ? MIN + depth : MAX - depth;
	}

	if (depth >= MAXDEPTH) {
		return avalia(board, pcColor, depth);
	}

	if (maximizingPlayer) {
		int best = MIN;

		ordenate(board, depth, pcColor);
		int i1, j1, i2, j2;

		if (ordersIndex == 0) //se nao ha mais jogadas
			return avalia(board, pcColor, depth);

		for (int i = ordersIndex[depth] -1; i >= 0; i--)
		{
			Play * moveVisitando = &orders[depth][i];
			i1 = moveVisitando->move_first->i;
			j1 = moveVisitando->move_first->j;
			i2 = moveVisitando->move_second->i;
			j2 = moveVisitando->move_second->j;

			int val;
			board[i1][j1] = pcColor;
			board[i2][j2] = pcColor;
			val = minimax(depth + getFacRam(ordersIndex[depth] - i - 1), false, board, alpha, beta);
			board[i1][j1] = EMPTY;
			board[i2][j2] = EMPTY;
			best = max(best, val);
			alpha = max(alpha, best);

			if (beta <= alpha) { //ends the cicle
				break;
			}
		}
		return best;
	}
	else {
		int best = MAX;

		clock_t start = clock();
		ordenate(board, depth, playerColor);
		clock_t end = clock();
		secondsOrdenate += (float)(end - start) / CLOCKS_PER_SEC;
		int i1, j1, i2, j2;

		if (ordersIndex == 0)
			return avalia(board, pcColor, depth);

		for (int i = 0; i < ordersIndex[depth]; i++)
		{
			Play * moveVisitando = &orders[depth][i];
			i1 = moveVisitando->move_first->i;
			j1 = moveVisitando->move_first->j;
			i2 = moveVisitando->move_second->i;
			j2 = moveVisitando->move_second->j;

			board[i1][j1] = playerColor;
			board[i2][j2] = playerColor;
			int val = minimax(depth + getFacRam(i), true, board, alpha, beta);
			board[i1][j1] = EMPTY;
			board[i2][j2] = EMPTY;
			best = min(best, val);
			beta = min(beta, best);

			if (beta <= alpha) { //ends the cicle
				break;
			}
		}
		return best;
	}
}



Play* choseNextPlay(unsigned char** board) {
	int bestValue = MIN;
	Play* ant = nullptr;
	int alpha = MIN;
	int beta = MAX;
	cv = 0;

	ordenate(board, 0, pcColor);
	clock_t start = clock();
	int i1, j1, i2, j2;

	for(int i =0; i < ordersIndex[0]; i++)
	{
		cv++;
		Play * moveVisitando = &orders[0][i];
		i1 = moveVisitando->move_first->i;
		j1 = moveVisitando->move_first->j;
		i2 = moveVisitando->move_second->i;
		j2 = moveVisitando->move_second->j;

		board[i1][j1] = pcColor;
		board[i2][j2] = pcColor;
		int val = minimax(1, false, board, alpha, beta);
		board[i1][j1] = EMPTY;
		board[i2][j2] = EMPTY;

		if (val > bestValue) {
			bestValue = val;
			ant = moveVisitando;
			cout << " -> " << i1 << " : " << j1 << "    +    " << i2 << " : " << j2 << "   a: " << bestValue << endl;
		}
		alpha = max(alpha, bestValue);
		//pruning nerver haps in the first node
		if(cv%100 == 0)
			cout << cv << " ";
	}
	confidance = bestValue;
	cout << "melhor valor: " << bestValue << endl;
	cout << "ram factor: " << cv << endl;
	clock_t end = clock();
	secnds = (float)(end - start) / CLOCKS_PER_SEC;
	cout << "seconds in ordenate: " << secondsOrdenate << endl;
	cout << "seconds in ordenate: " << secondsAvalia << endl;
	cout << "seconds total: " << secnds << endl;
	return ant;
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
	Play* m;

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

		if (playerTurn(board))
			break;

		if (pcTurn(board))
			break;



	}
}

bool pcTurn(unsigned char** board)
{
	Play* m = choseNextPlay(board);
	cout << "pc play [" << m->move_first->i << "][" << m->move_first->j << "]  +  [" << m->move_second->i << "][" << m->move_second->j << "]" << endl;
	cout << "number of nodes was " << numberOfNodes << endl;

	numberOfNodes = 0;
	board[m->move_first->i][m->move_first->j] = pcColor;
	board[m->move_second->i][m->move_second->j] = pcColor;
	mostrar(board);
	if (hasWon(board, 1))
	{
		cout << "blacks won" << endl;
		return true;
	}
	return false;
}

bool playerTurn(unsigned char** board)
{
	int i1 = -1;
	int j1 = -1;
	int i2 = -1;
	int j2 = -1;
	cout << "write i1:" << endl;
	cin >> i1;
	cout << "write j1:" << endl;
	cin >> j1;
	cout << "write i2:" << endl;
	cin >> i2;
	cout << "write j2:" << endl;
	cin >> j2;
	board[i1][j1] = playerColor;
	board[i2][j2] = playerColor;

	cout << "you play:" << endl;
	mostrar(board);

	if (hasWon(board, 2))
	{
		cout << "whites won" << endl;
		return true;
	}
	return false;
}

// Driver Code
int main()
{
	for (int i = 0; i < MAXDEPTH; i++)
	{
		FirstOrders[i] = nullptr;
	}
	initializeOrdenate();
	initilizeTestWon();
	testtestwon();
	//testOrdenate();

	//testAvalia();
	thread first(initServer);
	//interfacePvC();
	string a;
	cin >> a;
	return 0;
}