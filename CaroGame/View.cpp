#include "View.h"
#include "Menu.h"
#include "Control.h"
#include "Sound.h"
#include "InputHandle.h"

using namespace std;

// draw board with Size x Size cells
void View::drawBoard() {
	// draw TOP
	gotoXY(LEFT + 1, TOP);
	for (int i = 0; i < (2 * BOARD_SIZE); i++) {
		if (i % 2) {
			cout << char(194);
		}
		else {
			cout << char(196) << char(196) << char(196);
		}		
	}

	// draw BOTTOM
	gotoXY(LEFT + 1, BOT);
	for (int i = 0; i < (2 * BOARD_SIZE); i++) {
		if (i % 2) {
			cout << char(193);
		}
		else {
			cout << char(196) << char(196) << char(196);
		}
	}

	for (int i = 0; i < 2 * BOARD_SIZE; i++) {
		gotoXY(LEFT, TOP + i);
		if (i % 2) {
			cout << char(179);
		}
		else {
			cout << char(195);
		}

		gotoXY(RIGHT, TOP + i);
		if (i % 2) {
			cout << char(179);
		}
		else {
			cout << char(180);
		}
	}

	char s1[200], s2[200];
	for (int j = 0; j < 4 * BOARD_SIZE - 1; j++) {
		if (j % 4) {
			s1[j] = ' ';
		}
		else {
			s1[j] = 179;
		}
	}

	for (int j = 0; j < 4 * BOARD_SIZE - 1; j++) {
		if ((j + 1) % 4) {
			s2[j] = 196;
		}
		else {
			s2[j] = 197;
		}
	}

	s1[4 * BOARD_SIZE - 1] = '\0';
	s2[4 * BOARD_SIZE - 1] = '\0';

	int i = 1;
	while (i < 2 * BOARD_SIZE - 1) {
		gotoXY(LEFT, TOP + i++);
		cout << s1;

		gotoXY(LEFT + 1, TOP + i++);
		cout << s2;
	}

	gotoXY(LEFT, TOP + i); cout << s1;
	gotoXY(LEFT, TOP); cout << char(218);
	gotoXY(RIGHT, TOP); cout << char(191);
	gotoXY(LEFT, BOT); cout << char(192);
	gotoXY(RIGHT, BOT); cout << char(217);
}

void View::drawBoard2(int space_row, int space_col) {
	int x, y;
	x = 4;
	y = 1;

	//draw coordinate border

	View::printCharactors(L"a", { (short)(x + 2),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"b", { (short)(x + 6),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"c", { (short)(x + 10),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"d", { (short)(x + 14),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"e", { (short)(x + 18),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"f", { (short)(x + 22),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"g", { (short)(x + 26),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"h", { (short)(x + 30),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"i", { (short)(x + 34),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"j", { (short)(x + 38),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"k", { (short)(x + 42),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"l", { (short)(x + 46),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"m", { (short)(x + 50),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"n", { (short)(x + 54),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"o", { (short)(x + 58),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	//View::printCharactors(L"p", { (short)(x + 62),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);


	//col = 4*space_col -1
	//row = 2*space_row -1
	//inside
	int k = 1;
	while (1) {
		for (int i = 1; i <= 4 * space_col - 1; i++) {
			if (i % 4 == 0) View::printCharactors(L"║", { (short)(x + i),(short)(y + k) }, Color::BLACK, Color::WHITE);
		}
		k++;
		if (k > 2 * space_row - 1) break;

		for (int i = 1; i <= 4 * space_col - 1; i++) {
			if (i % 4 == 0) View::printCharactors(L"╬", { (short)(x  + i),(short)(y + k) }, Color::BLACK, Color::WHITE);
			else View::printCharactors(L"═", { (short)(x  + i),(short)(y + k) }, Color::BLACK, Color::WHITE);
		}
		k++;
	}

	//border
	for (int i = 1; i <= 4 * space_col - 1; i++) {			//top
		if (i % 4 == 0) View::printCharactors(L"╦", { (short)(x + i),(short)(y + 0) }, Color::BLACK, Color::WHITE);
		else View::printCharactors(L"═", { (short)(x + i),(short)(y + 0) }, Color::BLACK, Color::WHITE);
	}
	for (int i = 1; i <= 4 * space_col - 1; i++) {			//bot
		if (i % 4 == 0) View::printCharactors(L"╩", { (short)(x + i),(short)(y + 2*space_row -1 +1) }, Color::BLACK, Color::WHITE);
		else View::printCharactors(L"═", { (short)(x + i),(short)(y + 2 * space_row - 1 + 1) }, Color::BLACK, Color::WHITE);
	}
	for (int i = 1; i <= 2 * space_row - 1; i++) {			//left
		if (i % 2 == 0) View::printCharactors(L"╠", { (short)(x + 0),(short)(y + i) }, Color::BLACK, Color::WHITE);
		else View::printCharactors(L"║", { (short)(x + 0),(short)(y + i) }, Color::BLACK, Color::WHITE);
	}
	for (int i = 1; i <= 2 * space_row - 1; i++) {			//right
		if (i % 2 == 0) View::printCharactors(L"╣", { (short)(x + 4*space_col -1 +1),(short)(y + i) }, Color::BLACK, Color::WHITE);
		else View::printCharactors(L"║", { (short)(x + 4 * space_col - 1 + 1),(short)(y + i) }, Color::BLACK, Color::WHITE);
	}

	View::printCharactors(L"╔", { (short)(x + 0),(short)(y + 0) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"╗", { (short)(x + 4 * space_col - 1 + 1),(short)(y + 0) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"╚", { (short)(x + 0),(short)(y + 2 * space_row - 1 + 1) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"╝", { (short)(x + 4 * space_col - 1 + 1),(short)(y + 2 * space_row - 1 + 1) }, Color::BLACK, Color::WHITE);
}
void View::drawCaroGameText() {
	int x, y;

	//-----------------------------------------chu A ------------------
	x = 40;
	y = 0;


	for (int i = 2; i <= 5; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 2) }, Color::CYAN, Color::WHITE);
	}
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);



	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 6),(short)(y + 2 + 5) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 6),(short)(y + 2 + 2) }, Color::CYAN, Color::WHITE);

	View::printCharactors(L"\x2580", { (short)(x + 10 + 3),(short)(y + 2 + 4) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 4),(short)(y + 2 + 4) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 6),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 6),(short)(y + 2 + 2) }, Color::CYAN, Color::BLACK);

	View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);

	for (int i = 1; i <= 6; i++) {
		View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	}
	View::printCharactors(L"\x2580", { (short)(x + 10 + 0),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 7),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);

	//---------------------------------------------chu C ----------------------------------------
	x = 30;
	y = 0;

	//View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color::YELLOW, Color::WHITE);

	for (int i = 2; i <= 5; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 2) }, Color::CYAN, Color::WHITE);
	}

	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);


	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);

	for (int i = 1; i <= 6; i++) {
		View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	}
	View::printCharactors(L"\x2580", { (short)(x + 10 + 7),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 0),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 6),(short)(y + 2 + 2) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 3),(short)(y + 2 + 4) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 4) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 3) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 6),(short)(y + 2 + 3) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 3),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 4),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);


	//----------------------------------------------chu R-------------------------------------------
	x = 49;
	y = 0;

	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 2) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 2) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);


	View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);

	for (int i = 2; i <= 7; i++) {
		View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	}

	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 8),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);


	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 3) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 5),(short)(y + 2 + 3) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 7),(short)(y + 2 + 2) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 7),(short)(y + 2 + 4) }, Color::CYAN, Color::BLACK);

	View::printCharactors(L"\x2580", { (short)(x + 10 + 4),(short)(y + 2 + 2) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 2) }, Color::CYAN, Color::BLACK); 
	View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 3),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 6),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 7),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);

	//----------------------------------------------chu O-------------------------------------------
	x = 60;
	y = 0;

	for (int i = 2; i <= 5; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 2) }, Color::CYAN, Color::BLACK);
	}
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 3) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 3) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 4) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 4) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 4) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 4) }, Color::CYAN, Color::BLACK);

	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);


	for (int i = 1; i <= 6; i++) {
		View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	}

	View::printCharactors(L"\x2580", { (short)(x + 10 + 0),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 7),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);


	View::printCharactors(L"\x2584", { (short)(x + 10 + 3),(short)(y + 2 + 4) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 4) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 6),(short)(y + 2 + 2) }, Color::CYAN, Color::BLACK);

	View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 3),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 4),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);

	//-----------------------------------------chu G ------------------
	x = 34;
	y = 5;

	for (int i = 2; i <= 6; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 2) }, Color::CYAN, Color::WHITE);
	}
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);


	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);


	for (int i = 1; i <= 7; i++) {
		View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	}

	View::printCharactors(L"\x2580", { (short)(x + 10 + 0),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 8),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 3),(short)(y + 2 + 4) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 4) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 5),(short)(y + 2 + 4) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 7),(short)(y + 2 + 2) }, Color::CYAN, Color::BLACK);

	for (int i = 2; i <= 6; i++) {
		View::printCharactors(L"\x2580", { (short)(x + 10 + i),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	}
	for (int i = 4; i <= 7; i++) {
		View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 3) }, Color::CYAN, Color::BLACK);
	}


	//-----------------------------------------chu A2 ------------------
	x = 45;
	y = 5;


	for (int i = 2; i <= 5; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 2) }, Color::CYAN, Color::WHITE);
	}
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);



	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 6),(short)(y + 2 + 5) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 6),(short)(y + 2 + 2) }, Color::CYAN, Color::WHITE);

	View::printCharactors(L"\x2580", { (short)(x + 10 + 3),(short)(y + 2 + 4) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 4),(short)(y + 2 + 4) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 6),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 6),(short)(y + 2 + 2) }, Color::CYAN, Color::BLACK);

	View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);

	for (int i = 1; i <= 6; i++) {
		View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	}
	View::printCharactors(L"\x2580", { (short)(x + 10 + 0),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 7),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);


	//-----------------------------------------chu M ------------------
	x = 54;
	y = 5;

	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 2) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 2) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 2) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);


	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 9),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 9),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 9),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);

	for (int i = 2; i <= 8; i++) {
		View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	}

	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 9),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);


	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 2) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 6),(short)(y + 2 + 2) }, Color::CYAN, Color::BLACK);

	View::printCharactors(L"\x2580", { (short)(x + 10 + 4),(short)(y + 2 + 3) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 6),(short)(y + 2 + 3) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 3),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 7),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 8),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);

	//-----------------------------------------chu E ------------------
	x = 65;
	y = 5;

	for (int i = 2; i <= 6; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 2) }, Color::CYAN, Color::WHITE);
	}
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 4) }, Color::CYAN, Color::WHITE);



	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 7),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);

	for (int i = 2; i <= 6; i++) {
		View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	}

	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 3) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 5),(short)(y + 2 + 3) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 4) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 5),(short)(y + 2 + 4) }, Color::CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 6),(short)(y + 2 + 4) }, Color::CYAN, Color::BLACK);
	for (int i = 2; i <= 6; i++) {
		View::printCharactors(L"\x2580", { (short)(x + 10 + i),(short)(y + 2 + 5) }, Color::CYAN, Color::BLACK);
	}
}

