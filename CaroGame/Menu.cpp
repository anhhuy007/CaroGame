#include "Menu.h"
#include "Sound.h"
#include "InputHandle.h"
#include "Control.h"
#include <vector>
#include <string.h>
using namespace std;
//using namespace Menu;

// check if current menu index is valid index
bool checkIndex(int* index, int num) {
	num -= 1;
	if (*index < 0) {
		*index = 0;
		return 1;
	}
	if (*index > num) {
		*index = num;
		return 1;
	}
	return 0;
}

void clearMenu(
	MenuItem menu_items[],
	COORD start,
	int menu_size
) {
	for (int i = 0; i < menu_size; i++) {
		short y = start.Y + (i * 2);
		wstring selected_content = L">> " + menu_items[i].content + L" <<";
		short x = start.X - selected_content.length() / 2;
		for (short i = 0; i < selected_content.length(); i++) {
			View::printCharactors(L" ", { short(x + i), y }, View::Color::WHITE, View::Color::WHITE);
		}
	}
}

// draw menu 
void drawMenu(
	MenuItem menu_items[], 
	COORD start, 
	View::Color textcolor, 
	View::Color selected_textcolor, 
	int* cur_index, 
	int menu_size) {
	//clearMenu(menu_items, start, menu_size);
	for (int i = 0; i < menu_size; i++) {
		short y = start.Y + (i * 2);
		if (i == *cur_index) {
			wstring selected_content = L">> " + menu_items[i].content + L" <<";
			short x = start.X - selected_content.length() / 2;
			View::printCharactors(selected_content, {x, y}, selected_textcolor, View::Color::WHITE);
		}
		else {
			short x = start.X - menu_items[i].content.length() / 2;
			View::printCharactors(menu_items[i].content, { x, y }, textcolor, View::Color::WHITE);
		}
	}
}

// listen on keyboard input and return the index of selected menu item
void menuOptionChanged(
	MenuItem menu_items[], 
	COORD start, 
	View::Color text_color, 
	View::Color selected_text_color, 
	int* cur_index, 
	int menu_size
) {
	wstring selected_item = InputHandle::Get();

	while (selected_item != L"ENTER") {
		if (selected_item == L"UP" || selected_item == L"W" || selected_item == L"w") {
			*cur_index -= 1;
			if (checkIndex(cur_index, menu_size)) {
				Sound::playSound(Sound::error);
			}
			else {
				Sound::playSound(Sound::right);
			}
		}
		else if (selected_item == L"DOWN" || selected_item == L"S" || selected_item == L"s") {
			*cur_index += 1;
			if (checkIndex(cur_index, menu_size)) {
				Sound::playSound(Sound::error);
			}
			else {
				Sound::playSound(Sound::right);
			}
		}
		/*else if (selected_item == L"ESC") {
			Control::returnMenu();
		}*/
		clearMenu(menu_items, start, menu_size);
		drawMenu(menu_items, start, text_color, selected_text_color, cur_index, menu_size);
		selected_item = InputHandle::Get();
	}
}

// draw main menu screen
MenuOption mainMenu(
	COORD start, 
	View::Color text_color, 
	View::Color selected_textcolor
) {	
	int index = -1;
	int menu_size = 7;
	MenuItem main_menu_items[7] = {
		{ 0, L"CONTINUE", MenuOption::CONTINUE },
		{ 1, L"NEW GAME", MenuOption::NEW_GAME },
		{ 2, L"LOAD GAME", MenuOption::LOAD_GAME },
		{ 3, L"SETTING", MenuOption::SETTING },
		{ 4, L"INSTRUCTION", MenuOption::INSTRUCTION},
		{ 5, L"ABOUT", MenuOption::ABOUT },
		{ 6, L"QUIT", MenuOption::QUIT }
	};

	drawMenu(main_menu_items, start, text_color, selected_textcolor, &index, menu_size);
	menuOptionChanged(main_menu_items, start, text_color, selected_textcolor, &index, menu_size);
	clearMenu(main_menu_items, start, menu_size);

	return main_menu_items[index].menu_option;
}

MenuOption newGameMenu(
	COORD start,
	View::Color text_color,
	View::Color selected_textcolor
) {	
	int index = -1;
	int menu_size = 4;
	start = { 65, 15 };
	MenuItem newgame_menu_items[4] = {
		{0, L"VS HUMAN", MenuOption::NEW_GAME_VS_PLAYER },
		{1, L"VS COMPUTER (EASY)", MenuOption::NEW_GAME_VS_COMPUTER_EASY },
		{2, L"VS COMPUTER (HARD)", MenuOption::NEW_GAME_VS_COMPUTER_HARD },
		{3, L"BACK", MenuOption::BACK},
	};

	drawMenu(newgame_menu_items, start, text_color, selected_textcolor, &index, menu_size);
	menuOptionChanged(newgame_menu_items, start, text_color, selected_textcolor, &index, menu_size);
	clearMenu(newgame_menu_items, start, menu_size);

	return newgame_menu_items[index].menu_option;
}

MenuOption MenuScreen() {
	Sound::playSound(L"D:\\Caro\\Cipher2.wav");
	MenuOption option = mainMenu({ 65, 15 }, View::Color::BLACK, View::Color::PURPLE);
	
	switch (option) {
	case MenuOption::NEW_GAME:
		return newGameMenu({ 65, 15 }, View::Color::BLACK, View::Color::PURPLE);
	}
	return option;
}


