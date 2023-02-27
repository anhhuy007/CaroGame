#pragma once
#include "View.h"
#include "Sound.h"
#include <conio.h>
#include <iostream>

void menuItem(int x, int y, int textcolor, char content[][257], char content2[][257], int* index, int num);
void changeMenuItemColor(int x, int y, int t_color, char content[][257], char content2[][257], int index, int num);
bool checkIndex(int* index, int num);
void aboutMenu(int x, int y, int textcolor);
void playWithComputerMenu(int x, int y, int textcolor);
void newGameMenu(int x, int y, int textcolor);
void showMenu(int x, int y, int textcolor);

