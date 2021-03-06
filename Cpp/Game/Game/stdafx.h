// stdafx.h : arquivo de inclusão para inclusões do sistema padrões,
// ou inclusões específicas de projeto que são utilizadas frequentemente, mas
// são modificadas raramente
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <limits.h>


#define BSIZE 14
#define TESTBSIZE 14
#define MAXMIZEPLAYER 1
#define MINIMIZEPLAYER 2
#define EMPTY 0
#define BLACKS 1
#define WHITES 2
#define VISITEDBUFFERSIZE 1000000
#define MAXMAXDEPTH 10

//values to alfa and beta
const int MAX = 10000000;
const int MIN = -10000000;

const int FACTOROBJECTIVE = 6;
const int FACTORNONOBJECTIVE = 3;
const double EXPFACTOR = 2;


// TODO: adicionar referências de cabeçalhos adicionais que seu programa necessita
