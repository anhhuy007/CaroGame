#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <conio.h>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <wchar.h>
#include <functional>

namespace View {
	const int _SIZE = 15;
	const int LEFT = 1;
	const int RIGHT = LEFT + 4 * _SIZE;
	const int TOP = 1;
	const int BOT = TOP + 2 * _SIZE;
	const int SCREEN_WIDTH = 135;
	const int SCREEN_HEIGHT = 35;
	
	enum class Color {
		BLACK = 0,
		BLUE = 1,
		GREEN = 2,
		CYAN = 3,
		RED = 4,
		PURPLE = 5,
		BROWN = 6,
		LIGHT_GRAY = 7,
		DARK_GRAY = 8,
		LIGHT_BLUE = 9,
		LIGHT_GREEN = 10,
		LIGHT_CYAN = 11,
		LIGHT_RED = 12,
		LIGHT_PURPLE = 13,
		YELLOW = 14,
		WHITE = 15
	};

	void gotoXY(int x, int y);
	void drawBoard();
	void drawRectangleBorder(COORD spot, int width, int height, Color color);
	void fixConsoleWindow();
	void textColor(int color);
	void textStyle();	
	void clearRectangleArea(COORD start, int width, int height);
	void drawOtherDetail();
	void xWinScreen();
	void yWinScreen();
	void drawScreen();
	void printCharactors(
		std::wstring content, 
		COORD spot, 
		Color text_color, 
		Color background_color
	);
	void printVerticalCenteredCharactors(
		std::wstring content, 
		SMALL_RECT box,
		short y_offset,
		Color text_color, 
		Color background_color
	);
	PCHAR_INFO getScreenBuffer();
	void writeScreenBuffer(PCHAR_INFO buffer);
	void confirmDialog(
		std::wstring content,
		COORD spot,
		std::function<void()> positiveAction,
		std::function<void()> negativeAction
	);
	
	void showWinningMoves(int player, std::vector<COORD> winning_moves);
	std::ostream& bold_on(std::ostream& os);

	std::ostream& bold_off(std::ostream& os);


	void splashScreenInfo();
	void splashScreen();
	void drawPacman();
	int GetRandom(int min, int max);
	void drawBorder2(int left, int right, int top, int bot);

	void drawCaroGameText();

	void drawTurnBoard();
	void drawTrophy();
	void drawBorder3(int left, int right, int top, int bot);

	void drawIronmanAvatar();
	void drawBotAvatar();
	void drawBoard2(int space_row, int space_col);
	void drawVSText();
	void drawSpidermanAvatar();
	void drawThanosAvatar();
	
	void drawBackGroundAvatar(int n,int left, int right, int top , int bot);

}

	
