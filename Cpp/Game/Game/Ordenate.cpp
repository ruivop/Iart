#include "stdafx.h"
#include "Ordenate.h"

/*array of */
Play** orders = new Play*[MAXMAXDEPTH];
int ordersIndex[MAXMAXDEPTH];
int** scores = new int*[BSIZE];
extern unsigned char* lastPlayed;
extern int MAXDEPTH;
extern Play* FirstOrders[MAXMAXDEPTH];
extern Play* LastOrders[MAXMAXDEPTH];
Quadrants* numMorePieces = new Quadrants[4];

int ifNeibLastPlayed(unsigned char l, unsigned char c);

void initializeOrdenate()
{
	for (int i = 0; i < MAXMAXDEPTH; i++)
	{
		orders[i] = new Play[BSIZE * BSIZE * BSIZE * BSIZE / 4];
		ordersIndex[i] = 0;
	}
	for (int i = 0; i < BSIZE; ++i)
		scores[i] = new int[BSIZE];

}

void get_next_pos(int depth, Play* play)
{

	Play* moveVisitando = FirstOrders[depth];

	if (moveVisitando == nullptr) {
		play->previous_play = nullptr;
		play->next_play = nullptr;
		FirstOrders[depth] = play;
		LastOrders[depth] = play;
		return;
	}
	Play* ant = nullptr;

	while (moveVisitando != nullptr)
	{
		//se o score do que estamos a querer por for maior do que o que estamos a visitar, entao poe o que estamos querer por na posicao do que estamos a visitar
		if (play->value >= moveVisitando->value)
		{
			//se o anterior for nulo e porque temos de por no primeiro valor
			if (ant == nullptr) {
				play->next_play = FirstOrders[depth];
				play->previous_play = nullptr;
				FirstOrders[depth]->previous_play = play;
				FirstOrders[depth] = play;
			}
			else {
				play->next_play = moveVisitando;
				play->previous_play = ant;
				ant->next_play = play;
				moveVisitando->previous_play = play;
			}
			return;
		}
		ant = moveVisitando;

		moveVisitando = moveVisitando->next_play;
	}

	LastOrders[depth] = play;
	play->next_play = nullptr;
	play->previous_play = ant;
	ant->next_play = play;
}

bool sortPlays(Play i, Play j) { return i.value > j.value; }

int** ordenate(unsigned char ** b, int depth, unsigned char player)
{
	int ** ret = avaliaBoard(b, player);

	/*cout << endl << "    ";
	for (size_t i = 0; i < BSIZE; i++) {
		cout << "|" << setw(4) << i;
	}
	for (size_t i = 0; i < BSIZE; i++) {
		cout << endl << setw(3) << i;
		for (size_t j = 0; j < BSIZE; j++) {
			cout << " | " << setw(2) << ret[i][j];
		}
	}
	cout << endl;*/


	FirstOrders[depth] = nullptr;
	LastOrders[depth] = nullptr;
	ordersIndex[depth] = 0;

	for (unsigned int i = 0; i < BSIZE; i++) {
		for (unsigned int j = 0; j < BSIZE; j++) {
			if (b[i][j] == EMPTY)
			{
				b[i][j] = player;
				for (unsigned int k = i; k < BSIZE; k++) {
					for (unsigned int y = 0; y < BSIZE; y++) {
						if (b[k][y] == EMPTY)
						{
							b[k][y] = player;
							if (!isDiagnonalyAdj(b, i, j, player) && !isDiagnonalyAdj(b, k, y, player)) {
								if ((k == i && y == j + 1) || (k == i + 1 && y == j) || (k == i + 1 && y == j + 1))
									orders[depth][ordersIndex[depth]].value = scores[i][j] + scores[k][y] + 100;
								else
									orders[depth][ordersIndex[depth]].value = scores[i][j] + scores[k][y];
								orders[depth][ordersIndex[depth]].move_first->i = i;
								orders[depth][ordersIndex[depth]].move_first->j = j;
								orders[depth][ordersIndex[depth]].move_second->i = k;
								orders[depth][ordersIndex[depth]].move_second->j = y;
								ordersIndex[depth] += 1;
							}
							b[k][y] = EMPTY;
						}
					}
				}
				b[i][j] = EMPTY;
			}
		}
	}
	std::sort(orders[depth], orders[depth] + ordersIndex[depth], sortPlays);
	return ret;
}

