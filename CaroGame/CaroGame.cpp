#include "Control.h"
#include "View.h"
#include "AI.h"

using namespace std;

int main() {
	/*This file is not contain any sound effect because of the lack of memory*/

	/*use this function to start Caro Game
	however, this program only have play with human mode in new game
	Choose New Game -> VS Human to start new game*/

	AI::Board board = AI::Board();

	board[3][3] = 2;
	board[3][4] = 2;
	board[3][5] = 2;
	board[3][6] = 2;

	for (int i = 0; i < AI::BOARD_SZ; i++) {
		for (int j = 0; j < AI::BOARD_SZ; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	
	COORD move = AI::calculateNextMove(2, board);
	cout << move.X << " " << move.Y << endl;

	system("pause");
	return 0;
}