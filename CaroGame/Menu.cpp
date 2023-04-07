﻿#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "Menu.h"
#include "Sound.h"
#include "InputHandle.h"
#include <vector>
#include <string.h>
#include "FileIO.h"
using namespace std;

// global variable 
Sound::SoundManager soundManager;
bool menuEscPressed = false;
bool escEnable = false;

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
	std::vector<MenuItem> menu_items,
	COORD start
) {
	for (int i = 0; i < menu_items.size(); i++) {
		short y = start.Y + (i * 2);
		wstring selected_content = L">> " + menu_items[i].content + L" <<";
		short x = start.X - selected_content.length() / 2;
		for (short i = 0; i < selected_content.length(); i++) {
			View::printCharactors(L" ", { short(x + i), y }, View::Color::WHITE, View::Color::WHITE);
		}
	}
}

std::vector<MenuItem> getMenuItems(std::vector<MenuItem> menu_items, int indx, int displaymenu_size) {
	std::vector<MenuItem> display_menu_items;
	if (indx >= displaymenu_size) {
		for (int i = indx - displaymenu_size + 1; i <= indx; i++) {
			display_menu_items.push_back(menu_items[i]);
		}
	}
	else {
		for (int i = 0; i < displaymenu_size; i++) {
			display_menu_items.push_back(menu_items[i]);
		}
	}

	return display_menu_items;
}

// draw menu 
void drawMenu(
	std::vector<MenuItem> menu_items,
	COORD start,
	View::Color textcolor,
	View::Color selected_textcolor,
	int* cur_index,
	int displaymenu_size
) {
	menuEscPressed = false;
	std::vector<MenuItem> display_items = getMenuItems(menu_items, *cur_index, displaymenu_size);

	for (int i = 0; i < displaymenu_size; i++) {
		short y = start.Y + (i * 2);
		if (i == *cur_index || (*cur_index >= displaymenu_size && i == displaymenu_size - 1)) {
			wstring selected_content = L">> " + display_items[i].content + L" <<";
			short x = start.X - selected_content.length() / 2;
			View::printCharactors(selected_content, { x, y }, selected_textcolor, View::Color::WHITE);
		}
		else {
			short x = start.X - display_items[i].content.length() / 2;
			View::printCharactors(display_items[i].content, { x, y }, textcolor, View::Color::WHITE);
		}
	}
}

// listen on keyboard input and return the index of selected menu item
void menuOptionChanged(
	std::vector<MenuItem> menu_items,
	COORD start,
	View::Color text_color,
	View::Color selected_text_color,
	int* cur_index,
	int displaymenu_size
) {
	wstring key = InputHandle::Get();
	clearMenu(getMenuItems(menu_items, *cur_index, displaymenu_size), start);

	while (key != L"ENTER") {
		if (key == L"UP" || key == L"W" || key == L"w") {
			*cur_index -= 1;
			if (checkIndex(cur_index, menu_items.size())) {
				Sound::playEffectSound(Sound::INVALID, soundManager);
			}
			else {
				Sound::playEffectSound(Sound::VALID, soundManager);
			}
		}
		else if (key == L"DOWN" || key == L"S" || key == L"s") {
			*cur_index += 1;
			if (checkIndex(cur_index, menu_items.size())) {
				Sound::playEffectSound(Sound::INVALID, soundManager);
			}
			else {
				Sound::playEffectSound(Sound::VALID, soundManager);
			}
		}
		else if (key == L"ESC" && escEnable) {
			menuEscPressed = true;
			break;
		}
		drawMenu(menu_items, start, text_color, selected_text_color, cur_index, displaymenu_size);
		key = InputHandle::Get();
		clearMenu(getMenuItems(menu_items, *cur_index, displaymenu_size), start);
	}
}

// draw main menu screen
MenuOption mainMenu(
	COORD start,
	View::Color text_color,
	View::Color selected_textcolor
) {
	int index = 0;
	int menu_size = 6;
	std::vector<MenuItem> main_menu_items = {
		{ 0, L"NEW GAME", MenuOption::NEW_GAME },
		{ 1, L"LOAD GAME", MenuOption::LOAD_GAME },
		{ 2, L"SETTING", MenuOption::SETTING },
		{ 3, L"INSTRUCTION", MenuOption::INSTRUCTION},
		{ 4, L"ABOUT", MenuOption::ABOUT },
		{ 5, L"QUIT", MenuOption::QUIT }
	};

	drawMenu(main_menu_items, start, text_color, selected_textcolor, &index, menu_size);
	menuOptionChanged(main_menu_items, start, text_color, selected_textcolor, &index, menu_size);
	clearMenu(main_menu_items, start);

	return main_menu_items[index].menu_option;
}

