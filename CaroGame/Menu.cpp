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
	start = { 65, 10 };
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
	start = { 65, 10 };
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
	MenuOption option = mainMenu({ 65, 10 }, View::Color::BLACK, View::Color::PURPLE);
	
	switch (option) {
	case MenuOption::NEW_GAME:
		return newGameMenu({ 65, 10 }, View::Color::BLACK, View::Color::PURPLE);
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
		L">> ABOUT <<",
		L"",
		L"DESIGNED BY TEAM 10 HCMUS",
		L"22127086 - NGUYỄN LÂM ANH DUY",
		L"22127149 - HUỲNH ANH HUY",
		L"22127348 - PHAN NGUYỄN HOÀNG QUÂN",
		L"2217284 - LÊ HẢI NAM",
		L"",
		L"GIÁO VIÊN HƯỚNG DẪN - TRƯƠNG TOÀN THỊNH",
		L"",
		L"RELEASED DATE: 2023",
		L"VERSION: CARO 1.0.0",
		L"",
		L"PRESS ESC TO BACK"
	};
	int i = 0;
	View::clearRectangleArea({ 50, 10 }, 50, 50);
	
	for (int i = 0; i < 14; i++) {
		
		short x = start.X - about_content[i].length() / 2;
		short y = start.Y + i * 2;

		View::printCharactors(about_content[i], { x,y }, text_color, selected_textcolor);
		
	}

	while (key != L"ESC") {
		key = InputHandle::Get();
	}

	return MenuOption::ABOUT;
 }

MenuOption instructionMenu(
	COORD start,
	View::Color text_color,
	View::Color selected_textcolor
) {
	wstring key;
	wstring instruction_content[7] = { L"THÔNG TIN LIÊN HỆ",L"22127086 - NGUYỄN LÂM ANH DUY",L"22127149 - HUỲNH ANH HUY",L"22127348 - PHAN NGUYỄN HOÀNG QUÂN",L"2217284 - LÊ HẢI NAM",L"GIÁO VIÊN HƯỚNG DẪN - TRƯƠNG TOÀN THỊNH",L"PRESS ESC TO BACK" };
	int i = 0;
	View::clearRectangleArea({ 50, 10 }, 50, 50);

	for (int i = 0; i < 7; i++) {

		short x = start.X - instruction_content[i].length() / 2;
		short y = start.Y + i * 2;

		View::printCharactors(instruction_content[i], { x,y }, text_color, selected_textcolor);
	}

	while (key != L"ESC") {
		key = InputHandle::Get();
	}
	return MenuOption::INSTRUCTION;
}