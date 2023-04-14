#pragma once
#include <iostream>
#include <conio.h>
#include <wchar.h>
#include <Windows.h>
#include "View.h"
#include "Model.h"

enum class MenuOption {
	NONE = -1,
	NEW_GAME_VS_HUMAN = 1,
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

// functional funtions for menu
void DrawMenu(
	std::vector<MenuItem> menu_items,
	COORD start,
	View::Color textcolor,
	View::Color selected_textcolor,
	int* cur_index,
	int menudisplay_size
);
void menuOptionChanged(
	std::vector<MenuItem> menu_items,
	COORD start,
	View::Color text_color,
	View::Color selected_textcolor,
	int* cur_index,
	int menudisplay_size
);
void settingMenuOptionChanged(
	std::vector<SettingItem>& setting_items,
	COORD start,
	View::Color text_color,
	View::Color selected_textcolor,
	int* cur_index
);
std::string GetSavedGameTitle(
	std::vector<std::string> gameList,
	SMALL_RECT box
);

bool checkIndex(
	int* index,
	int num
);

void clearMenu(
	std::vector<MenuItem> menu_items,
	COORD start
);

// contain all others menu 
MenuOption MenuScreen();
// input 3 parameters: menu's position, normal text color and selected text color
MenuOption MainMenu(
	COORD start,
	View::Color text_color,
	View::Color selected_textcolor
);
MenuOption NewGameMenu(
	COORD start,
	View::Color text_color,
	View::Color selected_textcolor
);
MenuOption AboutMenu();
MenuOption InstructionMenu();
void SettingMenu();





