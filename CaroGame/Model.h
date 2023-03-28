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
	
	struct Setting {
		bool backgroundSound = false;
		bool soundEffect = false;
	};

	struct Player {
		char name[100] = "";
		int numberOfMoves;
		bool isFirstPlayer;
	};

	struct PlayerMove {
		COORD move;
		int player;
	};

	struct Board {
		int value[sz][sz];
		COORD spot[sz][sz];

		// initialize value for board 
		Board() {
			for (int i = 0; i < sz; i++) {
				for (int j = 0; j < sz; j++) {
					value[i][j] = 0;
					spot[i][j] = { short(View::LEFT + 2 + 4 * j), short(View::TOP + 1 + 2 * i) };
				}
			}
		}

		// override operator [][]
		int* operator [] (const int& i) {
			return value[i];
		}

		COORD getSpot(int i, int j) {
			return spot[i][j];
		}
	};
	
	struct GameInformation {
		char name[50] = "";
		Player player1;
		Player player2;
		bool isFirstPlayerTurn;
		int timeRemained; // in seconds
		Board board;
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
	void drawXO(Board board);
	void previousMove(
		GameInformation& game_info
	);
	PlayerMove getMoveHistory(GameInformation game_info, int num);
}

