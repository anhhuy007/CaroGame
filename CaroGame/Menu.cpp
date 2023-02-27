#include "Menu.h"

using namespace std;

void changeMenuItemColor(int x, int y, int t_color, char content[][257], char content2[][257], int index, int num) {
	//clearRectangleArea({ 50, 10 }, 50, 50);
	system("cls");
	//int tmp = x - int(strlen(content2[0])) / 2;
	for (int i = 0; i < num; i++) {
		if (i == index) {
			gotoXY(x - int(strlen(content2[i])) / 2, y + (i * 2));
			cout << content2[i];
			textColor(15);
			continue;
		}
		gotoXY(x - int(strlen(content[i])) / 2, y + (i * 2));
		cout << content[i];
	}
	system("color f0");
}

bool checkIndex(int* index, int num) {
	num -= 1;
	if (*index < 0) {
		*index = 0;
		return 1;
		//Error sound 
	}
	if (*index > num) {
		*index = num;
		return 1;
		//Error sound
	}
	return 0;
}

void menuItem(int x, int y, int textcolor, char content[][257], char content2[][257], int* index, int num) {
	LPCWSTR right = L"D:\\Caro\\Right.wav";
	LPCWSTR error = L"D:\\Caro\\Error.wav";
	LPCWSTR background = L"D:\\Caro\\Cipher2.wav";
	playSoundTrack(background);
	for (int i = 0; i < num; i++) {
		gotoXY(x - int(strlen(content[i])) / 2, y + (i * 2));
		cout << content[i];
	}
	while (true) {
		char c = _getch();
		if (c == 'w' || c == 'W') {
			(*index)--;
			if (checkIndex(index, num)) {
				playSoundTrack(error);
				continue;
			}
			playSoundTrack(right);
			changeMenuItemColor(x, y, textcolor, content, content2, *index, num);
		}
		if (c == 13) {
			break;
		}
		if (c == -32) {
			c = _getch();
			if (c == 72) {
				(*index)--;
				if (checkIndex(index, num)) {
					playSoundTrack(error);
					continue;
				}
				playSoundTrack(right);
				changeMenuItemColor(x, y, textcolor, content, content2, *index, num);
			}
			if (c == 80) {
				(*index)++;
				if (checkIndex(index, num)) {
					playSoundTrack(error);
					continue;
				}
				playSoundTrack(right);
				changeMenuItemColor(x, y, textcolor, content, content2, *index, num);
			}
			if (c == 75) {
				playSoundTrack(error);
				continue;
			}
			if (c == 77) {
				playSoundTrack(error);
				continue;
			}
		}
		else {
			playSoundTrack(error);
			continue;
		}
	}
}

int aboutMenu(int x, int y, int textcolor) {
	int index = -1;
	int number_element = 4;
	char about_content[4][257] = { "HUONG DAN","LUAT CHOI","NHOM VA GIAO VIEN HUONG DAN","THONG TIN LIEN HE" };
	char about_content2[4][257] = { ">> HUONG DAN <<",">> LUAT CHOI <<",">> NHOM VA GIAO VIEN HUONG DAN <<",">> THONG TIN LIEN HE <<" };
	menuItem(x, y, textcolor, about_content, about_content2, &index, number_element);
	system("cls");
	switch (index) {
	case 0:
		//Hướng dẫn
	case 1:
		//Luật chơi
	case 2:
		//Nhom va giao vien huong dan
	case 3:
		//Thong tin lien he
		break;
	}

	return 4;
}

int playWithComputerMenu(int x, int y, int textcolor) {
	int index = -1;
	int number_element = 2;
	char vscom_content[2][257] = { "EASY","HARD" };
	char vscom_content2[2][257] = { ">> EASY <<",">> HARD <<" };
	menuItem(x, y, textcolor, vscom_content, vscom_content2, &index, number_element);
	switch (index) {
	case 0:
		//Easy
		return 2;

	case 1:
		//Hard
		return 3;
	}
	return 1;
}

int newGameMenu(int x, int y, int textcolor) {
	int index = -1;
	int number_element = 2;
	char newgame_content[2][257] = { "VS HUMAN","VS COMPUTER" };
	char newgame_content2[2][257] = { ">> VS HUMAN <<", ">> VS COMPUTER <<" };
	menuItem(x, y, textcolor, newgame_content, newgame_content2, &index, number_element);
	system("cls");
	switch (index) {
	case 0:
		//VS human
		return 1;

	case 1:
		//VS computer
		return playWithComputerMenu(x, y, textcolor);
	}

	return 0;
}

int MenuScreen(int x, int y, int textcolor) {
	system("color f0");
	fixConsoleWindow();
	textStyle();

	int index = -1;
	char menu_content[5][257] = { "CONTINUE", "NEW GAME", "SETTING", "ABOUT", "QUIT" };
	char menu_content2[5][257] = { ">> CONTINUE <<",">> NEW GAME <<",">>  SETTING <<",">>   ABOUT  <<",">>   QUIT   <<" };
	int number_element = 5;
	menuItem(x, y, textcolor, menu_content, menu_content2, &index, number_element);
	system("cls");
	switch (index) {
	case 0:
		//Continue 
		gotoXY(0, 0);
		cout << "Continue";
		return 0;
	case 1:
		//New game
		gotoXY(0, 0);
		cout << "New Game";
		return newGameMenu(x, y, textcolor);
	case 2:
		// Setting
	case 3:
		//About
		return aboutMenu(x, y, textcolor);
	case 4:
		//Quit
		return 6;
	}

	return 0;
}
