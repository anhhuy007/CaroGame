#pragma once
#include <iostream>
#include <conio.h>
#include <wchar.h>
#include <Windows.h>
#include "View.h"

namespace Menu {
	struct MenuItem {
		int index;
		std::wstring content;
	};
	
	// input 3 parameters: menu's position, normal text color and selected text color
	int MainMenuScreen(
		COORD start,
		View::Color text_color,
		View::Color selected_textcolor
	);
	void menuOptionChanged(
		MenuItem menu_items[], 
		COORD start, 
		View::Color text_color, 
		View::Color selected_textcolor, 
		int* cur_index, 
		int menu_size
	);
	void drawMenu(
		MenuItem menu_items[], 
		COORD start, 
		View::Color textcolor, 
		View::Color selected_textcolor, 
		int* cur_index, 
		int menu_size
	);
	int MenuScreen();
	bool checkIndex(int* index, int num);
}


