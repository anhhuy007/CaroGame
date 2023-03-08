#include "Model.h"
#include "InputHandle.h"
#include "View.h"
#include "Control.h"
using namespace std;

short curX = View::LEFT + 38;
short curY = View::TOP + 19;
short preX = curX;
short preY = curY;

bool endGame = false;

void Model::previousMove(int& player, int**& board) {
	int i = (preY - View::TOP - 1) / 2;
	int j = (preX - View::LEFT - 2) / 4;

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
			if (curY > View::TOP + 1) {
				preX = curX; preY = curY;
				curY -= 2;
			}
			else {
				curY = View::BOT - 1;
			}
		}

		// move down
		else if (key == L"DOWN") {
			if (curY < View::BOT - 1) {
				preX = curX; preY = curY;
				curY += 2; 
			} 
			else {
				curY = View::TOP + 1;
			}
		}

		// move left
		else if (key == L"LEFT") {
			if (curX > View::LEFT + 2) {
				preX = curX; preY = curY;
				curX -= 4;
			}
			else {
				curX = View::RIGHT - 2;
			}
		}

		// move right
		else if (key == L"RIGHT") {
			if (curX < View::RIGHT - 2) {
				preX = curX; preY = curY;
				curX += 4;
			}
			else {
				curX = View::LEFT + 2;
			}
		}

		// enter -> mark a player move
		else if (key == L"ENTER") {
			int i = (curY - View::TOP - 1) / 2;
			int j = (curX - View::LEFT - 2) / 4;

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
// if game ended, return a pair of result and a vector of coordinates of winning line
Model::GameResult Model::checkResult(int player, int**& board) {
	vector<COORD> winPos(0, { 0, 0 });
	
	int count = 0;
	for (int i = 0; i < View::_SIZE; i++) {
		for (int j = 0; j < View::_SIZE; j++) {
			if (board[i][j] != 0) count++;

			if (board[i][j] == player) {
				if (Model::checkRow(i, j, player, board) == true) {
					for (int k = 0; k < 5; k++) {
						short x = View::LEFT + 2 + 4 * (j - k);
						short y = View::TOP + 1 + 2 * i;
						winPos.push_back({ x, y });
					}
					return { player, winPos };
				}
				else if (Model::checkCol(i, j, player, board) == true) {
					for (int k = 0; k < 5; k++) {
						short x = View::LEFT + 2 + 4 * j;
						short y = View::TOP + 1 + 2 * (i - k);
						winPos.push_back({ x, y });
					}
					return { player, winPos };
				}
				else if (Model::checkMainDiagonal(i, j, player, board) == true) {
					for (int k = 0; k < 5; k++) {
						short x = View::LEFT + 2 + 4 * (j - k);
						short y = View::TOP + 1 + 2 * (i - k);
						winPos.push_back({ x, y });
					}
					return { player, winPos };
				}
				else if (Model::checkSubDiagonal(i, j, player, board) == true) {
					for (int k = 0; k < 5; k++) {
						short x = View::LEFT + 2 + 4 * (j - k);
						short y = View::TOP + 1 + 2 * (i + k);
						winPos.push_back({ x, y });
					}
					return { player, winPos };
				}
			}
		}
	}

	int result = count == View::_SIZE * View::_SIZE ? 3 : 0;
	return { result, winPos };	
}

bool Model::checkRow(int i, int j, int player, int**& board) {
	if (j + 4 > View::_SIZE) {
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
	if (i + 4 > View::_SIZE) {
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
	if (i + 4 > View::_SIZE || j + 4 > View::_SIZE) {
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

	if (i - 4 < 0 || j + 4 > View::_SIZE) {
		return false;
	}

	return (board[i][j] == player &&
		board[i - 1][j + 1] == player &&
		board[i - 2][j + 2] == player &&
		board[i - 3][j + 3] == player &&
		board[i - 4][j + 4] == player
		);
}