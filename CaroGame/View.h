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

const int _SIZE = 15;
const int LEFT = 1;
const int RIGHT = LEFT + 4 * _SIZE;
const int TOP = 1;
const int BOT = TOP + 2 * _SIZE;

namespace View {
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
	void drawInfoBorder(int x, int y);
	void fixConsoleWindow();
	void textColor(int color);
	void textStyle();	
	void clearRectangleArea(COORD start, int width, int height);
	void drawOtherDetail();
	void xWinScreen();
	void yWinScreen();
	void drawScreen();
	void printCharactors(std::wstring content, COORD spot, Color text_color, Color background_color);
}