bool wayToSort(Quadrants i, Quadrants j) { return i.value > j.value; }

int** avaliaBoard(unsigned char ** b, unsigned char player)
{
	for (size_t i = 0; i < BSIZE; i++) {
		for (size_t j = 0; j < BSIZE; j++) {
			if (b[i][j] == EMPTY && !isDiagnonalyAdj(b, i, j, player))
			{
				scores[i][j] = calcNumVizinhos(b, i, j);
				scores[i][j] += ifNeibLastPlayed(i, j);
			}
			else
			{
				scores[i][j] = -1;
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		numMorePieces[i].index = i;
		numMorePieces[i].value = 0;
	}

	for (size_t i = 0; i < BSIZE; i++)
		for (size_t j = 0; j < BSIZE; j++)
			if (b[i][j] != EMPTY)
				numMorePieces[2 * (i / 7) + j / 7].value++;

	std::sort(numMorePieces, numMorePieces + 4, wayToSort);

	for (size_t i = 0; i < BSIZE; i++) {
		for (size_t j = 0; j < BSIZE; j++) {
			if (scores[i][j] != -1) {
				if (2 * (i / 7) + j / 7 == numMorePieces[0].index)
					scores[i][j] += 3;
				else if (2 * (i / 7) + j / 7 == numMorePieces[1].index)
					scores[i][j] += 2;
				else if (2 * (i / 7) + j / 7 == numMorePieces[2].index)
					scores[i][j] += 1;
			}
		}
	}
	return scores;
}

int calcNumVizinhos(unsigned char ** board, const int i, const int j)
{
	int numV = 0;
	if (i + 1 < BSIZE && board[i + 1][j] != EMPTY)
		numV++;
	if (j - 1 >= 0 && board[i][j - 1] != EMPTY)
		numV++;
	if (i - 1 >= 0 && board[i - 1][j] != EMPTY)
		numV++;
	if (j + 1 < BSIZE && board[i][j + 1] != EMPTY)
		numV++;

	if (numV == 0)
		return 0;
	if (numV == 1)
		return 4;
	return 6;
}

int ifNeibLastPlayed(unsigned char l, unsigned char c)
{
	if (lastPlayed[0] + 1 == l && lastPlayed[1] == c)
		return 6;
	if (lastPlayed[0] - 1 == l && lastPlayed[1] == c)
		return 6;
	if (lastPlayed[0] == l && lastPlayed[1] + 1 == c)
		return 6;
	if (lastPlayed[0] == l && lastPlayed[1] - 1 == c)
		return 6;
	return 0;
}


bool isDiagnonalyAdj(unsigned char** board, int i, int j, unsigned char colour) {
	if (i + 1 < BSIZE && j + 1 < BSIZE && board[i + 1][j + 1] == colour && board[i + 1][j] != colour && board[i][j + 1] != colour)
		return true;
	if (i + 1 < BSIZE && j - 1 >= 0 && board[i + 1][j - 1] == colour && board[i + 1][j] != colour && board[i][j - 1] != colour)
		return true;
	if (i - 1 >= 0 && j - 1 >= 0 && board[i - 1][j - 1] == colour && board[i - 1][j] != colour && board[i][j - 1] != colour)
		return true;
	if (i - 1 >= 0 && j + 1 < BSIZE && board[i - 1][j + 1] == colour && board[i - 1][j] != colour && board[i][j + 1] != colour)
		return true;
	return false;
}