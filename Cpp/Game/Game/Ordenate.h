#pragma once
#include "stdafx.h"
#include "Game.h"
/*
struct PossiblePlay
{
	int value = -1;
	unsigned char l = 0;
	unsigned char c = 0;
	PossiblePlay * next_pos = nullptr;
};*/

int** avaliaBoard(unsigned char ** b, unsigned char player);
int** ordenate(unsigned char ** b, int depth, unsigned char player);
void initializeOrdenate();
int calcNumVizinhos(unsigned char ** board, int i, int j);