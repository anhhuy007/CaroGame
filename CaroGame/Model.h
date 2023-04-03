#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include "View.h"

using namespace std;

const int sz = View::BOARD_SIZE;

namespace Model {
	typedef pair<int, vector<COORD>> GameResult;

	const bool PLAY_WITH_COMPUTER = 0;
	const bool PLAY_WITH_HUMAN = 1;
	const bool EASY = 0;
	const bool HARD = 1;
	
	struct Setting {
		bool backgroundSound = false;
		bool soundEffect = false;
	};

	struct Player {
		char name[20] = "";
		int numberOfMoves = 0;
		bool isFirstPlayer;
	};

	struct PlayerMove {
		COORD move;
		int player;
	};

	struct GameMode {
		bool isPlayWithHuman;
		bool level;
	};

	struct Board {
		int value[sz][sz];
		COORD gui[sz][sz];

		// constructor for board
		Board() {
			for (int i = 0; i < sz; i++) {
				for (int j = 0; j < sz; j++) {
					value[i][j] = 0;
					gui[i][j] = { short(View::LEFT + 2 + 4 * j), short(View::TOP + 1 + 2 * i) };
				}
			}
		}

		Board(const Board& other) {
			for (int i = 0; i < sz; i++) {
				for (int j = 0; j < sz; j++) {
					value[i][j] = other.value[i][j];
					gui[i][j] = other.gui[i][j];
				}
			}
		}

		// override operator [][]
		int* operator [] (const int& i) {
			return value[i];
		}

		COORD getSpot(int i, int j) {
			return gui[i][j];
		}

		void removeStoneNoGUI(int x, int y) {
			value[x][y] = 0;
		}

		void addStoneNoGUI(int x, int y, bool black) {
			value[x][y] = black ? 2 : 1;
		}

		bool addStone(int x, int y, bool black) {
			if (value[x][y] != 0) return false;

			value[x][y] = black ? 2 : 1;
			View::drawMove(gui[x][y].X, gui[x][y].Y, value[x][y]);
			return true;
		}

		// return data array 
		int** getDataArray() {
			return (int**)value;
		}

		std::vector<COORD> generateMoves() {
			std::vector<COORD> moveList;

			for (int i = 0; i < sz; i++) {
				for (int j = 0; j < sz; j++) {
					if (value[i][j] != 0) continue;

					if (i > 0) {
						if (j > 0) {
							if (value[i - 1][j - 1] > 0 ||
								value[i][j - 1] > 0) {
								COORD move = { i,j };
								moveList.push_back(move);
								continue;
							}
						}
						if (j < sz - 1) {
							if (value[i - 1][j + 1] > 0 ||
								value[i][j + 1] > 0) {
								COORD move = { i,j };
								moveList.push_back(move);
								continue;
							}
						}
						if (value[i - 1][j] > 0) {
							COORD move = { i,j };
							moveList.push_back(move);
							continue;
						}
					}
					if (i < sz - 1) {
						if (j > 0) {
							if (value[i + 1][j - 1] > 0 ||
								value[i][j - 1] > 0) {
								COORD move = { i,j };
								moveList.push_back(move);
								continue;
							}
						}
						if (j < sz - 1) {
							if (value[i + 1][j + 1] > 0 ||
								value[i][j + 1] > 0) {
								COORD move = { i,j };
								moveList.push_back(move);
								continue;
							}
						}
						if (value[i + 1][j] > 0) {
							COORD move = { i,j };
							moveList.push_back(move);
							continue;
						}
					}
				}
			}

			return moveList;
		}
	};
	
	struct GameInformation {
		char name[20] = "";
		Player player1;
		Player player2;
		GameMode gameMode;
		bool isFirstPlayerTurn;
		int timer; // in seconds
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
	void computerTurn(Model::Player player, Model::GameInformation& game_info);
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
	std::vector<Model::PlayerMove> getMoveHistory(GameInformation game_info, int num);
	void updateInform(GameInformation& game_info, COORD spot, int width, int height, View::Color color);
}

