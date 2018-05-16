#include "stdafx.h"
#include "Game.h"
#include "testAvalia.h"

using namespace std;

int numberOfNodes = 0;

int avalia(unsigned char** board, unsigned char piece);
void mostrar(unsigned char** board);

unsigned char* lastPlayed = new unsigned char[2];
Play* FirstOrders[MAXDEPTH];
Play* LastOrders[MAXDEPTH];
float secondsOrdenate = 0;

// Returns optimal value for current player (Initially called
// for root and maximizer)
int minimax(int depth, bool maximizingPlayer,
	unsigned char** board, int alpha, int beta)
{
	numberOfNodes++;
	if (depth >= MAXDEPTH) {
		return avalia(board, MAXMIZEPLAYER, depth);
	}

	if (maximizingPlayer) {
		int best = MIN;

		ordenate(board, depth, MAXMIZEPLAYER);
		Play* moveVisitando = FirstOrders[depth];
		int i1, j1, i2, j2;

		if (moveVisitando == nullptr) //se nao ha mais jogadas
			return avalia(board, MAXMIZEPLAYER, depth);

		while (moveVisitando != nullptr)
		{
			i1 = moveVisitando->move_first->i;
			j1 = moveVisitando->move_first->j;
			i2 = moveVisitando->move_second->i;
			j2 = moveVisitando->move_second->j;

			int val;
			board[i1][j1] = MAXMIZEPLAYER;
			board[i2][j2] = MAXMIZEPLAYER;
			val = minimax(depth + 1, false, board, alpha, beta);
			board[i1][j1] = EMPTY;
			board[i2][j2] = EMPTY;
			if (val == MAX - MAXDEPTH) //um filho e vencedor
			{
				const int score = avalia(board, MAXMIZEPLAYER, depth);
				if (score >= MAX - MAXDEPTH)
					return score;
				return val;
			}
			best = max(best, val);
			alpha = max(alpha, best);

			if (beta <= alpha) { //ends the cicle
				break;
			}

			moveVisitando = moveVisitando->next_play;
		}
		return best;
	}
	else {
		int best = MAX;

		clock_t start = clock();
		ordenate(board, depth, MINIMIZEPLAYER);
		clock_t end = clock();
		secondsOrdenate += (float)(end - start) / CLOCKS_PER_SEC;
		Play* moveVisitando = LastOrders[depth];
		int i1, j1, i2, j2;

		if (moveVisitando == nullptr)
			return avalia(board, MAXMIZEPLAYER, depth);

		while (moveVisitando != nullptr)
		{
			i1 = moveVisitando->move_first->i;
			j1 = moveVisitando->move_first->j;
			i2 = moveVisitando->move_second->i;
			j2 = moveVisitando->move_second->j;

			board[i1][j1] = MINIMIZEPLAYER;
			board[i2][j2] = MINIMIZEPLAYER;
			int val = minimax(depth + 1, true, board, alpha, beta);
			board[i1][j1] = EMPTY;
			board[i2][j2] = EMPTY;
			if (val <= MIN + MAXDEPTH) //um filho e perdedor
			{
				const int score = avalia(board, MAXMIZEPLAYER, depth);
				if (score <= MIN + MAXDEPTH)
					return score;
				return val;
			}
			best = min(best, val);
			beta = min(beta, best);

			if (beta <= alpha) { //ends the cicle
				break;
			}

			moveVisitando = moveVisitando->previous_play;
		}
		return best;
	}
}



Play* choseNextPlay(unsigned char** board) {
	int bestValue = MIN;
	Play* ant = nullptr;
	int alpha = MIN;
	int beta = MAX;
	int cv = 0;

	ordenate(board, 0, MAXMIZEPLAYER);
	clock_t start = clock();
	Play* moveVisitando = FirstOrders[0];
	int i1, j1, i2, j2;

	while (moveVisitando != nullptr)
	{
		cv++;

		i1 = moveVisitando->move_first->i;
		j1 = moveVisitando->move_first->j;
		i2 = moveVisitando->move_second->i;
		j2 = moveVisitando->move_second->j;

		board[i1][j1] = MAXMIZEPLAYER;
		board[i2][j2] = MAXMIZEPLAYER;
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
		moveVisitando = moveVisitando->next_play;
	}
	cout << "melhor valor: " << bestValue << endl;
	cout << "ram factor: " << cv << endl;
	clock_t end = clock();
	float seconds = (float)(end - start) / CLOCKS_PER_SEC;
	cout << "seconds in ordenate: " << secondsOrdenate << " seconds total: " << seconds << endl;
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
		cout << "pc play [" << m->move_first->i << "][" << m->move_first->j << "]  +  [" << m->move_second->i << "][" << m->move_second->j << "]" << endl;
		cout << "number of nodes was " << numberOfNodes << endl;

		numberOfNodes = 0;
		board[m->move_first->i][m->move_first->j] = MAXMIZEPLAYER;
		board[m->move_second->i][m->move_second->j] = MAXMIZEPLAYER;
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
		FirstOrders[i] = nullptr;
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