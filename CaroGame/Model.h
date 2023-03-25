#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <stack>
#include "View.h"

using namespace std;

const int sz = View::BOARD_SIZE;

namespace Model {
	typedef pair<int, vector<COORD>> GameResult;

	struct Player {
		char name[100] = "";
		int numberOfMoves;
		bool isFirstPlayer;
	};

	struct PlayerMove {
		COORD move;
		int player;
	};

	struct GameInformation {
		char name[50] = "";
		Player player1;
		Player player2;
		bool isFirstPlayerTurn;
		int timeRemained; // in seconds
		int board[sz][sz];
		PlayerMove playerMoveHistory[250];
		int moveHistorySize = 0;
		int curX; 
		int curY;
		bool endGame;
	};
	
	void playerTurn(
		Model::Player player, 
		Model::GameInformation& game_info
	);
	void makePlayerMove(std::wstring key);
	void markPlayerMove(
		COORD spot, 
		int player, 
		Model::GameInformation& game_info
	);
	pair<int, vector<COORD>> checkResult(
		int player, 
		int board[sz][sz]
	);
	bool checkRow(
		int i, 
		int j, 
		int player, 
		int board[sz][sz]
	);
	bool checkCol(
		int i, 
		int j, 
		int player, 
		int board[sz][sz]
	);
	bool checkMainDiagonal(
		int i, 
		int j, 
		int player, 
		int board[sz][sz]
	);
	bool checkSubDiagonal(
		int i, 
		int j, 
		int player, 
		int board[sz][sz]
	);
	void previousMove(
		Model::GameInformation& game_info
	);
}

