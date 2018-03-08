#include "stdafx.h"
#include "NonRepeat.h"

using namespace std;

struct VisitedBuffer
{
	unsigned char num1[34];
	int value = MIN;
};

unsigned char** nonRepeatX = new unsigned char*[BSIZE];

void initNonRepeat()
{
	cout << "sizeo of VisitedBuffer: " << sizeof(VisitedBuffer) << endl;
	for (int i = 0; i < BSIZE; ++i)
		nonRepeatX[i] = new unsigned char[BSIZE];
}

void initilizeNonRepeat()
{
	for (size_t i = 0; i < BSIZE; i++)
	{
		for (size_t j = 0; j < BSIZE; j++)
		{
			nonRepeatX[i][j] = 1;//MAXDEPTH;
		}
	}
}

bool isRepeated(unsigned char i, unsigned char j)
{
	return nonRepeatX[i][j] == 0;
}

void doneLevel(unsigned char i,unsigned char j)
{
	nonRepeatX[i][j] = 0;
/*	for (int h = 0; h < BSIZE; h++)
	{
		for (int g = 0; g < BSIZE; g++)
		{
			cout << (int)nonRepeatX[h][g] << " ";
		}
		cout << endl;
	}*/
}