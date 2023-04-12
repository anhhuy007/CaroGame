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

	enum class Avatar {
		CROCODILE = 1,
		MARIO = 2,
		JAKE = 3,
		FINN = 4,
		BMO = 5,
		DOGE = 6,
		BOT = 7, 
		AMONGUS = 8,
		SPIDERMAN = 9, 
		IRONMAN = 10
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
		Color background_color,
		short maxLength = -1
	);
	
	// 
	void printVerticalCenteredCharactors(
		std::wstring content, 
		SMALL_RECT box,
		short y_offset,
		Color text_color, 
		Color background_color,
		short maxLength = -1
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

	
	// funcional functions
	void clearRectangleArea(COORD start, int width, int height);
	void writeScreenBuffer(PCHAR_INFO buffer);
	PCHAR_INFO getScreenBuffer();
	int GetRandom(int min, int max);
	COORD getCenteredSpot(std::wstring content, SMALL_RECT box);
	void pressAnyKey(SMALL_RECT box); // press any key to continue


	// display game information
	void drawGamePlayInfoBox(COORD spot, int width, int height, Color color);

	// draw game board and game pieces
	void drawGameBoard();
	void drawF1F2list(int x, int y);
	void drawCaroGameText(int delayTime);
	void drawInstructionText();
	void drawLoadGameText();
	void drawSettingText();
	// draw all game pieces
	void DisplayGame(
		int board[BOARD_SIZE][BOARD_SIZE], 
		COORD cell[BOARD_SIZE][BOARD_SIZE], 
		std::wstring name1, 
		Avatar avatar1, 
		std::wstring name2, 
		Avatar avatar2
	);
	// display all X and O on board
	void drawXO(
		int board[BOARD_SIZE][BOARD_SIZE], 
		COORD cell[BOARD_SIZE][BOARD_SIZE]
	);
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
	void drawBackGroundAvatar(int n, int left, int right, int top, int bot);
	void drawXOart(COORD spot, bool isFirstPlayerTurn);
	void drawTurnBoard();
	void drawTrophy();
	void drawVSText();
	
	//draw avatar
	void DrawAvatar(Avatar avatar, int x, int y);
	void DrawDogeAvatar(int x, int y);
	void DrawIronmanAvatar(int x, int y);
	void DrawBotAvatar(int x, int y);
	void DrawSpidermanAvatar(int x, int y);
	void DrawFinnAvatar(int x, int y);
	void DrawBMOAvatar(int x, int y);
	void DrawMarioAvatar(int x, int y);
	void DrawAmongUsAvatar(int x, int y);
	void DrawJakeAvatar(int x, int y);
	void DrawCrocodileAvatar(int x, int y);
	void DrawPacman();
	
	//win screen
	void drawWinner(
		int winplayer, 
		std::wstring player1_name, 
		Avatar avatar1, 
		std::wstring player2_name, 
		Avatar avatar2
	);
	void drawWinDrawBanner(
		bool win ,
		int x, 
		int y
	);
	void showWinningMoves(
		int player, 
		std::vector<COORD> winning_moves
	);
	void drawFireWork(
		int k,
		int color, 
		int x, 
		int y
	);
	void drawFireWorkList(int k);
	void displayGameResult(
		int player,
		std::vector<COORD> winning_moves,
		std::wstring name1,
		Avatar avatar1,
		std::wstring name2,
		Avatar avatar2
	);
}
