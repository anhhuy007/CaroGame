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

	Control::startGame();
	//system("color f0");
	//View::textStyle(22);
	//View::fixConsoleWindow();



	return 0;
}