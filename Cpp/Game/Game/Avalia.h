#pragma once
#include "stdafx.h"

using namespace std;

void AinitilizeAvalia();
void AinitilizeVisited();
void AinitilizeUnvisited();
void AreInUnvisited();
bool AcheckIfHas(unsigned char y, unsigned char x);
int eveluateReach(unsigned char** board, unsigned char y, unsigned char x);
int avalia(unsigned char** board, unsigned char piece);