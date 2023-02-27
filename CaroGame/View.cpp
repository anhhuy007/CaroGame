#include "View.h"

using namespace std;

void drawBoard() {
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

void gotoXY(int x, int y) {
	static HANDLE h = NULL;
	if (!h) h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { x, y };
	SetConsoleCursorPosition(h, coord);
}

// set full screen console and fix it _SIZE
void fixConsoleWindow() {
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void textColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void textStyle() {
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

void clearRectangleArea(COORD start, int width, int height) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwWritten;
	
	for (int i = 0; i < height; i++) {
		gotoXY(start.X, start.Y + i);
		FillConsoleOutputCharacterA(hOut, ' ', width, start, &dwWritten);
	}
}

void testFunction() {
	COORD spot = { 0,0 };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD Written;

	for (int i = 0; 60 < 256; i++)
	{
		//FillConsoleOutputAttribute(hOut, 7, 1, spot, &Written);
		FillConsoleOutputCharacterW(hOut, char(i), 10, spot, &Written);

		spot.Y++;
	}
}