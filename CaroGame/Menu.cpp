#include "Menu.h"
#include "View.h"
#include <conio.h>
#include <iostream>

using namespace std;

void createMenu() {
	int menuItemColors[3] = { 12, 7, 7 };
	string menuItemTexts[3] = { "New Game", "Load Game", "Exit" };
	int counter = 0;

	textStyle();

	do {
		char key = _getch();

		// UP
		if (key == 72) {
			counter--;
			if (counter < 0) {
				counter = 2;
			}
		} 
		// DOWN
		else if (key == 80) {
			counter++;
			if (counter > 2) {
				counter = 0;
			}
		}
		// ENTER
		else if (key == '\r') {
			// clear the previous text
			gotoXY(1, 1);
			clearRectangleArea({ 0, 0 }, 30, 1);
			
			cout << "You have selected " << menuItemTexts[counter] << endl;
		}

		memset(menuItemColors, 7, sizeof(menuItemColors));
		menuItemColors[counter] = 12;

		for (int i = 0; i < 3; i++) {
			gotoXY(1, 2*i + 5);
			textColor(menuItemColors[i]);
			cout << menuItemTexts[i] << endl;
		}
	} while (1);
}
