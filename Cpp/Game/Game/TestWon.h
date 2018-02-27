#pragma once
#include "stdafx.h"

using namespace std;

void initilizeTestWon();
void initilizeVisited();
void initilizeUnvisited();
void reInUnvisited();
bool checkIfHas(unsigned char y, unsigned char x);
bool findReach(unsigned char** board, unsigned char y, unsigned char x);
bool hasWon(unsigned char** board, unsigned char piece);
int avalia(unsigned char** board, unsigned char piece);