void View::drawTurnBoard() {
	int x, y;		//x+10 , y+2
	x = 80;
	y = 9;

	View::printCharactors(L"\x2554", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);			//4 corners
	View::printCharactors(L"\x2557", { (short)(x + 10 + 16),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x255a", { (short)(x + 10 + 2),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x255d", { (short)(x + 10 + 16),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2551", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2551", { (short)(x + 10 + 16),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2551", { (short)(x + 10 + 2),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2551", { (short)(x + 10 + 16),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2551", { (short)(x + 10 + 2),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2551", { (short)(x + 10 + 16),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2560", { (short)(x + 10 + 2),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2563", { (short)(x + 10 + 16),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2560", { (short)(x + 10 + 2),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2563", { (short)(x + 10 + 16),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);

	for (int i = 3; i <= 15; i++) {
		View::printCharactors(L"\x2550", { (short)(x + 10 + i),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2550", { (short)(x + 10 + i),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2550", { (short)(x + 10 + i),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2550", { (short)(x + 10 + i),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	}

	View::printCharactors(L"\x2566", { (short)(x + 10 + 9),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2569", { (short)(x + 10 + 9),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2551", { (short)(x + 10 + 9),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);

	//content
	View::printCharactors(L"0:12", { (short)(x + 10 + 8),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"X Turn", { (short)(x + 10 + 7),(short)(y + 2 + 5) }, Color::RED, Color::WHITE);

	View::printCharactors(L"X:", { (short)(x + 10 + 4),(short)(y + 2 + 7) }, Color::RED, Color::WHITE);
	View::printCharactors(L"Y:", { (short)(x + 10 + 11),(short)(y + 2 + 7) }, Color::CYAN, Color::WHITE);

	View::printCharactors(L"11", { (short)(x + 10 + 6),(short)(y + 2 + 7) }, Color::RED, Color::WHITE);
	View::printCharactors(L"12", { (short)(x + 10 + 13),(short)(y + 2 + 7) }, Color::CYAN, Color::WHITE);
}

void View::drawRectangleBorder(COORD spot, int width, int height, Color color) {

	for (short i = spot.X; i < spot.X + width; i++) {
		for (short j = spot.Y; j < spot.Y + height; j++) {
			View::printCharactors(L" ", { i, j }, Color::BLACK, Color::WHITE);
		}
	}
	
	for (short i = spot.X; i < spot.X + width; i++) {
		View::printCharactors(L"=", { i, spot.Y}, color, Color::WHITE);
		View::printCharactors(L"=", { i, short(spot.Y + height - 1) }, color, Color::WHITE);
	}

	for (short i = spot.Y + 1; i < spot.Y + height - 1; i++) {
		View::printCharactors(L"||", { spot.X, i }, color, Color::WHITE);
		View::printCharactors(L"||", { short(spot.X + width - 2), i }, color, Color::WHITE);
	}
}
void View::drawBorder2(int left, int right, int top , int bot) {

	for (int i = left+1; i <= right-1; i++) {
		View::printCharactors(L"═", { (short)( i),(short)(top) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"═", { (short)( i),(short)(bot) }, Color::BLACK, Color::WHITE);
	}
	for (int i = top+1; i <= bot-1; i++) {
		View::printCharactors(L"║", { (short)(left),(short)(i) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"║", { (short)(right),(short)(i) }, Color::BLACK, Color::WHITE);
	}
	View::printCharactors(L"╗", { (short)(right),(short)(top) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"╝", { (short)(right),(short)(bot) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"╔", { (short)(left),(short)(top) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"╚", { (short)(left),(short)(bot) }, Color::BLACK, Color::WHITE);
}

void View::drawXOart() {

	int x, y;
	// default x +10, y +2
	x = 104;
	y = 0;
	//------------------------------------------------CHU O
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color::BLACK, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 2) }, Color::BLACK, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 9),(short)(y + 2 + 2) }, Color::BLACK, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::BLACK, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::BLACK, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 9),(short)(y + 2 + 3) }, Color::BLACK, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 4) }, Color::BLACK, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 4) }, Color::BLACK, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 9),(short)(y + 2 + 4) }, Color::BLACK, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 5) }, Color::BLACK, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 5) }, Color::BLACK, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 9),(short)(y + 2 + 5) }, Color::BLACK, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 6) }, Color::BLACK, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 6) }, Color::BLACK, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 9),(short)(y + 2 + 6) }, Color::BLACK, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 10),(short)(y + 2 + 2) }, Color::BLACK, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 10),(short)(y + 2 + 3) }, Color::BLACK, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 10),(short)(y + 2 + 4) }, Color::BLACK, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 10),(short)(y + 2 + 5) }, Color::BLACK, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 10),(short)(y + 2 + 6) }, Color::BLACK, Color::BLACK);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 5),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 6),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 7),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 8),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 5),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 6),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 7),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2580", { (short)(x + 10 + 4),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 6),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 7),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 8),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 6),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 7),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);


	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::LIGHT_CYAN, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::LIGHT_CYAN, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 4) }, Color::LIGHT_CYAN, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::LIGHT_CYAN, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 6) }, Color::LIGHT_CYAN, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 3) }, Color::LIGHT_CYAN, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 4) }, Color::LIGHT_CYAN, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 5) }, Color::LIGHT_CYAN, Color::BLACK);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 8),(short)(y + 2 + 2) }, Color::LIGHT_CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 8),(short)(y + 2 + 6) }, Color::LIGHT_CYAN, Color::BLACK);


	View::printCharactors(L"\x2584", { (short)(x + 10 + 3),(short)(y + 2 + 1) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 3),(short)(y + 2 + 7) }, Color::LIGHT_CYAN, Color::WHITE);


	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 2) }, Color::LIGHT_RED, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 3) }, Color::LIGHT_RED, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 4) }, Color::LIGHT_RED, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 5) }, Color::LIGHT_RED, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 6) }, Color::LIGHT_RED, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 3) }, Color::LIGHT_RED, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 4) }, Color::LIGHT_RED, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 5) }, Color::LIGHT_RED, Color::BLACK);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 2) }, Color::LIGHT_RED, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 4),(short)(y + 2 + 6) }, Color::LIGHT_RED, Color::BLACK);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 9),(short)(y + 2 + 1) }, Color::LIGHT_RED, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 9),(short)(y + 2 + 7) }, Color::LIGHT_RED, Color::WHITE);

	//-------------------------------------------------------CHU X

	x = 61;
	y = 0;

	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 4) }, Color::BLACK, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 4) }, Color::BLACK, Color::BLACK);

	for (int i = 4; i <= 9; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 3) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 5) }, Color::BLACK, Color::BLACK);
	}

	for (int i = 2; i <= 11; i++) {
		if (i >= 5 && i <= 8) continue;
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 2) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 6) }, Color::BLACK, Color::BLACK);

		View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + i),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	}

	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 4) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 5) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 6) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 2) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 6) }, Color::LIGHT_CYAN, Color::WHITE);

	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 2) }, Color::LIGHT_RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 10),(short)(y + 2 + 3) }, Color::LIGHT_RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 4) }, Color::LIGHT_RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 10),(short)(y + 2 + 5) }, Color::LIGHT_RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 6) }, Color::LIGHT_RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 2) }, Color::LIGHT_RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 6) }, Color::LIGHT_RED, Color::WHITE);


	View::printCharactors(L"\x2584", { (short)(x + 10 + 12),(short)(y + 2 + 1) }, Color::LIGHT_RED, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 12),(short)(y + 2 + 7) }, Color::LIGHT_RED, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 5),(short)(y + 2 + 1) }, Color::LIGHT_RED, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 7) }, Color::LIGHT_RED, Color::WHITE);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 1),(short)(y + 2 + 1) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 7) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 8),(short)(y + 2 + 1) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 8),(short)(y + 2 + 7) }, Color::LIGHT_CYAN, Color::WHITE);
}
void View::drawF1F2list(int x, int y) {
	//int x, y;
	//x = 80;
	//y = 23;

	//info board

	View::printCharactors(L"F1 : Return Hame", { (short)(x),(short)(y) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"F2 : Save game", { (short)(x + 25),(short)(y) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"F3 : Load game", { (short)(x),(short)(y + 1) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"F4 : Undo", { (short)(x + 25),(short)(y + 1 ) }, Color::BLACK, Color::WHITE);	
}
void View::drawTrophy() {
	int x, y;
	x = 82;
	y = 10;

	for (int i = 3; i <= 10; i++) {
		if (i == 4) continue;
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 3) }, Color::LIGHT_CYAN, Color::WHITE);
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 4) }, Color::LIGHT_CYAN, Color::WHITE);
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 5) }, Color::LIGHT_CYAN, Color::WHITE);
	}
	View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 5) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 7) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 8) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 9) }, Color::LIGHT_CYAN, Color::WHITE);
	for (int i = 5; i <= 8; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 6) }, Color::LIGHT_CYAN, Color::WHITE);
	}

	View::printCharactors(L"\x2584", { (short)(x + 10 + 7),(short)(y + 2 + 3) }, Color::PURPLE, Color::LIGHT_CYAN);		//1
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 4) }, Color::PURPLE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 5) }, Color::PURPLE, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 6),(short)(y + 2 + 4) }, Color::LIGHT_CYAN, Color::PURPLE);

	for (int i = 2; i <= 5; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + i) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + i) }, Color::BLACK, Color::WHITE);
	}

	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 12),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
								 
	View::printCharactors(L"\x2580", { (short)(x + 10 + 4),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 9),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 10),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 9) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 10),(short)(y + 2 + 9) }, Color::BLACK, Color::WHITE);

	for (int i = 4; i <= 10; i++) {
		View::printCharactors(L"\x2580", { (short)(x + 10 + i),(short)(y + 2 + 10) }, Color::BLACK, Color::WHITE);
	}
	//2 mau main+black
	for (int i = 3; i <= 10; i++) {
		View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 2) }, Color::LIGHT_CYAN, Color::BLACK);
	}
	View::printCharactors(L"\x2580", { (short)(x + 10 + 4),(short)(y + 2 + 6) }, Color::LIGHT_CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 6),(short)(y + 2 + 7) }, Color::LIGHT_CYAN, Color::BLACK);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 5),(short)(y + 2 + 9) }, Color::LIGHT_CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 6),(short)(y + 2 + 9) }, Color::LIGHT_CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 8),(short)(y + 2 + 9) }, Color::LIGHT_CYAN, Color::BLACK);

	//2 mau shadow + black
	View::printCharactors(L"\x2580", { (short)(x + 10 + 10),(short)(y + 2 + 6) }, Color::LIGHT_PURPLE, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 8),(short)(y + 2 + 7) }, Color::LIGHT_PURPLE, Color::BLACK);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 9),(short)(y + 2 + 9) }, Color::LIGHT_PURPLE, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 11),(short)(y + 2 + 2) }, Color::LIGHT_PURPLE, Color::BLACK);

	//2 mau main + shadow
	View::printCharactors(L"\x2580", { (short)(x + 10 + 9),(short)(y + 2 + 6) }, Color::LIGHT_CYAN, Color::LIGHT_PURPLE);
	
	//shadow
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 3) }, Color::LIGHT_PURPLE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 4) }, Color::LIGHT_PURPLE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 5) }, Color::LIGHT_PURPLE, Color::WHITE);

	//handle
	View::printCharactors(L"\x2580", { (short)(x + 10 + 0),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 13),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 14),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 0),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 13),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 14),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 0),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 14),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2588", { (short)(x + 10 + -1),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 15),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + -1),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 15),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);


}
void View::drawBorder3( int left, int right,int top, int bot) {
	/*
	int top = 2;
	int left = 77;
	int bot = top + 8;
	int right = left + 20;
	*/
	for (int i = left+1 ; i <= right -1 ; i++) {
		View::printCharactors(L"\x2584", { (short)i,(short)top }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2580", { (short)i,(short)bot }, Color::BLACK, Color::WHITE);

		//View::printCharactors(L"\x2584", { (short)i,(short)(bot+2) }, Color::BLACK, Color::WHITE);

	}

	for (int i = top + 1; i <= bot - 1 ; i++) {
		View::printCharactors(L"\x2588", { (short)left,(short)i }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2588", { (short)right,(short)i }, Color::BLACK, Color::WHITE);
	}

	View::printCharactors(L"Quân Phan", { (short)(left + 5),(short)(bot+1)}, Color::BLACK, Color::WHITE);
	
}

void View::drawBotAvatar() {
	int x, y;
	x = 105;		// (105,2)
	y = 2;
	//View::drawBackGroundAvatar(4, x + 6, x + 6 + 18, y , y  + 10);
	//blue

	for (int i = 3; i <= 8; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 2) }, Color::BLUE, Color::WHITE);
	}

	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::BLUE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 4) }, Color::BLUE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 10),(short)(y + 2 + 3) }, Color::BLUE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 10),(short)(y + 2 + 4) }, Color::BLUE, Color::WHITE);

	for (int i = 2; i <= 9; i++) {
		if (i == 5 || i == 6) 	View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 5) }, Color::LIGHT_CYAN, Color::BLACK);
		else View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 5) }, Color::BLUE, Color::BLACK);
	}
	for (int i = 2; i <= 9; i++) {
		if (i == 2 || i == 9) 	View::printCharactors(L"\x2580", { (short)(x + 10 + i),(short)(y + 2 + 6) }, Color::LIGHT_CYAN, Color::BLACK);
		else View::printCharactors(L"\x2580", { (short)(x + 10 + i),(short)(y + 2 + 6) }, Color::BLUE, Color::BLACK);
	}

	//cyan
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 3) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 4) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 3) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 4) }, Color::LIGHT_CYAN, Color::WHITE);

	//blue + cyan
	View::printCharactors(L"\x2584", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color::BLUE, Color::LIGHT_CYAN);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 9),(short)(y + 2 + 2) }, Color::BLUE, Color::LIGHT_CYAN);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::BLUE, Color::LIGHT_CYAN);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 10),(short)(y + 2 + 5) }, Color::BLUE, Color::LIGHT_CYAN);


	//cyan + black
	View::printCharactors(L"\x2584", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::LIGHT_CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 10),(short)(y + 2 + 2) }, Color::LIGHT_CYAN, Color::BLACK);

	View::printCharactors(L"\x2580", { (short)(x + 10 + 0),(short)(y + 2 + 5) }, Color::LIGHT_CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 11),(short)(y + 2 + 5) }, Color::LIGHT_CYAN, Color::BLACK);

	//black
	for (int i = 2; i <= 9; i++) {
		if(i==7) View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
		else View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	}

	View::printCharactors(L"\x2584", { (short)(x + 10 + 0),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 11),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2580", { (short)(x + 10 + -1),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 12),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 10),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2588", { (short)(x + 10 + -1),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + -1),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	
	for (int i = 2; i <= 9; i++) {
		if(i == 3 || i == 8) 	View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 3) }, Color::LIGHT_CYAN, Color::BLACK);
		else View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	}
	
	for (int i = 2; i <= 9; i++) {
		if (i == 3 || i == 8) 	View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 4) }, Color::LIGHT_CYAN, Color::BLACK);
		else View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 4) }, Color::BLACK, Color::BLACK);
	}
	View::printCharactors(L"\x2580", { (short)(x + 10 + 9),(short)(y + 2 + 0) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 8),(short)(y + 2 + 0) }, Color::BLACK, Color::WHITE);
}
void View::drawSpidermanAvatar() {
	int x, y;
	x = 112;		//(104,0)
	y = -2;
	View::drawBackGroundAvatar(2,x+7, x+7 + 18, y+2, y+2 + 10);	
	//red
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	for (int i = 2; i <= 10; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 2) }, Color::RED, Color::WHITE);

	}
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 4) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 4) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 5) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 5) }, Color::RED, Color::WHITE);

	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 6) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 6) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 6) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 6) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 6) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);

	for (int i = 3; i <= 9; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 7) }, Color::RED, Color::WHITE);
	}
	
	//black

	for (int i = 2; i <= 10; i++) {
		View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLACK, Color::LIGHT_CYAN);
	}
	View::printCharactors(L"\x2588", { (short)(x + 10 + -1),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 13),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + -1),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 13),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + -1),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 13),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 0),(short)(y + 2 + 2) }, Color::BLACK, Color::LIGHT_CYAN);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 12),(short)(y + 2 + 2) }, Color::BLACK, Color::LIGHT_CYAN);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 5),(short)(y + 2 + 5) }, Color::BLACK, Color::LIGHT_CYAN);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 7),(short)(y + 2 + 5) }, Color::BLACK, Color::LIGHT_CYAN);

	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 7) }, Color::BLACK, Color::LIGHT_CYAN);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 11),(short)(y + 2 + 7) }, Color::BLACK, Color::LIGHT_CYAN);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 3),(short)(y + 2 + 8) }, Color::BLACK, Color::LIGHT_CYAN);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 9),(short)(y + 2 + 8) }, Color::BLACK, Color::LIGHT_CYAN);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 4) }, Color::BLACK, Color::LIGHT_CYAN);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 7),(short)(y + 2 + 4) }, Color::BLACK, Color::LIGHT_CYAN);

	View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::BLACK, Color::LIGHT_CYAN);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::BLACK, Color::LIGHT_CYAN);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 10),(short)(y + 2 + 3) }, Color::BLACK, Color::LIGHT_CYAN);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 9),(short)(y + 2 + 3) }, Color::BLACK, Color::LIGHT_CYAN);

	//red + black
	View::printCharactors(L"\x2584", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 11),(short)(y + 2 + 2) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 2),(short)(y + 2 + 6) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 3),(short)(y + 2 + 6) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 6) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 8),(short)(y + 2 + 6) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 9),(short)(y + 2 + 6) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 10),(short)(y + 2 + 6) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 6),(short)(y + 2 + 5) }, Color::RED, Color::BLACK);

	for (int i = 4; i <= 8; i++) {
		View::printCharactors(L"\x2580", { (short)(x + 10 + i),(short)(y + 2 + 8) }, Color::RED, Color::BLACK);
	}
	View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 7) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 10),(short)(y + 2 + 7) }, Color::RED, Color::BLACK);


	View::printCharactors(L"\x2580", { (short)(x + 10 + 6),(short)(y + 2 + 4) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 11),(short)(y + 2 + 3) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 4),(short)(y + 2 + 3) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 8),(short)(y + 2 + 3) }, Color::RED, Color::BLACK);
}

