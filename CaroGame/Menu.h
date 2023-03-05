#pragma once
#include <iostream>
#include <conio.h>
#include <wchar.h>
#include <Windows.h>

namespace Menu {
	struct MenuItem {
		int index;
		std::wstring content;
	};
	
	int MainMenuScreen(COORD start);
	void menuOptionChanged(MenuItem menu_items[], COORD start, int text_color, int selected_text_color, int* cur_index, int menu_size);
	void drawMenu(MenuItem menu_items[], COORD start, int textcolor, int selected_textcolor, int cur_index, int menu_size);
	void menuItem(int x, int y, int textcolor, char content[][257], char content2[][257], int* index, int num);
	void changeMenuItemColor(int x, int y, int t_color, char content[][257], char content2[][257], int index, int num);
	bool checkIndex(int* index, int num);
	int aboutMenu(int x, int y, int textcolor);
	int playWithComputerMenu(int x, int y, int textcolor);
	int newGameMenu(int x, int y, int textcolor);
	int MenuScreen(int x, int y, int textcolor);
}