MenuOption newGameMenu(
	COORD start,
	View::Color text_color,
	View::Color selected_textcolor
) {
	int index = 0;
	int menu_size = 4;
	start = { 70, 15 };
	std::vector<MenuItem> newgame_menu_items = {
		{0, L"VS HUMAN", MenuOption::NEW_GAME_VS_PLAYER },
		{1, L"VS COMPUTER (EASY)", MenuOption::NEW_GAME_VS_COMPUTER_EASY },
		{2, L"VS COMPUTER (HARD)", MenuOption::NEW_GAME_VS_COMPUTER_HARD },
		{3, L"BACK", MenuOption::BACK},
	};

	drawMenu(newgame_menu_items, start, text_color, selected_textcolor, &index, menu_size);
	menuOptionChanged(newgame_menu_items, start, text_color, selected_textcolor, &index, menu_size);
	clearMenu(newgame_menu_items, start);

	return newgame_menu_items[index].menu_option;
}

MenuOption MenuScreen() {
	Setting soundSetting = FileIO::readSetting("GameSetting.dat");
	soundManager = { soundSetting.backgroundSound, soundSetting.soundEffect, soundManager.backgroundPlaying };
	Sound::playBackgroundSound(soundManager);
	View::gotoXY(0, 0);
	MenuOption option = mainMenu({ 70, 15 }, View::Color::BLACK, View::Color::PURPLE);

	switch (option) {
	case MenuOption::NEW_GAME:
		return newGameMenu({ 70, 15 }, View::Color::BLACK, View::Color::PURPLE);
	}
	return option;
}

