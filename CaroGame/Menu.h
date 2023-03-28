#pragma once
#include <iostream>
#include <conio.h>
#include <wchar.h>
#include <Windows.h>
#include "View.h"

	enum class MenuOption {
		NONE = -1,
		NEW_GAME_VS_PLAYER = 1,
		NEW_GAME_VS_COMPUTER_EASY = 2,
		NEW_GAME_VS_COMPUTER_HARD = 3,
		LOAD_GAME = 4,
		SETTING = 5,
		ABOUT = 6,
		QUIT = 7,	
		BACK = 8,
		NEW_GAME = 9,
		INSTRUCTION = 10,
		YES = 11,
		NO = 12,
	};

	struct MenuItem {
		int index;
		std::wstring content;
		MenuOption menu_option;
	};

	struct SettingItem {
		int indx;
		std::wstring content;
		bool status;
		std::wstring status_true;
		std::wstring status_false;
	};
	
	// input 3 parameters: menu's position, normal text color and selected text color
	MenuOption mainMenu(
		COORD start,
		View::Color text_color,
		View::Color selected_textcolor
	);
	MenuOption newGameMenu(
		COORD start,
		View::Color text_color,
		View::Color selected_textcolor
	);
	MenuOption aboutMenu(
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
	MenuOption MenuScreen();
	bool checkIndex(
		int* index, 
		int num
	);

	MenuOption aboutMenu(
		COORD start,
		View::Color text_color,
		View::Color selected_textcolor
	);

	MenuOption instructionMenu(
		COORD start,
		View::Color text_color,
		View::Color selected_textcolor
	);

	void clearMenu(
		MenuItem menu_items[],
		COORD start,
		int menu_size
	);

	void settingMenu(
		COORD start,
		View::Color text_color,
		View::Color selected_textcolor
	);
	void settingMenuOptionChanged(
		SettingItem setting_items[],
		COORD start,
		View::Color text_color,
		View::Color selected_textcolor,
		int* cur_index,
		int menu_size
	);
