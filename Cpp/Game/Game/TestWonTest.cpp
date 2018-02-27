#include "stdafx.h"
#include "TestWonTest.h"

void initializeB(unsigned char b[BSIZE][BSIZE], unsigned char** board)
{
	for (size_t i = 0; i < BSIZE; i++)
	{
		for (size_t j = 0; j < BSIZE; j++)
		{
			board[i][j] = b[i][j];
		}
	}
}

void testtestwon() {

	cout << "testes do teste de tabuleiro ganho: " << endl;
	unsigned char win1[BSIZE][BSIZE] =
   {{ 1, 2, 2, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0 },
	{ 0, 2, 0, 1, 0, 0, 1, 1, 2, 0, 0, 0, 0, 1 },
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
	{ 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 } };

	unsigned char win2[BSIZE][BSIZE] =
	{ { 1, 2, 2, 1, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0 },
	{ 1, 2, 0, 1, 1, 0, 1, 1, 2, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 2, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 1, 2, 0, 0, 0, 0 },
	{ 0, 1, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 0 },
	{ 2, 0, 2, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2 },
	{ 2, 2, 2, 0, 0, 1, 0, 0, 1, 1, 2, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0 },
	{ 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
	{ 0, 2, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0 },
	{ 0, 0, 0, 1, 0, 0, 0, 0, 2, 1, 1, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 } };

	unsigned char win3[BSIZE][BSIZE] =
	{ { 1, 2, 2, 1, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0 },
	{ 1, 2, 0, 1, 1, 0, 1, 1, 2, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 2, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 1, 2, 0, 0, 0, 0 },
	{ 0, 1, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 0 },
	{ 2, 0, 2, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2 },
	{ 2, 2, 2, 0, 0, 1, 0, 0, 1, 1, 2, 0, 0, 0 },
	{ 0, 0, 1, 1, 1, 0, 0, 2, 0, 1, 0, 0, 1, 0 },
	{ 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0 },
	{ 0, 2, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1 },
	{ 1, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 } };

	unsigned char lost1[BSIZE][BSIZE] =
	{ { 1, 2, 2, 1, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0 },
	{ 1, 2, 0, 1, 1, 0, 1, 1, 2, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 2, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 1, 2, 0, 0, 0, 0 },
	{ 0, 1, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 0 },
	{ 2, 0, 2, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2 },
	{ 2, 2, 2, 0, 0, 1, 0, 0, 1, 1, 2, 0, 0, 0 },
	{ 0, 0, 1, 1, 1, 0, 0, 2, 0, 1, 0, 0, 1, 0 },
	{ 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0 },
	{ 0, 2, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1 },
	{ 1, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 } };

	unsigned char test3[BSIZE][BSIZE] =
	{ { 1, 2, 2, 1, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0 },
	{ 1, 2, 0, 1, 1, 0, 1, 1, 2, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 2, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 1, 2, 0, 0, 0, 0 },
	{ 0, 1, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 0 },
	{ 2, 0, 2, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2 },
	{ 2, 2, 2, 0, 0, 1, 0, 0, 1, 1, 2, 0, 0, 0 },
	{ 0, 0, 1, 1, 1, 0, 0, 2, 0, 1, 0, 0, 1, 0 },
	{ 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0 },
	{ 0, 2, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1 },
	{ 1, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 } };


	unsigned char** board = new unsigned char*[BSIZE];
	for (int i = 0; i < BSIZE; ++i)
		board[i] = new unsigned char[BSIZE];
	int sucsees = 0;
	int unsucsess = 0;

	initializeB(win1, board);
	if(hasWon(board,1))
		sucsees++;
	else
		unsucsess++;

	initializeB(win2, board);
	if (hasWon(board, 1))
		sucsees++;
	else
		unsucsess++;

	initializeB(win3, board);
	if (hasWon(board, 1))
		sucsees++;
	else
		unsucsess++;

	initializeB(lost1, board);
	if (!hasWon(board, 1)) 
		sucsees++;
	else
		unsucsess++;
	

	initializeB(test3, board);
	int hasWonTimes = 0;
		for (size_t i = 0; i < BSIZE; i++) {
			for (size_t j = 0; j < BSIZE; j++) {
				if (board[i][j] == EMPTY) {
					board[i][j] = MAXMIZEPLAYER;

					if (hasWon(board, 1))
						hasWonTimes++;

					board[i][j] = EMPTY;

				}
			}
		}
	if (hasWonTimes == 3)
		sucsees++;
	else
		unsucsess++;
	cout << "sucsess: " << sucsees << " unsucsess: " << unsucsess << endl;

}