void View::drawThanosAvatar() {
	int x, y;
	x = 69;		// (65,0)
	y = -2;

	View::drawBackGroundAvatar(3,x + 7, x+ 7 + 18, y+ 2, y+ 2 + 10);	
	//blue
	View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 2) }, Color::BLUE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 2) }, Color::BLUE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 2) }, Color::BLUE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 2) }, Color::BLUE, Color::WHITE);

	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::BLUE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 3) }, Color::BLUE, Color::WHITE);
	for (int i = 3; i <= 9; i++) {
		if (i == 6) continue;
		else View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 3) }, Color::BLUE, Color::WHITE);
	}

	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 4) }, Color::BLUE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 4) }, Color::BLUE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 4) }, Color::BLUE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 4) }, Color::BLUE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 5) }, Color::BLUE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 5) }, Color::BLUE, Color::WHITE);
	//blue + yellow
	View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::BLUE, Color::YELLOW);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 10),(short)(y + 2 + 3) }, Color::BLUE, Color::YELLOW);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 4) }, Color::BLUE, Color::YELLOW);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 7),(short)(y + 2 + 4) }, Color::BLUE, Color::YELLOW);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::BLUE, Color::YELLOW);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 11),(short)(y + 2 + 5) }, Color::BLUE, Color::YELLOW);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 2),(short)(y + 2 + 4) }, Color::BLUE, Color::YELLOW);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 10),(short)(y + 2 + 4) }, Color::BLUE, Color::YELLOW);

	//yellow
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 2) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 3) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 4) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 4) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 4) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 9),(short)(y + 2 + 4) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 4) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 6) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 6) }, Color::YELLOW, Color::WHITE);

	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 7) }, Color::YELLOW, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 11),(short)(y + 2 + 7) }, Color::YELLOW, Color::BLACK);


	//purple
	for (int i = 3; i <= 9; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 5) }, Color::LIGHT_PURPLE, Color::YELLOW);
	}
	View::printCharactors(L"\x2584", { (short)(x + 10 + 2),(short)(y + 2 + 5) }, Color::LIGHT_PURPLE, Color::YELLOW);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 10),(short)(y + 2 + 5) }, Color::LIGHT_PURPLE, Color::YELLOW);

	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 6) }, Color::LIGHT_PURPLE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 10),(short)(y + 2 + 6) }, Color::LIGHT_PURPLE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 6) }, Color::LIGHT_PURPLE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 6) }, Color::LIGHT_PURPLE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 6) }, Color::LIGHT_PURPLE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 7) }, Color::LIGHT_PURPLE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 7) }, Color::LIGHT_PURPLE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 9),(short)(y + 2 + 7) }, Color::LIGHT_PURPLE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 7) }, Color::LIGHT_PURPLE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 7) }, Color::LIGHT_PURPLE, Color::BLACK);			//---------------
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 7) }, Color::LIGHT_PURPLE, Color::BLACK);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 7) }, Color::LIGHT_PURPLE, Color::BLACK);
	for (int i = 3; i <= 9; i++) {
		if (i == 4 || i == 6 || i == 8) {
			View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 8) }, Color::BLACK, Color::BLACK);
		}else View::printCharactors(L"\x2580", { (short)(x + 10 + i),(short)(y + 2 + 8) }, Color::LIGHT_PURPLE, Color::BLACK);
	}

	View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 7) }, Color::LIGHT_PURPLE, Color::YELLOW);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 10),(short)(y + 2 + 7) }, Color::LIGHT_PURPLE, Color::YELLOW);

	//blue + black
	View::printCharactors(L"\x2584", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color::BLUE, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 3),(short)(y + 2 + 2) }, Color::BLUE, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 10),(short)(y + 2 + 2) }, Color::BLUE, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 9),(short)(y + 2 + 2) }, Color::BLUE, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 0),(short)(y + 2 + 6) }, Color::BLUE, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 12),(short)(y + 2 + 6) }, Color::BLUE, Color::BLACK);
	//black
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + -1),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 13),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + -1),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 13),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 9),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::BLACK, Color::GREEN);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 11),(short)(y + 2 + 2) }, Color::BLACK, Color::GREEN);
	View::printCharactors(L"\x2580", { (short)(x + 10 + -1),(short)(y + 2 + 6) }, Color::BLACK, Color::GREEN);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 13),(short)(y + 2 + 6) }, Color::BLACK, Color::GREEN);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 0),(short)(y + 2 + 7) }, Color::BLACK, Color::GREEN);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 12),(short)(y + 2 + 7) }, Color::BLACK, Color::GREEN);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 8) }, Color::BLACK, Color::GREEN);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 10),(short)(y + 2 + 8) }, Color::BLACK, Color::GREEN);
	for (int i = 4; i <= 8; i++) {
		View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLACK, Color::GREEN);
	}

}
void View::drawIronmanAvatar() {

	int x, y;				// (65,0)
	x = 65;
	y = 0;
	//View::drawBackGroundAvatar(1,71, 71 + 20, 2, 2 + 10);	
	View::drawBackGroundAvatar(1, x + 7, x + 7 + 18, y + 2, y + 2 + 10);
	//red
	for (int i = 4; i <= 8; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 2) }, Color::RED, Color::WHITE);
	}
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);

	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 4) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 5) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 5) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 4) }, Color::RED, Color::WHITE);

	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 6) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 6) }, Color::RED, Color::WHITE);

	//black
	for (int i = 2; i <= 10; i++) {
		View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLACK, Color::LIGHT_BLUE);
	}

	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + -1),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 13),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + -1),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 13),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);


	//YELLOW + BLACK
	for(int i = 2 ; i<=10 ; i++){
		View::printCharactors(L"\x2580", { (short)(x + 10 + i),(short)(y + 2 + 4) }, Color::YELLOW, Color::BLACK);

	}
	for (int i = 2; i <= 10; i++) {
		if (i >=5 && i <=7) View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 5) }, Color::YELLOW, Color::BLACK);
		else{
			View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 5) }, Color::YELLOW, Color::WHITE);						//----------------LIGHT_BLUE
		}
	}
	for (int i = 4; i <= 8; i++) {
		View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 7) }, Color::YELLOW, Color::BLACK);
	}
	View::printCharactors(L"\x2580", { (short)(x + 10 + 3),(short)(y + 2 + 7) }, Color::YELLOW, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 9),(short)(y + 2 + 7) }, Color::YELLOW, Color::BLACK);

	//yellow
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 9),(short)(y + 2 + 3) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 10),(short)(y + 2 + 3) }, Color::YELLOW, Color::WHITE);

	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 5) }, Color::YELLOW, Color::WHITE);
	for (int i = 2; i <= 10; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 6) }, Color::YELLOW, Color::WHITE);
	}


	// yellow+ red
	View::printCharactors(L"\x2584", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color::YELLOW, Color::RED);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 3),(short)(y + 2 + 2) }, Color::YELLOW, Color::RED);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 9),(short)(y + 2 + 2) }, Color::YELLOW, Color::RED);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 10),(short)(y + 2 + 2) }, Color::YELLOW, Color::RED);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 3) }, Color::YELLOW, Color::RED);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 8),(short)(y + 2 + 3) }, Color::YELLOW, Color::RED);

	//red + black
	View::printCharactors(L"\x2584", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 11),(short)(y + 2 + 2) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 7) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 10),(short)(y + 2 + 7) }, Color::RED, Color::BLACK);
	for (int i = 4; i <= 8; i++) {
		View::printCharactors(L"\x2580", { (short)(x + 10 + i),(short)(y + 2 + 8) }, Color::RED, Color::BLACK);
	}

	//black + WHITE
	View::printCharactors(L"\x2584", { (short)(x + 10 + 0),(short)(y + 2 + 2) }, Color::BLACK, Color::LIGHT_BLUE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 12),(short)(y + 2 + 2) }, Color::BLACK, Color::LIGHT_BLUE);

	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 7) }, Color::BLACK, Color::LIGHT_BLUE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 11),(short)(y + 2 + 7) }, Color::BLACK, Color::LIGHT_BLUE);

	View::printCharactors(L"\x2580", { (short)(x + 10 + 3),(short)(y + 2 + 8) }, Color::BLACK, Color::LIGHT_BLUE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 9),(short)(y + 2 + 8) }, Color::BLACK, Color::LIGHT_BLUE);
}

