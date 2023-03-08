#include <iostream>
#include "Control.h"
#include "View.h"
#include "Model.h"
#include "Menu.h"
#include "InputHandle.h"
#include <functional>
using namespace std;

void dosomething1() {
	cout << "dosomething1" << endl;
}

void dosomething2() {
	cout << "dosomething2" << endl;
}

int main() {
	/*This file is not contain any sound effect because of the lack of memory*/

	/*use this function to start Caro Game
	however, this program only have play with human mode in new game 
	Choose New Game -> VS Human to start new game*/
	
	//Control::startGame();
	View::fixConsoleWindow();
	View::textStyle();
	View::confirmDialog(L"Are you sure you want to leave?", { 40, 10 }, &dosomething1, &dosomething2);

	//xWinScreen();

	return 0;
}
