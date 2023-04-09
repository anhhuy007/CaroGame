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

	// init console window function
	void gotoXY(short x, short y);
	void fixConsoleWindow();
	void textColor(int color);	
	void textStyle(int fontSize);
	
	// print text 
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
	void printCenteredToast(
		std::wstring content, 
		SMALL_RECT box, 
		Color text_color, 
		Color background_color
	);
	
	void confirmDialog(
		std::wstring content,
		COORD spot,
		std::function<void()> positiveAction,
		std::function<void()> negativeAction
	);

	void pressAnyKey(SMALL_RECT box);
	
	// funcional functions
	void clearRectangleArea(COORD start, int width, int height);
	void writeScreenBuffer(PCHAR_INFO buffer);
	PCHAR_INFO getScreenBuffer();
	int GetRandom(int min, int max);
	COORD getCenteredSpot(std::wstring content, SMALL_RECT box);

	// display game information
	void displayTimer();
	void drawGamePlayInfoBox(COORD spot, int width, int height, Color color);
	void drawMove(short x, short y, int player);

	// draw game board and game pieces
	void drawGameBoard();
	void drawF1F2list(int x, int y);
	void drawCaroGameText(int delayTime);
	void drawInstructionText();
	void drawLoadGameText();
	void drawSettingText();
	void DisplayGame(int board[BOARD_SIZE][BOARD_SIZE], COORD cell[BOARD_SIZE][BOARD_SIZE], std::wstring name1, std::wstring name2);
	void drawXO(int board[BOARD_SIZE][BOARD_SIZE], COORD cell[BOARD_SIZE][BOARD_SIZE]);
	void drawAboutText();
	void splashScreenInfo();
	void splashScreen();

	// draw border
	void drawRectangleBorder(COORD spot, int width, int height, Color color);
	void drawBorder2(int left, int right, int top, int bot);
	void drawBorder3(int left, int right, int top, int bot, std::wstring winnerName);
	void LoadGameBorder(int left, int right, int top, int bot);
	void drawBox(COORD spot, int width, int height, Color color);
	void drawBoxLoad(COORD spot, int width, int height, Color color);
	
	// draw animated image 
	void drawIronmanAvatar(int x, int y);
	void drawBotAvatar(int x, int y);
	void drawSpidermanAvatar(int x, int y);
	void drawThanosAvatar(int x, int y);
	void drawBackGroundAvatar(int n, int left, int right, int top, int bot);
	void drawPacman();
	void drawXOart(COORD spot, bool isFirstPlayerTurn);
	void drawTurnBoard();
	void drawTrophy();
	void drawVSText();
	
	//win screen
	void drawWinner(int winplayer, std::wstring player1_name, std::wstring player2_name);
	void drawWinDrawBanner(bool win ,int x, int y);
	void showWinningMoves(int player, std::vector<COORD> winning_moves);
	void drawFireWork(int x, int y, int k);
	void drawFireWorkList(int k);
	void drawFireWork2(int k,int color, int x, int y);
	void drawFireWorkList2(int k);
	void displayGameResult(int player, std::vector<COORD> winning_moves, std::wstring name1, std::wstring name2);
}
