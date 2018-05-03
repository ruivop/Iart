#include "stdafx.h"
#include "TestOredenate.h"
#include "TestWonTest.h"

using namespace std;

unsigned char** testBoardE = new unsigned char*[TESTBSIZE];
extern unsigned char* lastPlayed;

void initializeEvalO(unsigned char b[TESTBSIZE][TESTBSIZE], unsigned char** board)
{
	for (size_t i = 0; i < TESTBSIZE; i++)
	{
		for (size_t j = 0; j < TESTBSIZE; j++)
		{
			board[i][j] = b[i][j];
		}
	}
}

bool testOrdenates(unsigned char b1[TESTBSIZE][TESTBSIZE], int b2[TESTBSIZE][TESTBSIZE])
{
	initializeEvalO(b1, testBoardE);
	int ** av = avaliaBoard(testBoardE, MAXMIZEPLAYER);
	for (size_t i = 0; i < TESTBSIZE; i++) {
		for (size_t j = 0; j < TESTBSIZE; j++) {
			if (av[i][j] != b2[i][j])
				return false;
		}
	}
	return true;
}

void testOrdenate()
{
	for (int i = 0; i < TESTBSIZE; ++i)
		testBoardE[i] = new unsigned char[TESTBSIZE];

	int sucsees = 0;
	int unsucsess = 0;

	cout << "testes da avaliacao do tabuleiro: " << endl;

	unsigned char b1[TESTBSIZE][TESTBSIZE] =
	{ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
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
	lastPlayed[0] = 0;
	lastPlayed[1] = 0;

	int bT1[TESTBSIZE][TESTBSIZE] =
	{ { -1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 10, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 4, -1, 4, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0 },
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

	if (testOrdenates(b1, bT1))
		sucsees++;
	else
		unsucsess++;


	unsigned char b2[TESTBSIZE][TESTBSIZE] =
	{ { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
	lastPlayed[0] = 1;
	lastPlayed[1] = 1;

	int bT2[TESTBSIZE][TESTBSIZE] =
	{ { -1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 10, 0, 6, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 6, 0, 0, 0, 4, -1, 6, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 6, -1, 4, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 4, -1, 6, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

	if (testOrdenates(b2, bT2))
		sucsees++;
	else
		unsucsess++;


	cout << "sucsess: " << sucsees << " unsucsess: " << unsucsess << endl;
}