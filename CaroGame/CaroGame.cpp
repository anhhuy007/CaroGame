#include "Control.h"
#include "View.h"
#include "AI.h"

using namespace std;

int main() {
	/*This file is not contain any sound effect because of the lack of memory*/

	/*use this function to start Caro Game
	however, this program only have play with human mode in new game
	Choose New Game -> VS Human to start new game*/

	View::fixConsoleWindow();
	View::textStyle(22);
	Control::playWithComputer(Control::initNewGame({ false, true }));

	/*Model::Board board = Model::Board();

	board[0][4] = 2;
	board[0][5] = 2;
	board[1][6] = 2;
	
	board[1][2] = 1;
	board[1][3] = 1;
	board[1][4] = 1;

	for (int i = 0; i < AI::BOARD_SZ; i++) {
		for (int j = 0; j < AI::BOARD_SZ; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	
	COORD move = AI::calculateNextMove(2, board);
	cout << move.X << " " << move.Y << endl;*/

	//AI::evaluateHorizontal(board, true, true);

	system("pause");
	return 0;
}