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
#include <vector>

namespace View {
	const int BOARD_SIZE = 15;
	const int LEFT = 4;
	const int RIGHT = LEFT + 4 * BOARD_SIZE;
	const int TOP = 2;
	const int BOT = TOP + 2 * BOARD_SIZE;
	const int SCREEN_WIDTH = 146;
	const int SCREEN_HEIGHT = 37;
	const SMALL_RECT WINDOW_SIZE = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };
	
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

	void gotoXY(short x, short y);

	void LoadGameBorder(int left, int right, int top, int bot);
	void drawBoard(int space_row, int space_col);
	
	void drawF1F2list(int x, int y);
	void fixConsoleWindow();
	void textColor(int color);	
	void textStyle(int fontSize);	
	void clearRectangleArea(COORD start, int width, int height);
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
	void drawCaroGameText(int delayTime);
	void splashScreenInfo();
	void splashScreen();
	void drawPacman();
	int GetRandom(int min, int max);
	COORD getCenteredSpot(std::wstring content, SMALL_RECT box);
	void printCenteredToast(std::wstring content, SMALL_RECT box, Color text_color, Color background_color);
	void clock(short x, short y, int width, int height);
	void drawBox(COORD spot, int width, int height, Color color);
	void drawGamePlayInfoBox(COORD spot, int width, int height, Color color);
	void drawTurnBoard();
	void drawTrophy();
	void drawVSText();
	void drawXOart(COORD spot,bool isFirstPlayerTurn);
	void drawSavedGameTable(std::vector<std::string> gameList, SMALL_RECT box);

	// draw border
	void drawRectangleBorder(COORD spot, int width, int height, Color color);
	void drawBorder2(int left, int right, int top, int bot);
	void drawBorder3(int left, int right, int top, int bot);

	// draw avatar
	void drawIronmanAvatar(int x, int y);
	void drawBotAvatar(int x, int y);
	void drawSpidermanAvatar(int x, int y);
	void drawThanosAvatar(int x, int y);
	void drawBackGroundAvatar(int n, int left, int right, int top, int bot);

	//win screen
	void drawWinner(int winplayer,bool playervsplayer);
	void drawWinDrawBanner(bool win ,int x, int y);
}
