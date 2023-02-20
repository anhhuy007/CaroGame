#include "Model.h"
#include "View.h"
#include <iostream>
#include <conio.h>

using namespace std;

int curX = LEFT + 38;
int curY = TOP + 19;
bool endGame = false;

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
				if (board[i][j] == 0) {
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
