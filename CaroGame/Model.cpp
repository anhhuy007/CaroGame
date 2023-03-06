#include "Model.h"
#include "InputHandle.h"
#include "View.h"
#include "Control.h"
using namespace std;

short curX = LEFT + 38;
short curY = TOP + 19;
short preX = curX;
short preY = curY;

bool endGame = false;

void Model::previousMove(int& player, int**& board) {
	int i = (preY - TOP - 1) / 2;
	int j = (preX - LEFT - 2) / 4;

	board[i][j] = 0;
	player = player == 1 ? 2 : 1;
	curX = preX; curY = preY;

	View::gotoXY(preX, preY);
	cout << char(32);
}

void Model::playGame(int& player, int**& board) {
	wstring key; endGame = false;

	while (!endGame) {
		View::gotoXY(curX, curY);
		key = InputHandle::Get();

		// move up
		if (key == L"UP") {
			if (curY > TOP + 1) {
				preX = curX; preY = curY;
				curY -= 2;
			}
			else {
				curY = BOT - 1;
			}
		}

		// move down
		else if (key == L"DOWN") {
			if (curY < BOT - 1) {
				preX = curX; preY = curY;
				curY += 2; 
			} 
			else {
				curY = TOP + 1;
			}
		}

		// move left
		else if (key == L"LEFT") {
			if (curX > LEFT + 2) {
				preX = curX; preY = curY;
				curX -= 4;
			}
			else {
				curX = RIGHT - 2;
			}
		}

		// move right
		else if (key == L"RIGHT") {
			if (curX < RIGHT - 2) {
				preX = curX; preY = curY;
				curX += 4;
			}
			else {
				curX = LEFT + 2;
			}
		}

		// enter -> mark a player move
		else if (key == L"ENTER") {
			int i = (curY - TOP - 1) / 2;
			int j = (curX - LEFT - 2) / 4;

			if (board[i][j] == 0) {
				board[i][j] = player;
				wstring ch = player == 1 ? L"X" : L"O";
				View::printCharactors(ch, { curX, curY }, View::Color::BLACK, View::Color::WHITE);
				player = player == 1 ? 2 : 1;
			}
			
			break;
		}
		
		else if (key == L"ESC") {
			endGame = true;
			Control::quitGame();
		}
		else if (key == L"F4") {
			previousMove(player, board);
		}
	}
}

// 0: game not ended
// 1 : player 1 win
// 2 : player 2 win
// 3 : draw
int Model::checkResult(int player, int**& board) {
	View::gotoXY(1, 1);
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

bool Model::checkRow(int i, int j, int player, int**& board) {
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

bool Model::checkCol(int i, int j, int player, int**& board) {
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

bool Model::checkMainDiagonal(int i, int j, int player, int**& board) {
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

bool Model::checkSubDiagonal(int i, int j, int player, int**& board) {

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