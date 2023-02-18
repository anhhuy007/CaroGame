#include "Game.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

using namespace std;

const int _SIZE = 20;
const int LEFT = 1;
const int RIGHT = LEFT + 4 * _SIZE;
const int TOP = 1;
const int BOT = TOP + 2 * _SIZE;

int curX = LEFT + 2 * _SIZE - 2, curY = TOP + _SIZE + 1; 
int scoreA = 0, scoreB = 0;
bool endGame = false;

void startNewGame() {
	resetGame();
	fixConsoleWindow();
	drawBoard();

	int** board = new int* [_SIZE];
	for (int i = 0; i < _SIZE; i++) {
		board[i] = new int[_SIZE];
	}


	for (int i = 0; i < _SIZE; i++) {
		for (int j = 0; j < _SIZE; j++) {
			board[i][j] = 0;
		}
	}

	bool isFirstPlayerTurn = true;

	while (!endGame) {
		playGame(isFirstPlayerTurn, board);
		playGame(!isFirstPlayerTurn, board);
	}
}

void playGame(bool isFirstPlayerTurn, int**& board) {
	char key;

	while (!endGame) {
		gotoXY(curX, curY);
		if (_kbhit()) {
			key = _getch();

			int i = (curY - TOP - 1) / 2;
			int j = (curX - LEFT - 2) / 4;

			switch ((int)key) {
			case 27:
				endGame = true;
				system("cls");
				break;

			case 13:
				if (isValidPosition(curX, curY, i, j, board)) {
					if (isFirstPlayerTurn) {
						board[i][j] = 1;
						cout << "X";
						isFirstPlayerTurn = false;
					}
					else {
						board[i][j] = 2;
						cout << "O";
						isFirstPlayerTurn = true;
					}
					return;
				}
				break;
			case 72:
				if (curY - 2 < TOP + 1) {
					curY = BOT - 1;
				}
				else {
					curY -= 2;
				}
				break;

			case 75:
				if (curX - 4 < LEFT + 2) {
					curX = RIGHT - 2;
				}
				else {
					curX -= 4;
				}
				break;

			case 77:
				if (curX + 4 > RIGHT) {
					curX = LEFT + 2;
				}
				else {
					curX += 4;
				}
				break;

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

bool isValidPosition(int x, int y, int i, int j, int**& board) {
	if (x >= LEFT && x <= RIGHT && y >= TOP && y <= BOT) {
		if (board[i][j] == 0) {
			return true;
		}
	}

	return false;
}

void drawBoard() {
	// draw TOP
	gotoXY(LEFT + 1, TOP);
	for (int i = 0; i < (2 * _SIZE); i++) {
		if (i % 2) {
			printf("%c", 194);
		}
		else {
			printf("%c%c%c", 196, 196, 196);
		}
	}

	// draw BOTTOM
	gotoXY(LEFT + 1, BOT);
	for (int i = 0; i < (2 * _SIZE); i++) {
		if (i % 2) {
			printf("%c", 193);
		}
		else {
			printf("%c%c%c", 196, 196, 196);
		}
	}

	for (int i = 0; i < 2 * _SIZE; i++) {
		gotoXY(LEFT, TOP + i);
		if (i % 2) {
			printf("%c", 179);
		}
		else {
			printf("%c", 195);
		}

		gotoXY(RIGHT, TOP + i);
		if (i % 2) {
			printf("%c", 179);
		}
		else {
			printf("%c", 180);
		}
	}

	char s1[200], s2[200];
	for (int j = 0; j < 4 * _SIZE - 1; j++) {
		if (j % 4) {
			s1[j] = ' ';
		}
		else {
			s1[j] = 179;
		}
	}

	for (int j = 0; j < 4 * _SIZE - 1; j++) {
		if ((j + 1) % 4) {
			s2[j] = 196;
		}
		else {
			s2[j] = 197;
		}
	}

	s1[4 * _SIZE - 1] = '\0';
	s2[4 * _SIZE - 1] = '\0';

	int i = 1;
	while (i < 2 * _SIZE - 1) {
		gotoXY(LEFT, TOP + i++);
		printf("%s", s1);

		gotoXY(LEFT + 1, TOP + i++);
		printf("%s", s2);
	}

	gotoXY(LEFT, TOP + i); printf("%s", s1);
	gotoXY(LEFT, TOP); printf("%c", 218);
	gotoXY(RIGHT, TOP); printf("%c", 191);
	gotoXY(LEFT, BOT); printf("%c", 192);
	gotoXY(RIGHT, BOT); printf("%c", 217);
}

void gotoXY(int x, int y) {
	static HANDLE h = NULL;
	if (!h) h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { x, y };
	SetConsoleCursorPosition(h, coord);
}

// set full screen console and fix it _SIZE
void fixConsoleWindow() {
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void resetGame() {
	system("cls");
}