void View::drawBackGroundAvatar(int n,int left , int right, int top , int bot) {
	
	switch (n)
	{
	case 1:
		for (int i = top + 1; i <= bot - 1; i++) {
			for (int j = left; j <= right; j++) {
				View::printCharactors(L"\x2588", { (short)(j),(short)(i) }, Color::LIGHT_BLUE, Color::WHITE);
			}
		}
		break;
	case 2:
		for (int i = top + 1; i <= bot - 1; i++) {
			for (int j = left; j <= right; j++) {
				View::printCharactors(L"\x2588", { (short)(j),(short)(i) }, Color::LIGHT_CYAN, Color::WHITE);
			}
		}
		break;
	case 3:
		for (int i = top + 1; i <= bot - 1; i++) {
			for (int j = left; j <= right; j++) {
				View::printCharactors(L"\x2588", { (short)(j),(short)(i) }, Color::GREEN, Color::WHITE);
			}
		}
		break;
	default:
		break;
	}

	
}

void View::drawVSText() {
	int x, y;
	x = 91;
	y = 1;
	//chu V
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 4),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);

	x = 96;
	y = 3;
	//chu S
	View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 3),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 3),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 5),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);

}


//-------------------------------------------splash screen------------------------------
void View::splashScreenInfo() {
	int x, y;
	x = 50;
	y = 12;

	View::printCharactors(L"        NHÓM 10", { (short)(x + 10),(short)(y + 2) }, Color::BLACK, Color::WHITE); Sleep(300);
	View::printCharactors(L" GV: Trương Toàn Thịnh", { (short)(x + 10),(short)(y + 4) }, Color::BLACK, Color::WHITE); Sleep(400);

	View::printCharactors(L" Huỳnh Anh Huy			", { (short)(x + 10),(short)(y + 6) }, Color::BLACK, Color::WHITE); Sleep(400);
	View::printCharactors(L" Phan Nguyễn Hoàng Quân	", { (short)(x + 10),(short)(y + 7) }, Color::BLACK, Color::WHITE); Sleep(400);
	View::printCharactors(L" Nguyễn Lâm Anh Duy		", { (short)(x + 10),(short)(y + 8) }, Color::BLACK, Color::WHITE); Sleep(400);
	View::printCharactors(L" Lê Hải Nam				", { (short)(x + 10),(short)(y + 9) }, Color::BLACK, Color::WHITE); Sleep(300);
}
void View::splashScreen() {
	//system("cls");
	View::fixConsoleWindow();
	int x, y;
	x = 25;
	y = 2;

	Sleep(300);
	View::printCharactors(L"	░█████╗░░█████╗░██████╗░░█████╗░  ░██████╗░░█████╗░███╗░░░███╗███████╗		", { (short)(10 + x),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	Sleep(400);
	View::printCharactors(L"	██╔══██╗██╔══██╗██╔══██╗██╔══██╗  ██╔════╝░██╔══██╗████╗░████║██╔════╝	    ", { (short)(10 + x),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	Sleep(400);
	View::printCharactors(L"	██║░░╚═╝███████║██████╔╝██║░░██║  ██║░░██╗░███████║██╔████╔██║█████╗░░	    ", { (short)(10 + x),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	Sleep(400);
	View::printCharactors(L"	██║░░██╗██╔══██║██╔══██╗██║░░██║  ██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░	    ", { (short)(10 + x),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	Sleep(400);
	View::printCharactors(L"	╚█████╔╝██║░░██║██║░░██║╚█████╔╝  ╚██████╔╝██║░░██║██║░╚═╝░██║███████╗	    ", { (short)(10 + x),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	Sleep(400);
	View::printCharactors(L"	░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝░╚════╝░  ░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝		", { (short)(10 + x),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	Sleep(400);

	View::splashScreenInfo();
	View::drawPacman();

	system("pause");
	gotoXY(10, 50);
}
void View::drawPacman() {
	int x, y;
	x = -5;
	y = 25;
	int color;
	//srand((unsigned int)time(NULL));				//?
	for (int i = 1; i <= 13; i++) {				//number of ghosts

		color = View::GetRandom(1, 13);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color(color), Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 2) }, Color(color), Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 2) }, Color(color), Color::BLACK);

		View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 3) }, Color(color), Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color(color), Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 3) }, Color(color), Color::BLACK);

		for (int i = 0; i <= 6; i++) {
			View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 4) }, Color(color), Color::BLACK);
		}

		View::printCharactors(L"\x2584", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color(color), Color::WHITE);
		View::printCharactors(L"\x2584", { (short)(x + 10 + 5),(short)(y + 2 + 2) }, Color(color), Color::WHITE);

		View::printCharactors(L"\x2580", { (short)(x + 10 + 0),(short)(y + 2 + 5) }, Color(color), Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 5) }, Color(color), Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 4),(short)(y + 2 + 5) }, Color(color), Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 6),(short)(y + 2 + 5) }, Color(color), Color::WHITE);

		View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
		Sleep(300);

		x += 10;
	}

}

