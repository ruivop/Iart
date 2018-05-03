#include "stdafx.h"
#include "Ordenate.h"

/*array of */
int* ** orders = new int**[MAXDEPTH];
int** scores = new int*[BSIZE];
extern unsigned char* lastPlayed;
extern int* FirstOrders;

int ifNeibLastPlayed(unsigned char l, unsigned char c);

void initializeOrdenate()
{
	for (int i = 0; i < MAXDEPTH; i++)
	{
		orders[i] = new int*[BSIZE];
		for (int j = 0; j < BSIZE; j++)
		{
			orders[i][j] = new int[BSIZE];
			for (int u = 0; u < BSIZE; u++)
			{
				orders[i][j][u] = -1;
			}
		}
	}
	for (int i = 0; i < BSIZE; ++i)
		scores[i] = new int[BSIZE];

}

void get_next_pos(int depth, unsigned int l, unsigned int c)
{

	int indiceVisitando = FirstOrders[depth];

	if (indiceVisitando == -1) {
		FirstOrders[depth] = l * BSIZE + c;
		return;
	}
	int ant = -1;

	while (orders[depth][indiceVisitando / BSIZE][indiceVisitando%BSIZE] != -1)
	{
		//se o score do que estamos a querer por for maior do que o que estamos a visitar, entao poe o que estamos querer por na posicao do que estamos a visitar
		if (scores[l][c] >= scores[indiceVisitando / BSIZE][indiceVisitando%BSIZE])
		{
			//se o anterioir for igual a -1 e porque temos de por no primeiro valor
			if (ant == -1) {
				orders[depth][l][c] = FirstOrders[depth];
				FirstOrders[depth] = l * BSIZE + c;
			}
			else {
				orders[depth][ant / BSIZE][ant%BSIZE] = l * BSIZE + c;
				orders[depth][l][c] = indiceVisitando;
			}
			return;
		}
		ant = indiceVisitando;

		indiceVisitando = orders[depth][indiceVisitando / BSIZE][indiceVisitando%BSIZE];
	}

	orders[depth][indiceVisitando / BSIZE][indiceVisitando%BSIZE] = l * BSIZE + c;
	orders[depth][l][c] = -1;
}

int** ordenate(unsigned char ** b, int depth)
{
	int ** ret = avaliaBoard(b);

	for (unsigned int i = 0; i < BSIZE; i++) {
		for (unsigned int j = 0; j < BSIZE; j++) {
			orders[depth][i][j] = -1;
		}
	}

	for (unsigned int i = 0; i < BSIZE; i++) {
		for (unsigned int j = 0; j < BSIZE; j++) {
			if (scores[i][j] != -1)
			{
				get_next_pos(depth, i, j);
			}
		}
	}

	/*int indiceVisitando = FirstOrders[depth];

	bool para = false;
	if (FirstOrders[depth] == -1)
		para = true;
	while (!para)
	{
		cout << "   >" << (int)indiceVisitando / BSIZE << " - " << indiceVisitando % BSIZE << " s: " << scores[indiceVisitando / BSIZE][indiceVisitando%BSIZE];

		if (orders[depth][indiceVisitando / BSIZE][indiceVisitando%BSIZE] != -1)
			indiceVisitando = orders[depth][indiceVisitando / BSIZE][indiceVisitando%BSIZE];
		else
			para = true;
	}
	cout << endl;*/
	return ret;
}

int** avaliaBoard(unsigned char ** b)
{
	for (size_t i = 0; i < BSIZE; i++) {
		for (size_t j = 0; j < BSIZE; j++) {
			if (b[i][j] == EMPTY)
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