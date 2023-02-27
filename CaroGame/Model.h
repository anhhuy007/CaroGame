#pragma once
#include "View.h"
#include "Control.h"
#include <iostream>
#include <conio.h>

void playGame(int& player, int**& board);
int checkResult(int player, int**& board);
bool checkRow(int i, int j, int player, int**& board);
bool checkCol(int i, int j, int player, int**& board);
bool checkMainDiagonal(int i, int j, int player, int**& board);
bool checkSubDiagonal(int i, int j, int player, int**& board);
void previousMove(int& player, int**& board);