//random function in range
int View::GetRandom(int min, int max) {							
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}
//----------------------------------------------------------------------------------------
void View::gotoXY(short x, short y) {
	static HANDLE h = NULL;
	if (!h) h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { x, y };
	SetConsoleCursorPosition(h, coord);
}

void View::fixConsoleWindow() {
	system("color f0");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void View::textColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void View::textStyle(int fontSize) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = fontSize;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

std::ostream& View::bold_on(std::ostream& os)
{
	return os << "\e[1m";
}

std::ostream& View::bold_off(std::ostream& os)
{
	return os << "\e[0m";
}

void View::clearRectangleArea(
	COORD start, 
	int width, 
	int height
) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwWritten;
	int startY = start.Y;
	
	for (int i = startY; i < height; i++) {
		FillConsoleOutputCharacterA(hOut, ' ', width, start, &dwWritten);
		start.Y++;
	}
}

void View::printCharactors(
	std::wstring content, 
	COORD spot, 
	Color text_color,
	Color background_color
) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD Written;

	// convert text color and background color to WORD that in range of 0-265 in color code table
	int color = (int)text_color + (int)background_color * 16;

	for (int i = 0; i < content.length(); i++) {
		// set text background color
		FillConsoleOutputAttribute(hOut, color, 1, spot, &Written);
		
		// print 1 character 
		FillConsoleOutputCharacterW(hOut, content[i], 1, spot, &Written);
		spot.X++;
	}
}

