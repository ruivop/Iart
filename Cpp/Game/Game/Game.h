#pragma once
#include "TestWon.h"
#include "TestWonTest.h"
#include "TestOredenate.h"
#include "Ordenate.h"
#include "Server.h"

struct Move
{
	int i, j;
};

struct Play
{
	Move* move_first = new Move;
	Move* move_second = new Move;
	int value = 0;
	Play* next_play = nullptr;
	Play* previous_play = nullptr;
};

bool isDiagnonalyAdj(unsigned char** board, int i, int j, unsigned char colour);
void mostrar(unsigned char** board);
bool pcTurn(unsigned char** board);
bool playerTurn(unsigned char** board);
Play* choseNextPlay(unsigned char** board);