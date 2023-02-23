#include "Model.h"
#include "View.h"
#include "Control.h"
#include <iostream>
#include <conio.h>

using namespace std;

int curX = LEFT + 38;
int curY = TOP + 19;
int preX = curX;
int preY = curY;

bool endGame = false;

void previousMove(int &player, int**& board) {
	int i = (preY - TOP - 1) / 2;
	int j = (preX - LEFT - 2) / 4;
	
	board[i][j] = 0;
	player = player == 1 ? 2 : 1;
	curX = preX; curY = preY;

	gotoXY(preX, preY);
	cout << char(32);
}

void playGame(int &player, int**& board) {
	char key;

	while (!endGame) {
		gotoXY(curX, curY);
		if (_kbhit()) {
			key = _getch();

			int i = (curY - TOP - 1) / 2;
			int j = (curX - LEFT - 2) / 4;

			switch ((int)key) {
			// press F4
			case 62:
				previousMove(player, board);
				break;
				
			// press ESC
			case 27:
				endGame = true;
				exitGame();
				break;

			// press Enter
			case 13:
				if (board[i][j] == 0) {
					if (player == 1) {
						cout << "X";
						
						player = 2;
						board[i][j] = 1;
						preX = curX;
						preY = curY;
					}
					else {
						cout << "O";
						
						player = 1;
						board[i][j] = 2;
						preX = curX;
						preY = curY;
					}
					return;
				}
				break;

			// press UP
			case 72:
				if (curY - 2 < TOP + 1) {
					curY = BOT - 1;
				}
				else {
					curY -= 2;
				}
				break;

			// press LEFT
			case 75:
				if (curX - 4 < LEFT + 2) {
					curX = RIGHT - 2;
				}
				else {
					curX -= 4;
				}
				break;
			
			// press RIGHT 
			case 77:
				if (curX + 4 > RIGHT) {
					curX = LEFT + 2;
				}
				else {
					curX += 4;
				}
				break;
			
			// press DOWN
			case 80:
				if (curY + 2 > BOT) {
					curY = TOP + 1;
				}
				else {
					curY += 2;
				}
				break;
			}
		}
	}
}

// 0: game not ended
// 1 : player 1 win
// 2 : player 2 win
// 3 : draw

int checkResult(int player, int**& board) {
	gotoXY(1, 1);
	cout << player;
	
	int count = 0;
	for (int i = 0; i < _SIZE; i++) {
		for (int j = 0; j < _SIZE; j++) {
			if (board[i][j] != 0) count++;
			
			if (board[i][j] == player) {
				if (checkRow(i, j, player, board) ||
					checkCol(i, j, player, board) ||
					checkMainDiagonal(i, j, player, board) ||
					checkSubDiagonal(i, j, player, board)
				) {
					return player;
				}
			}
		}
	}

	return count == _SIZE * _SIZE ? 3 : 0;
}

bool checkRow(int i, int j, int player, int**& board) {
	if (j + 4 > _SIZE) {
		return false;
	}

	return (board[i][j] == player &&
			board[i][j + 1] == player &&
			board[i][j + 2] == player &&
			board[i][j + 3] == player &&
			board[i][j + 4] == player
	);
}

bool checkCol(int i, int j, int player, int**& board) {
	if (i + 4 > _SIZE) {
		return false;
	}

	return (board[i][j] == player &&
		board[i + 1][j] == player &&
		board[i + 2][j] == player &&
		board[i + 3][j] == player &&
		board[i + 4][j] == player
		);
}

bool checkMainDiagonal(int i, int j, int player, int**& board) {
	if (i + 4 > _SIZE || j + 4 > _SIZE) {
		return false;
	}

	return (board[i][j] == player &&
		board[i + 1][j + 1] == player &&
		board[i + 2][j + 2] == player &&
		board[i + 3][j + 3] == player &&
		board[i + 4][j + 4] == player
		);
}

bool checkSubDiagonal(int i, int j, int player, int**& board) {

	if (i - 4 < 0 || j + 4 > _SIZE) {
		return false;
	}

	return (board[i][j] == player &&
		board[i - 1][j + 1] == player &&
		board[i - 2][j + 2] == player &&
		board[i - 3][j + 3] == player &&
		board[i - 4][j + 4] == player
		);
}