MenuOption aboutMenu() {
	COORD start = { 70, 10 };
	system("cls");
	wstring key;
	wstring about_content[12] = {
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

	for (int i = 0; i < 12; i++) {

		short x = start.X - about_content[i].length() / 2;
		short y = start.Y + i * 2;

		View::printCharactors(about_content[i], { x,y }, View::Color::BLACK, View::Color::WHITE);

	}

	View::drawAboutText();

	while (key != L"ESC") {
		key = InputHandle::Get();
		Sound::playEffectSound(Sound::INVALID, soundManager);
	}

	return MenuOption::ABOUT;
}

MenuOption instructionMenu() {
	COORD start = { 70, 10 };

	system("cls");
	wstring key;
	wstring instruction_content[12] = {
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

	View::drawInstructionText();

	for (int i = 0; i < 12; i++) {

		short x = start.X - instruction_content[i].length() / 2;
		short y = start.Y + i * 2;

		View::printCharactors(instruction_content[i], { x,y }, View::Color::BLACK, View::Color::WHITE);
	}


	while (key != L"ESC") {
		key = InputHandle::Get();
		Sound::playEffectSound(Sound::INVALID, soundManager);
	}
	return MenuOption::INSTRUCTION;
}

void drawSettingMenu(
	std::vector<SettingItem> setting_items,
	COORD start,
	View::Color textcolor,
	View::Color selected_textcolor,
	int* cur_index,
	int menu_size
) {
	View::drawSettingText();
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
	std::vector<SettingItem>& setting_items,
	COORD start,
	View::Color text_color,
	View::Color selected_textcolor,
	int* cur_index
) {
	wstring selected_item = InputHandle::Get();

	while (selected_item != L"ESC") {
		if (selected_item == L"UP" || selected_item == L"W" || selected_item == L"w") {
			*cur_index -= 1;
			if (checkIndex(cur_index, setting_items.size())) {
				Sound::playEffectSound(Sound::INVALID, soundManager);
			}
			else {
				Sound::playEffectSound(Sound::VALID, soundManager);
			}
		}
		else if (selected_item == L"DOWN" || selected_item == L"S" || selected_item == L"s") {
			*cur_index += 1;
			if (checkIndex(cur_index, setting_items.size())) {
				Sound::playEffectSound(Sound::INVALID, soundManager);
			}
			else {
				Sound::playEffectSound(Sound::VALID, soundManager);
			}
		}
		else if (selected_item == L"ENTER") {
			if (*cur_index == 2) {
				return;
			}

			setting_items[*cur_index].status = !setting_items[*cur_index].status;
			soundManager = { setting_items[0].status, setting_items[1].status };
			if (soundManager.backgroundSound == true) {
				soundManager.backgroundPlaying = true;
			}
			else {
				soundManager.backgroundPlaying = false;
			}
			Sound::playBackgroundSound(soundManager);
			Sound::playEffectSound(Sound::VALID, soundManager);
			View::gotoXY(0, 0);
			cout << "Sound: " << soundManager.backgroundSound << " " << soundManager.effectSound << " " << soundManager.backgroundPlaying;
		}
		View::clearRectangleArea({ 40,10 }, 50, 10);
		drawSettingMenu(setting_items, start, text_color, selected_textcolor, cur_index, setting_items.size());
		selected_item = InputHandle::Get();
	}
}

void settingMenu() {
	COORD start = { 70, 10 };
	int index = 0;
	std::vector<SettingItem> setting_items = {
		{ 0, L"BACKGROUND SOUND: ", soundManager.backgroundSound, L"ON", L"OFF"},
		{ 1, L"SOUND EFFECT: ", soundManager.effectSound, L"ON", L"OFF"},
		{ 2, L"BACK", false, L"", L""}
	};

	system("cls");
	drawSettingMenu(setting_items, start, View::Color::BLACK, View::Color::PURPLE, &index, setting_items.size());
	settingMenuOptionChanged(setting_items, start, View::Color::BLACK, View::Color::PURPLE, &index);

	Setting setting;
	setting.backgroundSound = setting_items[0].status;
	setting.soundEffect = setting_items[1].status;

	FileIO::saveSetting("GameSetting.dat", setting);
}

// formating string so that it can fill the whole line with the given width
std::wstring formatStringToWidth(std::vector<std::string> contents, std::vector<int> widths) {
	// fill the string with spaces
	for (int i = 0; i < contents.size(); i++) {
		contents[i] = contents[i].substr(0, widths[i]);
		while (contents[i].length() < widths[i]) {
			contents[i] += " ";
		}
	}

	// concat the whole string
	std::wstring result = L"";
	for (int i = 0; i < contents.size(); i++) {
		result += std::wstring(contents[i].begin(), contents[i].end());
	}

	return result;
}

std::string GetSavedGameTitle(std::vector<std::string> gameList, SMALL_RECT box) {
	// display saved games' table
	box.Bottom = box.Top + gameList.size() + 4;
	View::drawBoxLoad({ 25,12 }, 91, 20,View::Color::BLACK);
	View::printCharactors(L"╠", { 25,14 }, View::Color::BLACK, View::Color::BLACK);
	View::printCharactors(L"╣", { 116,14 }, View::Color::BLACK, View::Color::BLACK);
	for (short x = 26; x < 116; x++) {
		for (short y = 13; y < 14; y++) {
			View::printCharactors(L" ", { x,y }, View::Color::BLACK, View::Color::BLACK);
		}
	}
	View::printVerticalCenteredCharactors(L"NAME", { 25,12,55 ,14 }, 1, View::Color::WHITE, View::Color::BLACK);
	View::printVerticalCenteredCharactors(L"DATE", { 55,12,86,14 }, 1, View::Color::WHITE, View::Color::BLACK);
	View::printVerticalCenteredCharactors(L"TYPE", { 86,12,116,14 }, 1, View::Color::WHITE, View::Color::BLACK);
	
	std::vector<MenuItem> titles;

	for (int i = 0; i < gameList.size(); i++) {
		//gameList pattern: name@date@type
		std::string name = gameList[i].substr(0, gameList[i].find_first_of("@"));
		std::string date = gameList[i].substr(gameList[i].find_first_of("@") + 1, gameList[i].find_last_of("@") - gameList[i].find_first_of("@") - 1);
		std::string type = gameList[i].substr(gameList[i].find_last_of("@") + 1, gameList[i].length() - gameList[i].find_last_of("@") - 1);
		
		std::vector<std::string> contents = {
			name,
			date,
			type
		};

		std::wstring data = formatStringToWidth(contents, { 25, 30, 18 });
		titles.push_back({ i, data, MenuOption::NONE });
	}

	escEnable = true;
	int index = 0, menu_size = min(gameList.size(), 7);
	COORD spot = View::getCenteredSpot(L"", box);
	drawMenu(titles, { short(spot.X + 2), short(box.Top + 1) }, View::Color::BLACK, View::Color::PURPLE, &index, menu_size);
	menuOptionChanged(titles, { short(spot.X + 2), short(box.Top + 1) }, View::Color::BLACK, View::Color::PURPLE, &index, menu_size);
	escEnable = false;
	
	if (menuEscPressed) return "-1";
	return gameList[index].substr(0, gameList[index].find_first_of("@"));
}
