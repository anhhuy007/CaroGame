#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>

using namespace std;

namespace Model {
	typedef pair<int, vector<COORD>> GameResult;
	
	void playGame(int& player, int**& board);
	pair<int, vector<COORD>> checkResult(int player, int**& board);
	bool checkRow(int i, int j, int player, int**& board);
	bool checkCol(int i, int j, int player, int**& board);
	bool checkMainDiagonal(int i, int j, int player, int**& board);
	bool checkSubDiagonal(int i, int j, int player, int**& board);
	void previousMove(int& player, int**& board);
}

