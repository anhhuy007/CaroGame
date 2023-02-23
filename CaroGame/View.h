const int _SIZE = 20;
const int LEFT = 1;
#include <conio.h>
#include <Windows.h>
const int RIGHT = LEFT + 4 * _SIZE;
const int TOP = 1;
const int BOT = TOP + 2 * _SIZE;

void gotoXY(int x, int y);
void drawBoard();
void fixConsoleWindow();
void textColor(int color);
void textStyle();
void testFunction();
void clearRectangleArea(COORD start, int width, int height);