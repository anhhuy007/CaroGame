#include "View.h"

using namespace std;

// draw board with Size x Size cells
void View::drawBoard() {
	// draw TOP
	gotoXY(LEFT + 1, TOP);
	for (int i = 0; i < (2 * _SIZE); i++) {
		if (i % 2) {
			cout << char(194);
		}
		else {
			cout << char(196) << char(196) << char(196);
		}		
	}

	// draw BOTTOM
	gotoXY(LEFT + 1, BOT);
	for (int i = 0; i < (2 * _SIZE); i++) {
		if (i % 2) {
			cout << char(193);
		}
		else {
			cout << char(196) << char(196) << char(196);
		}
	}

	for (int i = 0; i < 2 * _SIZE; i++) {
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
	for (int j = 0; j < 4 * _SIZE - 1; j++) {
		if (j % 4) {
			s1[j] = ' ';
		}
		else {
			s1[j] = 179;
		}
	}

	for (int j = 0; j < 4 * _SIZE - 1; j++) {
		if ((j + 1) % 4) {
			s2[j] = 196;
		}
		else {
			s2[j] = 197;
		}
	}

	s1[4 * _SIZE - 1] = '\0';
	s2[4 * _SIZE - 1] = '\0';

	int i = 1;
	while (i < 2 * _SIZE - 1) {
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

void View::drawInfoBorder(int x, int y) {
	int right = y + 25;
	int bot = x + 13;

	gotoXY(y, x); printf("%c", 201);
	gotoXY(right, x); printf("%c", 187);
	gotoXY(y, bot); printf("%c", 200);
	gotoXY(right, bot); printf("%c", 188);
	for (int i = y + 1; i < right; i++) {
		gotoXY(i, x);
		printf("%c", (char)205);
	}


	for (int i = y + 1; i < right; i++) {

		gotoXY(i, bot);
		printf("%c", (char)205);
	}

	//2 sides

	for (int i = x + 1; i < bot; i++) {
		gotoXY(y, i);
		printf("%c", (char)186);
	}

	for (int i = x + 1; i < bot; i++) {
		gotoXY(right, i);
		printf("%c\n", (char)186);
	}
}

void View::drawOtherDetail() {
	vector<string> a;

	a.resize(0);
	a.push_back(" 0=======================0 ");
	a.push_back(" |                       | ");
	a.push_back(" |      Y88b   d88P      | ");
	a.push_back(" |       Y88b d88P       | ");
	a.push_back(" |        Y88o88P        | ");
	a.push_back(" |         Y888P         | ");
	a.push_back(" |          888          | ");
	a.push_back(" |          888          | ");
	a.push_back(" |          888          | ");
	a.push_back(" |          888          | ");
	a.push_back(" |                       | ");
	a.push_back(" 0=======================0 ");

	for (int i = 0; i < a.size(); i++) {
		gotoXY(100, 2 + i);
		cout << a[i];

	}

	a.resize(0);
	a.push_back(" 0======================0 ");
	a.push_back(" |                      | ");
	a.push_back(" |     Y88b   d88P      | ");
	a.push_back(" |      Y88b d88P       | ");
	a.push_back(" |       Y88o88P        | ");
	a.push_back(" |        Y888P         | ");
	a.push_back(" |        d888b         | ");
	a.push_back(" |       d88888b        | ");
	a.push_back(" |      d88P Y88b       | ");
	a.push_back(" |     d88P   Y88b      | ");
	a.push_back(" |                      | ");
	a.push_back(" 0======================0 ");

	for (int i = 0; i < a.size(); i++) {
		gotoXY(70, 2 + i);
		cout << a[i];

	}
	a.resize(0);

	//info board
	a.push_back("F1 : New game   ");
	a.push_back("");
	a.push_back("F2 : Save game  ");
	a.push_back("");
	a.push_back("F3 : Load game  ");
	a.push_back("");
	a.push_back("F4 : Undo       ");
	a.push_back("");
	a.push_back("Esc: Return home");

	for (int i = 0; i < a.size(); i++) {
		gotoXY(90, 17 + i);
		cout << a[i];
	}

}

void View::gotoXY(int x, int y) {
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

void View::textStyle() {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 24;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
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

void View::xWinScreen() {
	fixConsoleWindow();
	vector <string> a;

	a.resize(0);

	a.push_back("     ===========================================================   ");
	a.push_back("     o      O       o          `O ooOoOOo o.     O      oO oO oO   ");
	a.push_back("      O    o        O           o    O    Oo     o      OO OO OO   ");
	a.push_back("       o  O         o           O    o    O O    O      oO oO oO   ");
	a.push_back("        oO          O           O    O    O  o   o      Oo Oo Oo   ");
	a.push_back("        Oo          o     o     o    o    O   o  O      oO oO oO   ");
	a.push_back("       o  o         O     O     O    O    o    O O                 ");
	a.push_back("      O    O        `o   O o   O'    O    o     Oo      Oo Oo Oo   ");
	a.push_back("     O      o        `OoO' `OoO'  ooOOoOo O     `o      oO oO oO   ");
	a.push_back("     ===========================================================   ");

	for (int i = 0; i < a.size(); i++) {
		gotoXY(30, 10 + i);
		cout << a[i];
	}

	a.resize(0);

	a.push_back("Yes[Press 'Y']   : New Game");
	a.push_back("");
	a.push_back("No[N / press any key]   : Back to Menu");


	for (int i = 0; i < a.size(); i++) {
		gotoXY(50, 23 + i);
		cout << a[i];
	}
	PlaySound(TEXT("D:\\Caro\\Win.wav"), NULL, SND_FILENAME);
}

void View::yWinScreen() {
	fixConsoleWindow();
	vector <string> a;

	a.resize(0);

	a.push_back("         ===========================================================   ");
	a.push_back("         o       O      o          `O ooOoOOo o.     O      oO oO oO   ");
	a.push_back("         O       o      O           o    O    Oo     o      OO OO OO   ");
	a.push_back("         `o     O'      o           O    o    O O    O      oO oO oO   ");
	a.push_back("           O   o        O           O    O    O  o   o      Oo Oo Oo   ");
	a.push_back("            `O'         o     o     o    o    O   o  O      oO oO oO   ");
	a.push_back("             o          O     O     O    O    o    O O                 ");
	a.push_back("             O          `o   O o   O'    O    o     Oo      Oo Oo Oo   ");
	a.push_back("             O           `OoO' `OoO'  ooOOoOo O     `o      oO oO oO   ");
	a.push_back("         ===========================================================   ");

	for (int i = 0; i < a.size(); i++) {
		gotoXY(30, 10 + i);
		cout << a[i];
	}

	a.resize(0);

	a.push_back("Yes[Press 'Y']   : New Game");
	a.push_back("");
	a.push_back("No[N / press any key]   : Back to Menu");


	for (int i = 0; i < a.size(); i++) {
		gotoXY(50, 23 + i);
		cout << a[i];
	}
	PlaySound(TEXT("D:\\Caro\\Win.wav"), NULL, SND_FILENAME);
}

void View::drawScreen() {
	fixConsoleWindow();
	vector <string> a;

	a.resize(0);

	a.push_back("         ===========================================================   ");
	a.push_back("        o.OOOo.   `OooOOo.     Oo    o          `O       oO oO oO      ");
	a.push_back("         O    `o   o     `o   o  O   O           o       OO OO OO      ");
	a.push_back("         o      O  O      O  O    o  o           O       oO oO oO      ");
	a.push_back("         O      o  o     .O oOooOoOo O           O       Oo Oo Oo      ");
	a.push_back("         o      O  OOooOO'  o      O o     o     o       oO oO oO      ");
	a.push_back("         O      o  o    o   O      o O     O     O                     ");
	a.push_back("         o    .O'  O     O  o      O `o   O o   O'       Oo Oo Oo      ");
	a.push_back("         OooOO'    O      o O.     O  `OoO' `OoO'        oO oO oO      ");
	a.push_back("         ===========================================================   ");

	for (int i = 0; i < a.size(); i++) {
		gotoXY(30, 10 + i);
		cout << a[i];
	}

	a.resize(0);

	a.push_back("Yes[Press 'Y']   : New Game");
	a.push_back("");
	a.push_back("No[N / press any key]   : Back to Menu");


	for (int i = 0; i < a.size(); i++) {
		gotoXY(50, 23 + i);
		cout << a[i];
	}
	PlaySound(TEXT("D:\\Caro\\Win.wav"), NULL, SND_FILENAME);
}