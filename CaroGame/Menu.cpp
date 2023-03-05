#include "Menu.h"
#include "Sound.h"
#include "InputHandle.h"
#include <string.h>
using namespace std;

// check if current menu index is valid index
bool Menu::checkIndex(int* index, int num) {
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

// draw menu 
void Menu::drawMenu(
	MenuItem menu_items[], 
	COORD start, 
	View::Color textcolor, 
	View::Color selected_textcolor, 
	int* cur_index, 
	int menu_size) {
	View::clearRectangleArea({ 50, 10 }, 50, 50);
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
void Menu::menuOptionChanged(
	Menu::MenuItem menu_items[], 
	COORD start, 
	View::Color text_color, 
	View::Color selected_text_color, 
	int* cur_index, 
	int menu_size
) {
	wstring selected_item = InputHandle::Get();

	while (selected_item != L"ENTER") {
		if (selected_item == L"UP") {
			*cur_index -= 1;
			if (Menu::checkIndex(cur_index, menu_size)) {
				Sound::playSound(Sound::error);
			}
			else {
				Sound::playSound(Sound::right);
			}
		}
		else if (selected_item == L"DOWN") {
			*cur_index += 1;
			if (Menu::checkIndex(cur_index, menu_size)) {
				Sound::playSound(Sound::error);
			}
			else {
				Sound::playSound(Sound::right);
			}
		}
		
		Menu::drawMenu(menu_items, start, text_color, selected_text_color, cur_index, menu_size);
		selected_item = InputHandle::Get();
	}
}

// draw main menu screen
int Menu::MainMenuScreen(
	COORD start, 
	View::Color text_color, 
	View::Color selected_textcolor
) {
	int index = -1;
	int menu_size = 6;
	start = { 65, 10 };
	Menu::MenuItem main_menu_items[6] = {
		{0, L"CONTINUE"},
		{1, L"NEW GAME"},
		{2, L"LOAD GAME"},
		{3, L"SETTING"},
		{4, L"ABOUT"},
		{5, L"QUIT"}
	};

	Menu::drawMenu(main_menu_items, start, text_color, selected_textcolor, &index, menu_size);
	Menu::menuOptionChanged(main_menu_items, start, text_color, selected_textcolor, &index, menu_size);

	return index;
}

int Menu::MenuScreen() {
	Sound::playSound(L"D:\\Caro\\Cipher2.wav");
	int index = -1;
	Menu::MainMenuScreen({ 65, 10 }, View::Color::BLACK, View::Color::PURPLE);

	// Return menu options selected
	switch (index) {
	case 0:
		//Continue game
		return 0;
	case 1:
		//New game
		//return newGameMenu(x, y, textcolor);
	case 2:
		// Setting
	case 3:
		//About
		//return aboutMenu(x, y, textcolor);
	case 4:
		//Quit
		return 6;
	}

	return 0;
}
