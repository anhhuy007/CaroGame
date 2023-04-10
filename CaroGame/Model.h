#pragma once
#pragma warning(disable:4996)
#include "View.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>	
#include <chrono>
#include <ctime> 
#include <string>
#include <time.h>
#include <locale.h>
#include <stdio.h>

const int sz = View::BOARD_SIZE;

namespace Model {
	typedef std::pair<int, std::vector<COORD>> GameResult;

	const bool PLAY_WITH_COMPUTER = 0;
	const bool PLAY_WITH_HUMAN = 1;
	const bool EASY = 0;
	const bool HARD = 1;
	const bool CREATED = 0;
	const bool MODIFIED = 1;
	
	struct Setting {
		bool backgroundSound = false;
		bool soundEffect = false;
	};

	struct Player {
		char name[20] = "";
		View::Avatar avatar;
		int numberOfMoves = 0;
		bool isFirstPlayer;
		int score = 0;

		std::wstring getWStringName() {
			std::wstring wstr;
			wstr.assign(name, name + strlen(name));
			return wstr;
		}
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

		// default constructor for board
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
		inline int* operator [] (const int& i) {
			return value[i];
		}

		// return cell position
		inline COORD getSpot(int i, int j) {
			return gui[i][j];
		}

		inline void removeMoveNoGUI(int x, int y) {
			value[x][y] = 0;
		}

		inline void addMoveNoGUI(int x, int y, bool computer) {
			value[x][y] = computer ? 2 : 1;
		}

		inline bool addMove(int x, int y, bool black) {
			if (value[x][y] != 0) return false;

			value[x][y] = black ? 2 : 1;
			View::drawMove(gui[x][y].X, gui[x][y].Y, value[x][y]);
			return true;
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

	struct DisplayedHistory {
		PlayerMove playerMove = { { -1, -1 }, 0 };
		bool isPrevious;
	};
	
	struct GameInformation {
		char name[20] = "";
		Player player1;
		Player player2;
		GameMode gameMode;
		bool isFirstPlayerTurn;
		Board board;
		PlayerMove playerMoveHistory[250];
		int moveHistorySize = 0;
		DisplayedHistory displayedHistory[4];
		short curX; 
		short curY;
		int totalStep = 0; // total step of game
		bool endGame;

		void updateDisplayedHistory(DisplayedHistory history) {
			for (int i = 0; i < 3; i++) {
				displayedHistory[i] = displayedHistory[i + 1];
			}
			displayedHistory[3] = history;
		}
	};

	// store general game information, including name, date created or modified, and game mode
	struct GeneralGameInformation {
		char name[20];
		std::pair<time_t, bool> date = { time(0), false };
		GameMode gameMode;

		// default constructer
		GeneralGameInformation(char name[], std::pair<time_t, bool> date, GameMode gameMode) {
			strcpy_s(this->name, name);
			this->date = date;
			this->gameMode = gameMode;
		}

		void updateNewDate() {
			// get current date
			auto now = std::chrono::system_clock::now();
			time_t now_c = std::chrono::system_clock::to_time_t(now);

			// if player created new game, then save current time
			if (date.first == time(0)) {
				date.second = CREATED;
			}
			// if player modified game
			else {
				date.second = MODIFIED;
			}
			date.first = now_c;
		}

		std::string getFormatedDate() {
			char buffer[80];
			tm* timeinfo = localtime(&date.first);
			strftime(buffer, 80, "%d-%m-%Y - %I:%M:%S", timeinfo);
			std::string str(buffer);
			return str;
		}

		// information pattern: name@date@gameMode
		std::string getFormatedInformation() {
			std::string formatStr = name;
			formatStr += "@";
			formatStr += getFormatedDate();
			formatStr += "@";
			formatStr += getGameMode();

			return formatStr;
		}

		// return game mode 
		std::string getGameMode() {
			if (gameMode.isPlayWithHuman == true) return "Player vs Player";
			else {
				if (gameMode.level == EASY) return "Player vs Computer (Easy)"; 
				else return "Player vs Computer (Hard)";
			}
		}
	};
	
	void playerTurn(
		Model::Player player, 
		Model::GameInformation& game_info
	);
	
	void computerTurn(
		Model::Player player, 
		Model::GameInformation& game_info
	);
	
	// display cursor's movement on board
	void makePlayerMove(
		std::wstring key, 
		Model::GameInformation& game_info
	);
	
	// mark player move to board and
	void markPlayerMove(
		COORD spot, 
		int player, 
		Model::GameInformation& game_info
	);

	void previousMove(GameInformation& game_info);

	// display current game information on screen
	void updateInform(
		GameInformation& game_info, 
		COORD spot, 
		int width, 
		int height, 
		View::Color color
	);

	// check if there is a winning move then return winner and list of winning moves
	std::pair<int, std::vector<COORD>> checkResult(
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
}

