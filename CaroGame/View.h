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

const int _SIZE = 15;
const int LEFT = 1;
const int RIGHT = LEFT + 4 * _SIZE;
const int TOP = 1;
const int BOT = TOP + 2 * _SIZE;


void gotoXY(int x, int y);
void drawBoard();
void drawInfoBorder(int x, int y);
void fixConsoleWindow();
void textColor(int color);
void textStyle();
void testFunction();
void clearRectangleArea(COORD start, int width, int height);
void changeMenuItemColor(int x, int y, int t_color, char content[][257], char content2[][257], int index, int num);
void drawOtherDetail();
void xWinScreen();
void yWinScreen();
void drawScreen();