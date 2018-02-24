#pragma once
#include "stdafx.h"

using namespace std;

bool checkIfHas(std::vector<int*>* v, unsigned char y, unsigned char x);
vector<int*>* findReach(unsigned char** board, unsigned char y, unsigned char x);
bool hasTopToBotom(vector<int*>* visited);
bool hasWon(unsigned char** board, unsigned char piece);