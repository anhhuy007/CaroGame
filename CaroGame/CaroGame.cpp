#include <iostream>
#include "Control.h"
#include "View.h"
#include "Model.h"
#include "Menu.h"
#include "InputHandle.h"
#include <functional>
#include "FileIO.h"
#include <string>
using namespace std;

int main() {
	/*This file is not contain any sound effect because of the lack of memory*/

	/*use this function to start Caro Game
	however, this program only have play with human mode in new game 
	Choose New Game -> VS Human to start new game*/
	View::textStyle(22);
	system("color f0");
	View::fixConsoleWindow();
	
	//Control::startGame();
	//Control::newGame(1, 1, Control::initNewGame());
	system("cls");
	View::LoadGameBorder(50, 50 + 50, 2, 2 + 20);
	return 0;
}