void View::printVerticalCenteredCharactors(
	std::wstring content,
	SMALL_RECT box,
	short y_offset,
	View::Color text_color,
	View::Color background_color
) {
	short x = box.Left + (box.Right - box.Left) / 2 - content.length() / 2;
 	printCharactors(content, { x, short(box.Top + y_offset) }, text_color, background_color);
}

PCHAR_INFO View::getScreenBuffer() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	PCHAR_INFO buffer = new CHAR_INFO[View::SCREEN_WIDTH * View::SCREEN_HEIGHT];
	SMALL_RECT readRegion = { 0, 0, View::SCREEN_WIDTH - 1, View::SCREEN_HEIGHT - 1 };

	ReadConsoleOutput(hOut, buffer, { View::SCREEN_WIDTH, View::SCREEN_HEIGHT }, { 0, 0 }, &readRegion);
	
	return buffer;
}

void View::writeScreenBuffer(PCHAR_INFO buffer) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT writeRegion = { 0, 0, View::SCREEN_WIDTH - 1, View::SCREEN_HEIGHT - 1 };

	WriteConsoleOutput(hOut, buffer, { View::SCREEN_WIDTH, View::SCREEN_HEIGHT }, { 0, 0 }, &writeRegion);
}

void View::confirmDialog(
	std::wstring content,
	COORD spot,
	function<void()> positiveAction,
	function<void()> negativeAction
) {
	int width = content.size() + 20;
	View::drawRectangleBorder(spot, width, 10, View::Color::BLACK);
	// print dialog title
	View::printVerticalCenteredCharactors(
		L"Confirm Dialog",
		{ spot.X, spot.Y, short(spot.X + width), short(spot.Y + 10) },
		2,
		View::Color::BLACK,
		View::Color::WHITE
	);
	
	// print dialog content
	View::printVerticalCenteredCharactors(
		content,
		{ spot.X, spot.Y, short(spot.X + width), short(spot.Y + 10) },
		4,
		View::Color::BLACK,
		View::Color::WHITE
	);

	// print dialog buttons
	int indx = 0;
	MenuItem items[] = {
		{ 0, L"YES", MenuOption::YES },
		{ 1, L"NO", MenuOption::NO }
	};

	short center_x = spot.X + width / 2;
	
	drawMenu(items, { center_x, short(spot.Y + 6) }, View::Color::BLACK, View::Color::PURPLE, &indx, 2);
	menuOptionChanged(items, { center_x, short(spot.Y + 6) }, View::Color::BLACK, View::Color::PURPLE, &indx, 2);

	switch (items[indx].menu_option) {
	case MenuOption::YES:
		positiveAction();
		break;
	case MenuOption::NO:
		negativeAction();
		break;

	default:
		negativeAction();
		break;
	}
}

