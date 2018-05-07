#include "stdafx.h"
#include "TestWonTest.h"

void initializeB(unsigned char b[TESTBSIZE][TESTBSIZE], unsigned char** board)
{
	for (size_t i = 0; i < TESTBSIZE; i++)
	{
		for (size_t j = 0; j < TESTBSIZE; j++)
		{
			board[i][j] = b[i][j];
		}
	}
}

void testtestwon() {
/*
	cout << "testes do teste de tabuleiro ganho: " << endl;
	unsigned char win1[TESTBSIZE][TESTBSIZE] =
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

	unsigned char win2[TESTBSIZE][TESTBSIZE] =
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

	unsigned char win3[TESTBSIZE][TESTBSIZE] =
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

	unsigned char lost1[TESTBSIZE][TESTBSIZE] =
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

	unsigned char test3[TESTBSIZE][TESTBSIZE] =
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


	unsigned char** board = new unsigned char*[TESTBSIZE];
	for (int i = 0; i < TESTBSIZE; ++i)
		board[i] = new unsigned char[TESTBSIZE];
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
		for (size_t i = 0; i < TESTBSIZE; i++) {
			for (size_t j = 0; j < TESTBSIZE; j++) {
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


	int succsessDisgnolay = 0;
	int unsuccsessDisgnolay = 0;
	unsigned char test4[TESTBSIZE][TESTBSIZE] =
	{ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
	initializeB(test4, board);
	if (!isDiagnonalyAdj(board,0,0,1))
		succsessDisgnolay++;
	else
		unsuccsessDisgnolay++;

	unsigned char test5[TESTBSIZE][TESTBSIZE] =
	{ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
	initializeB(test5, board);
	if (isDiagnonalyAdj(board, 1, 1, 1))
		succsessDisgnolay++;
	else
		unsuccsessDisgnolay++;

	unsigned char test6[TESTBSIZE][TESTBSIZE] =
	{ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
	initializeB(test6, board);
	if (!isDiagnonalyAdj(board, 1, 0, 1))
		succsessDisgnolay++;
	else
		unsuccsessDisgnolay++;

	unsigned char test7[TESTBSIZE][TESTBSIZE] =
	{ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
	initializeB(test7, board);
	if (isDiagnonalyAdj(board, 2, 2, 1))
		succsessDisgnolay++;
	else
		unsuccsessDisgnolay++;

	unsigned char test8[TESTBSIZE][TESTBSIZE] =
	{ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
	initializeB(test8, board);
	if (!isDiagnonalyAdj(board, 1, 3, 1))
		succsessDisgnolay++;
	else
		unsuccsessDisgnolay++;

	unsigned char test9[TESTBSIZE][TESTBSIZE] =
	{ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
	initializeB(test9, board);
	if (!isDiagnonalyAdj(board, 2, 3, 1))
		succsessDisgnolay++;
	else
		unsuccsessDisgnolay++;

	unsigned char test10[TESTBSIZE][TESTBSIZE] =
	{ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
	initializeB(test10, board);
	if (isDiagnonalyAdj(board, 0, 4, 1))
		succsessDisgnolay++;
	else
		unsuccsessDisgnolay++;


	unsigned char test11[TESTBSIZE][TESTBSIZE] =
	{ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
	initializeB(test11, board);
	if (isDiagnonalyAdj(board, 3, 1, 1))
		succsessDisgnolay++;
	else
		unsuccsessDisgnolay++;

	cout << "TEST ON isDiagnonalyAdj: sucsess: " << succsessDisgnolay << " unsucsess: " << unsuccsessDisgnolay << endl;
	cout << "sucsess: " << sucsees << " unsucsess: " << unsucsess << endl;
	*/
}