MenuOption aboutMenu(
	COORD start,
	View::Color text_color,
	View::Color selected_textcolor
) {
	wstring key;
	wstring about_content[14] = {
		L"ABOUT",
		L"",
		L"DESIGNED BY TEAM 10 - HCMUS",
		L"22127086 - Nguyễn Lâm Anh Duy",
		L"22127149 - Huỳnh Anh Huy",
		L"22127348 - Phan Nguyễn Hoàng Quân",
		L"2217284 - Lê Hải Nam",
		L"",
		L"INSTRUCTOR - Trương Toàn Thịnh",
		L"",
		L"RELEASED DATE: 2023",
		L"VERSION: CARO 1.0.0",
		L"",
		L"PRESS ESC TO BACK"
	};
	View::clearRectangleArea({ 50, 15 }, 50, 50);
	
	for (int i = 0; i < 14; i++) {
		
		short x = start.X - about_content[i].length() / 2;
		short y = start.Y + i * 2;

		View::printCharactors(about_content[i], { x,y }, text_color, selected_textcolor);
		
	}

	while (key != L"ESC") {
		key = InputHandle::Get();
		Sound::playSound(Sound::error);
	}

	return MenuOption::ABOUT;
 }

MenuOption instructionMenu(
	COORD start,
	View::Color text_color,
	View::Color selected_textcolor
) {
	wstring key;
	wstring instruction_content[14] = {
		L"INSTRUCTION",
		L"",
		L"Controls",
		L"Press 'W' or '↑' to move UP",
		L"Press 'S' or '↓' to move DOWN",
		L"Press 'A' or '←' to move LEFT",
		L"Press 'D' or '→' to move RIGHT",
		L"",
		L"Rules",
		L"1. The game is played on a board of 15x15 squares.",
		L"2. One player is assigned 'X' and the other 'O'. Players take turns placing their marks in empty squares.",
		L"3. The player who succeeds in placing five of their marks in a horizontal, vertical, or diagonal row wins the game.",
		L"",
		L"PRESS ESC TO BACK"
	};
	View::clearRectangleArea({ 50, 15 }, 50, 50);

	for (int i = 0; i < 14; i++) {

		short x = start.X - instruction_content[i].length() / 2;
		short y = start.Y + i * 2;

		View::printCharactors(instruction_content[i], { x,y }, text_color, selected_textcolor);
	}

	while (key != L"ESC") {
		key = InputHandle::Get();
		Sound::playSound(Sound::error);
	}
	return MenuOption::INSTRUCTION;
}

void drawSettingMenu(
	SettingItem setting_items[],
	COORD start,
	View::Color textcolor,
	View::Color selected_textcolor,
	int* cur_index,
	int menu_size
) {
	//clearMenu(menu_items, start, menu_size);
	for (int i = 0; i < menu_size; i++) {
		short y = start.Y + (i * 2);
		wstring content = setting_items[i].content;
		if (setting_items[i].status == true) {
			content += setting_items[i].status_true;
		}
		else {
			content += setting_items[i].status_false;
		}
		
		if (i == *cur_index) {
			wstring selected_content = L">> " + content + L" <<";
			short x = start.X - selected_content.length() / 2;
			View::printCharactors(selected_content, { x, y }, selected_textcolor, View::Color::WHITE);
		}
		else {
			short x = start.X - content.length() / 2;
			View::printCharactors(content, { x, y }, textcolor, View::Color::WHITE);
		}
	}
}

void settingMenuOptionChanged(
	SettingItem setting_items[],
	COORD start,
	View::Color text_color,
	View::Color selected_textcolor,
	int* cur_index,
	int menu_size
) {
	wstring selected_item = InputHandle::Get();

	while (selected_item != L"ESC") {
		if (selected_item == L"UP" || selected_item == L"W" || selected_item == L"w") {
			*cur_index -= 1;
			if (checkIndex(cur_index, menu_size)) {
				Sound::playSound(Sound::error);
			}
			else {
				Sound::playSound(Sound::right);
			}
		}
		else if (selected_item == L"DOWN" || selected_item == L"S" || selected_item == L"s") {
			*cur_index += 1;
			if (checkIndex(cur_index, menu_size)) {
				Sound::playSound(Sound::error);
			}
			else {
				Sound::playSound(Sound::right);
			}
		}
		else if (selected_item == L"ENTER") {
			if (*cur_index == 2) {
				return;
			}

			setting_items[*cur_index].status = !setting_items[*cur_index].status;
			Sound::playSound(Sound::right);
		}
		system("cls");
		drawSettingMenu(setting_items, start, text_color, selected_textcolor, cur_index, menu_size);
		selected_item = InputHandle::Get();
	}
}

void settingMenu(
	COORD start,
	View::Color text_color,
	View::Color selected_textcolor
) {
	int index = -1;
	int menu_size = 3;
	bool background = 1;
	bool effect = 1;
	SettingItem setting_items[3] = {
		{ 0, L"BACKGROUND SOUND: ", background, L"ON", L"OFF"},
		{ 1, L"SOUND EFFECT: ", effect, L"ON", L"OFF"}, 
		{ 2, L"BACK", false, L"", L""}
	};

	drawSettingMenu(setting_items, start, text_color, selected_textcolor, &index, menu_size);
	settingMenuOptionChanged(setting_items, start, text_color, selected_textcolor, &index, menu_size);
}