COORD View::getCenteredSpot(std::wstring content, SMALL_RECT box) {
	short x = box.Left + (box.Right - box.Left) / 2 - content.length() / 2;
	short y = box.Top + (box.Bottom - box.Top) / 2;
	return { x, y };
}

void View::printCenteredToast(std::wstring content, SMALL_RECT box, View::Color text_color, View::Color background_color) {
	system("cls");
	COORD spot = View::getCenteredSpot(content, box);
	View::printCharactors(content, spot, text_color, background_color);
}

void View::showWinningMoves(int player, std::vector<COORD> winning_moves) {
	wstring winner_ws = player == 1 ? L"X" : L"O";
	for (int i = 0; i < winning_moves.size(); i++) {
		View::printCharactors(winner_ws, winning_moves[i], View::Color::BLACK, View::Color::YELLOW);
	}
}

//void View::splashScreenInfo() {
//	int x, y;
//	x = 50;
//	y = 12;
//
//	View::printCharactors(L"        NHÓM 10", { (short)(x + 10),(short)(y + 2) }, Color::BLACK, Color::WHITE); Sleep(300);
//	View::printCharactors(L" GV: Trương Toàn Thịnh", { (short)(x + 10),(short)(y + 4) }, Color::BLACK, Color::WHITE); Sleep(400);
//
//	View::printCharactors(L" Huỳnh Anh Huy			", { (short)(x + 10),(short)(y + 6) }, Color::BLACK, Color::WHITE); Sleep(400);
//	View::printCharactors(L" Phan Nguyễn Hoàng Quân	", { (short)(x + 10),(short)(y + 7) }, Color::BLACK, Color::WHITE); Sleep(400);
//	View::printCharactors(L" Nguyễn Lâm Anh Duy		", { (short)(x + 10),(short)(y + 8) }, Color::BLACK, Color::WHITE); Sleep(400);
//	View::printCharactors(L" Lê Hải Nam				", { (short)(x + 10),(short)(y + 9) }, Color::BLACK, Color::WHITE); Sleep(300);
//}
//void View::splashScreen() {
//	//system("cls");
//	View::fixConsoleWindow();
//	
//	Sound::playSound(Sound::background);
//	View::drawCaroGameText(200);
//	View::splashScreenInfo();
//	View::drawPacman();
//
//	system("pause");
//	gotoXY(10, 50);
//}
//void View::drawPacman() {
//	int x, y;
//	x = -5;
//	y = 25;
//	int color;
//	//srand((unsigned int)time(NULL));				//?
//	for (int i = 1; i <= 13; i++) {				//number of ghosts
//
//		color = View::GetRandom(1, 13);
//		View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color(color), Color::BLACK);
//		View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 2) }, Color(color), Color::BLACK);
//		View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 2) }, Color(color), Color::BLACK);
//
//		View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 3) }, Color(color), Color::BLACK);
//		View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color(color), Color::BLACK);
//		View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 3) }, Color(color), Color::BLACK);
//
//		for (int i = 0; i <= 6; i++) {
//			View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 4) }, Color(color), Color::BLACK);
//		}
//
//		View::printCharactors(L"\x2584", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color(color), Color::WHITE);
//		View::printCharactors(L"\x2584", { (short)(x + 10 + 5),(short)(y + 2 + 2) }, Color(color), Color::WHITE);
//
//		View::printCharactors(L"\x2580", { (short)(x + 10 + 0),(short)(y + 2 + 5) }, Color(color), Color::WHITE);
//		View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 5) }, Color(color), Color::WHITE);
//		View::printCharactors(L"\x2580", { (short)(x + 10 + 4),(short)(y + 2 + 5) }, Color(color), Color::WHITE);
//		View::printCharactors(L"\x2580", { (short)(x + 10 + 6),(short)(y + 2 + 5) }, Color(color), Color::WHITE);
//
//		View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
//		View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
//		Sleep(100);
//
//		x += 10;
//	}
//
//}
void View::drawCaroGameText(int delayTime) {
	int x, y;
	x = 25;
	y = 2;
	Sleep(delayTime);
	View::printCharactors(L"	░█████╗░░█████╗░██████╗░░█████╗░  ░██████╗░░█████╗░███╗░░░███╗███████╗		", { (short)(10 + x),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	Sleep(delayTime);
	View::printCharactors(L"	██╔══██╗██╔══██╗██╔══██╗██╔══██╗  ██╔════╝░██╔══██╗████╗░████║██╔════╝	    ", { (short)(10 + x),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	Sleep(delayTime);
	View::printCharactors(L"	██║░░╚═╝███████║██████╔╝██║░░██║  ██║░░██╗░███████║██╔████╔██║█████╗░░	    ", { (short)(10 + x),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	Sleep(delayTime);
	View::printCharactors(L"	██║░░██╗██╔══██║██╔══██╗██║░░██║  ██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░	    ", { (short)(10 + x),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	Sleep(delayTime);
	View::printCharactors(L"	╚█████╔╝██║░░██║██║░░██║╚█████╔╝  ╚██████╔╝██║░░██║██║░╚═╝░██║███████╗	    ", { (short)(10 + x),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	Sleep(delayTime);
	View::printCharactors(L"	░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝░╚════╝░  ░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝		", { (short)(10 + x),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	Sleep(delayTime);
}
//int View::GetRandom(int min, int max) {							//random function in range
//	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
//}
wstring format(int t) {
	wstring time = to_wstring(t);
	if (t < 10) {
		time = L"0" + to_wstring(t);
	}
	return time;
}

void View::clock(short x, short y, int width, int height) {
	int min = 0, sc = 0;
	wstring time = format(min) + L":" + format(sc);
	View::printVerticalCenteredCharactors(
		time,
		{ x,y,short(x + width),short(y + height) },
		short(height / 2),
		View::Color::BLACK,
		View::Color::WHITE
	);
	sc++;
	wstring input = InputHandle::Get();
	if (input == L"ENTER") {
		while (1 /*Win or Lost*/) {
			wstring time = format(min) + L":" + format(sc);
			View::printVerticalCenteredCharactors(
				time,
				{ x,y,short(x + width),short(y + height) },
				2,
				View::Color::BLACK,
				View::Color::WHITE
			);
			Sleep(1000);
			sc++;
			if (sc == 60) {
				sc = 0;
				min++;
			}
		}
	}

}

void View::drawBox(COORD spot, int width, int height, Color color) {
	short x = spot.X + width;
	short y = spot.Y + height;
	for (short i = spot.X; i <= x; i++) {
		View::printCharactors(L"═", { i,spot.Y }, color, Color::WHITE);
		View::printCharactors(L"═", { i,y }, color, Color::WHITE);
	}

	for (short j = spot.Y; j <= y; j++) {
		View::printCharactors(L"║", { spot.X,j }, color, Color::WHITE);
		View::printCharactors(L"║", { x,j }, color, Color::WHITE);
	}
	View::printCharactors(L"╔", spot, color, Color::WHITE);

	View::printCharactors(L"╗", { x,spot.Y }, color, Color::WHITE);

	View::printCharactors(L"╚", { spot.X,y }, color, Color::WHITE);

	View::printCharactors(L"╝", { x,y }, color, Color::WHITE);
}

void View::drawGamePlayInfoBox(COORD spot, int width, int height, Color color) {
	short maxX = spot.X + width;
	short maxY = spot.Y + height;

	drawBox(spot, width, height, color);
	drawBox(spot, width, int(height - height / 2 - 2), color);
	drawBox(spot, int((width - 4) / 3 + 1), int(height / 2 - 2), color);
	drawBox(spot, int(((width - 4) / 3) * 2 + 3), int(height / 2 - 2), color);
	drawBox(spot, int((width - 4) / 3 + 1), int((height / 2 - 2) / 2), color);

	short x = spot.X + (width - 4) / 3 + 1;
	short y = spot.Y + (height / 2 - 2);

	drawBox({ x ,spot.Y }, int((width - 4) / 3 + 2), int((height / 2 - 2) / 2), color);

	x = spot.X + (((width - 4) / 3) * 2 + 3);
	drawBox({ x ,spot.Y }, int(width - 4) / 3 + 1, int((height / 2 - 2) / 2), color);

	y = spot.Y + (height / 2 - 2);
	drawBox({ spot.X,y }, int((width - 4) / 2 + 3), int(height - (height / 2 - 2)), color);


	/*╩╦╠╣╬*/
	x = spot.X;
	y = spot.Y + (height / 2 - 2);

	View::printCharactors(L"╠", { x,y }, color, Color::WHITE);
	View::printCharactors(L"╣", { maxX,y }, color, Color::WHITE);

	y = spot.Y + (height / 2 - 2) / 2;
	View::printCharactors(L"╠", { x,y }, color, Color::WHITE);
	View::printCharactors(L"╣", { maxX,y }, color, Color::WHITE);

	x = spot.X + (width - 4) / 3 + 1;
	y = spot.Y + ((height / 2 - 2) / 2);

	View::printCharactors(L"╬", { x,y }, color, Color::WHITE);
	View::printCharactors(L"╦", { x,spot.Y }, color, Color::WHITE);

	y = spot.Y + (height / 2 - 2);
	View::printCharactors(L"╩", { x,y }, color, Color::WHITE);

	x = spot.X + (((width - 4) / 3) * 2 + 3);
	y = spot.Y + (height / 2 - 2);
	View::printCharactors(L"╦", { x,spot.Y }, color, Color::WHITE);
	View::printCharactors(L"╩", { x,y }, color, Color::WHITE);

	y = spot.Y + (height / 2 - 2) / 2;
	View::printCharactors(L"╬", { x,y }, color, Color::WHITE);

	x = spot.X + (width - 4) / 2 + 3;
	y = spot.Y + (height / 2 - 2);
	View::printCharactors(L"╦", { x,y }, color, Color::WHITE);
	View::printCharactors(L"╩", { x,maxY }, color, Color::WHITE);

	x = spot.X + ((width - 4) / 3 + 1);
	View::printVerticalCenteredCharactors(
		L"TIMER",
		{ x,spot.Y,short(x + ((width - 4) / 3 + 3)),short(spot.Y + ((height / 2 - 2) / 2)) },
		short(((height / 2 - 2) / 2) / 2),
		View::Color::BLACK,
		View::Color::WHITE
	);

	View::printVerticalCenteredCharactors(
		L"X's moves",
		{ spot.X,spot.Y,short(spot.X + ((width - 4) / 3 + 2)),short(spot.Y + ((height / 2 - 2) / 2)) },
		short(((height / 2 - 2) / 2) / 2),
		View::Color::BLACK,
		View::Color::WHITE
	);

	x = spot.X + (((width - 4) / 3) * 2 + 2);
	y = spot.Y;

	View::printVerticalCenteredCharactors(
		L"O's moves",
		{ x,y,short(x + (width - 4) / 3 + 4),short(y + ((height / 2 - 2) / 2)) },
		short(((height / 2 - 2) / 2) / 2),
		View::Color::BLACK,
		View::Color::WHITE
	);

	x = spot.X;
	y = spot.Y + (height / 2 - 2);

	View::printVerticalCenteredCharactors(
		L"TURN",
		{ x,y,short(x + (width - 4) / 2 + 3),short(y + ((height / 2 - 2) / 2)) },
		2,
		View::Color::BLACK,
		View::Color::WHITE
	);

	x = spot.X + (width - 4) / 2 + 3;
	y = spot.Y + (height / 2 - 2);

	View::printVerticalCenteredCharactors(
		L"HISTORY",
		{ x,y,short(x + (width - 4) / 2 + 3),short(y + ((height / 2 - 2) / 2)) },
		2,
		View::Color::BLACK,
		View::Color::WHITE
	);

	int moveX = 0, moveY = 0;
	int count = 0;
	x = spot.X;
	y = spot.Y + (height / 2 - 2) / 2;
	wstring xMoves = format(moveX);
	View::printVerticalCenteredCharactors(
		xMoves,
		{ x,y,short(x + (width - 4) / 3 + 2),short(y + ((height / 2 - 2) / 2)) },
		short(((height / 2 - 2) / 2) / 2),
		View::Color::BLACK,
		View::Color::WHITE
	);
	x = spot.X + (((width - 4) / 3) * 2 + 3);
	y = spot.Y + (height / 2 - 2) / 2;
	wstring yMoves = format(moveY);
	View::printVerticalCenteredCharactors(
		yMoves,
		{ x,y,short(x + (width - 4) / 3 + 2),short(y + ((height / 2 - 2) / 2)) },
		short(((height / 2 - 2) / 2) / 2),
		View::Color::BLACK,
		View::Color::WHITE
	);
	/*x = spot.X;
	y = spot.Y + (height / 2 - 2) / 2;

	int moveX = 0;
	wstring xMoves = format(moveX);
	View::printVerticalCenteredCharactors(
			xMoves,
		{ x,y,short(x + (width - 4) / 3 + 2),short(y + ((height / 2 - 2) / 2)) },
		short(((height / 2 - 2) / 2) / 2),
		View::Color::BLACK,
		View::Color::WHITE
	);

	x = spot.X + (((width - 4) / 3) * 2 + 3);
	y = spot.Y + (height / 2 - 2) / 2;


	int moveY = 0;
	wstring yMoves = format(moveY);
	View::printVerticalCenteredCharactors(
		yMoves,
		{ x,y,short(x + (width - 4) / 3 + 2),short(y + ((height / 2 - 2) / 2)) },
		short(((height / 2 - 2) / 2) / 2),
		View::Color::BLACK,
		View::Color::WHITE
	);*/


	x = spot.X + (width - 4) / 3 + 1;
	y = spot.Y + (height / 2 - 2) / 2;
	View::clock(x, y, int((width - 4) / 3 + 3), int((height / 2 - 2) / 2));
}
