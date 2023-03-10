#include <iostream>
#include "Control.h"
#include "View.h"
#include "Model.h"
#include "Menu.h"
#include "InputHandle.h"
#include <functional>
using namespace std;

int main() {
	/*This file is not contain any sound effect because of the lack of memory*/

	/*use this function to start Caro Game
	however, this program only have play with human mode in new game 
	Choose New Game -> VS Human to start new game*/
	
	Control::startGame();

	/*wstring key = InputHandle::Get();

	while (key != L"ESC") {
		key = InputHandle::Get();
		wcout << key << endl;
	}*/

	/*View::fixConsoleWindow();
	View::textStyle();*/
	
	return 0;
}
