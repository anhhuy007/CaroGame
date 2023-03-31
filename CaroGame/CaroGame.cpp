#include "Control.h"
#include "View.h"
#include "Model.h"
#include "Menu.h"
#include "InputHandle.h"
#include "FileIO.h"

using namespace std;

int main() {
	/*This file is not contain any sound effect because of the lack of memory*/

	/*use this function to start Caro Game
	however, this program only have play with human mode in new game
	Choose New Game -> VS Human to start new game*/





	//View::LoadGameBorder(50, 50 + 50, 2, 2 + 20);
	View::fixConsoleWindow();
	View::textStyle(22);
	system("cls");
	system("color f0");
	Control::startGame();
	//Control::newGame(1, 1, GameInformation());

	return 0;
}