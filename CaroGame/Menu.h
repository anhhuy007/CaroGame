#pragma once
#include "View.h"
#include "Sound.h"
#include <conio.h>
#include <iostream>

void menuItem(int x, int y, int textcolor, char content[][257], char content2[][257], int* index, int num);
void changeMenuItemColor(int x, int y, int t_color, char content[][257], char content2[][257], int index, int num);
bool checkIndex(int* index, int num);
int aboutMenu(int x, int y, int textcolor);
int playWithComputerMenu(int x, int y, int textcolor);
int newGameMenu(int x, int y, int textcolor);
int MenuScreen(int x, int y, int textcolor);

