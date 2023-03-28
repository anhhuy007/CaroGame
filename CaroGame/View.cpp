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
	
	Sound::playSound(Sound::background);
	View::drawCaroGameText(200);
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
		Sleep(100);

		x += 10;
	}

}
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
int View::GetRandom(int min, int max) {							//random function in range
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}
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
	drawBox(spot, width, int(height / 2 - 2), color);
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
	wstring input = InputHandle::Get();
	if (input == L"ENTER") {
		count += 1;
		count %= 2;
		if (count == 0) {
			x = spot.X;
			y = spot.Y + (height / 2 - 2) / 2;
			moveX++;
			wstring xMoves = format(moveX);
			View::printVerticalCenteredCharactors(
				xMoves,
				{ x,y,short(x + (width - 4) / 3 + 2),short(y + ((height / 2 - 2) / 2)) },
				short(((height / 2 - 2) / 2) / 2),
				View::Color::BLACK,
				View::Color::WHITE
			);
		}
		else {
			x = spot.X + (((width - 4) / 3) * 2 + 3);
			y = spot.Y + (height / 2 - 2) / 2;
			moveY++;
			wstring yMoves = format(moveY);
			View::printVerticalCenteredCharactors(
				yMoves,
				{ x,y,short(x + (width - 4) / 3 + 2),short(y + ((height / 2 - 2) / 2)) },
				short(((height / 2 - 2) / 2) / 2),
				View::Color::BLACK,
				View::Color::WHITE
			);
		}
		/*x = spot.X + (width - 4) / 3 + 1;
		y = spot.Y + (height / 2 - 2) / 2;
		View::clock(x, y, int((width - 4) / 3 + 3), int((height / 2 - 2) / 2));*/
	}

	x = spot.X;
	y = spot.Y + (height / 2 - 2) / 2;

	/*int moveX = 0;
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
