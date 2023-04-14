#include "View.h"
#include "Menu.h"
#include "Control.h"
#include "Sound.h"
#include "InputHandle.h"

void View::DisplayGame(
	int board[sz][sz], 
	COORD cell[sz][sz], 
	std::string gameName, 
	std::wstring name1, 
	Avatar avatar1, 
	std::wstring name2, 
	Avatar avatar2
) {
	View::drawTitleAndStatus(gameName, Control::gameSaved);
	View::drawGameBoard();
	View::drawXO(board, cell);
	View::drawGamePlayInfoBox({ 75,13 }, 64, 15, View::Color::BLACK);
	View::drawBorder3(75, 75 + 20, 0, 0 + 10, name1);
	View::drawBorder3(119, 119 + 20, 0, 0 + 10, name2);
	View::DrawAvatar(avatar1, 69, -2);
	View::DrawAvatar(avatar2, 113, -2);
	View::drawVSText();
	View::drawBorder2(80, 80 + 55, 31, 30 + 4);
	View::drawF1F2list(88, 32);
}

void View::drawXO(int board[sz][sz], COORD cell[sz][sz]) {
	for (int i = 0; i < View::BOARD_SIZE; i++) {
		for (int j = 0; j < View::BOARD_SIZE; j++) {
			if (board[i][j] == 0) continue;
			COORD spot = cell[i][j];

			if (board[i][j] == 1) View::printCharactors(
					L"X",
					{ spot.X , spot.Y },
					View::Color::RED,
					View::Color::WHITE
				);
			else View::printCharactors(
				L"O",
				{ spot.X , spot.Y },
				View::Color::BLUE,
				View::Color::WHITE
			);
		}
	}
}

void View::drawAboutText() {
	int x, y;
	x = 49;
	y = 2;

	
	View::printCharactors(L"░█████╗░██████╗░░█████╗░██╗░░░██╗████████╗",{short(x),short(y + 0)},Color::BLACK,Color::WHITE);
	View::printCharactors(L"██╔══██╗██╔══██╗██╔══██╗██║░░░██║╚══██╔══╝",{short(x),short(y + 1)},Color::BLACK,Color::WHITE);
	View::printCharactors(L"███████║██████╦╝██║░░██║██║░░░██║░░░██║░░░",{short(x),short(y + 2)},Color::BLACK,Color::WHITE);
	View::printCharactors(L"██╔══██║██╔══██╗██║░░██║██║░░░██║░░░██║░░░",{short(x),short(y + 3)},Color::BLACK,Color::WHITE);
	View::printCharactors(L"██║░░██║██████╦╝╚█████╔╝╚██████╔╝░░░██║░░░",{short(x),short(y + 4)},Color::BLACK,Color::WHITE);
	View::printCharactors(L"╚═╝░░╚═╝╚═════╝░░╚════╝░░╚═════╝░░░░╚═╝░░░",{short(x),short(y + 5)},Color::BLACK,Color::WHITE);
}
void View::drawSettingText() {
	int x, y;
	x = 46;
	y = 2;

	
	View::printCharactors(L"░██████╗███████╗████████╗████████╗██╗███╗░░██╗░██████╗░",{short(x),short(y)},Color::BLACK,Color::WHITE);
	View::printCharactors(L"██╔════╝██╔════╝╚══██╔══╝╚══██╔══╝██║████╗░██║██╔════╝░",{short(x),short(y+1)},Color::BLACK,Color::WHITE);
	View::printCharactors(L"╚█████╗░█████╗░░░░░██║░░░░░░██║░░░██║██╔██╗██║██║░░██╗░",{short(x),short(y+2)},Color::BLACK,Color::WHITE);
	View::printCharactors(L"░╚═══██╗██╔══╝░░░░░██║░░░░░░██║░░░██║██║╚████║██║░░╚██╗",{short(x),short(y+3)},Color::BLACK,Color::WHITE);
	View::printCharactors(L"██████╔╝███████╗░░░██║░░░░░░██║░░░██║██║░╚███║╚██████╔╝",{short(x),short(y+4)},Color::BLACK,Color::WHITE);
	View::printCharactors(L"╚═════╝░╚══════╝░░░╚═╝░░░░░░╚═╝░░░╚═╝╚═╝░░╚══╝░╚═════╝░",{short(x),short(y+5)},Color::BLACK,Color::WHITE);

}
void View::drawTitleAndStatus(std::string name, bool isSaved) {
	View::clearRectangleArea({ 0, 0 }, 65, 3);
	View::drawBorder2(4, 40, 1, 3);
	View::drawBorder2(41, 64, 1, 3);
	View::printCharactors(L"Name:", { 6, 2 }, Color::WHITE, Color::BLACK);
	View::printCharactors(L"Status:", { 43, 2 }, Color::WHITE, Color::BLACK);


	if (isSaved) {
		View::printCharactors(L" Saved!", { 53, 2 }, Color::WHITE, Color::GREEN);
	}
	else {
		View::printCharactors(L"Not saved!", { 52, 2 }, Color::WHITE, Color::RED);
	}

	std::wstring gameName = std::wstring(name.begin(), name.end());
	if (gameName == L"") gameName = L"Untitled";
	
	View::printCharactors(gameName, { 12, 2 }, Color::LIGHT_PURPLE, Color::WHITE);
}
void View::drawLoadGameText() {
	int x, y;
	x = 37;
	y = 2;
	
	View::printCharactors(L"██╗░░░░░░█████╗░░█████╗░██████╗░  ░██████╗░░█████╗░███╗░░░███╗███████╗",{short(x),short(y)},Color::BLACK,Color::WHITE);
	View::printCharactors(L"██║░░░░░██╔══██╗██╔══██╗██╔══██╗  ██╔════╝░██╔══██╗████╗░████║██╔════╝",{short(x),short(y+1)},Color::BLACK,Color::WHITE);
	View::printCharactors(L"██║░░░░░██║░░██║███████║██║░░██║  ██║░░██╗░███████║██╔████╔██║█████╗░░",{short(x),short(y+2)},Color::BLACK,Color::WHITE);
	View::printCharactors(L"██║░░░░░██║░░██║██╔══██║██║░░██║  ██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░",{short(x),short(y+3)},Color::BLACK,Color::WHITE);
	View::printCharactors(L"███████╗╚█████╔╝██║░░██║██████╔╝  ╚██████╔╝██║░░██║██║░╚═╝░██║███████╗",{short(x),short(y+4)},Color::BLACK,Color::WHITE);
	View::printCharactors(L"╚══════╝░╚════╝░╚═╝░░╚═╝╚═════╝░  ░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝",{short(x),short(y+5)},Color::BLACK,Color::WHITE);
}
void View::drawInstructionText() {
	int x, y;
	x = 33;
	y = 2;
	
	View::printCharactors(L"██╗███╗░░██╗░██████╗████████╗██████╗░██╗░░░██╗░█████╗░████████╗██╗░█████╗░███╗░░██╗",{short(x),short(y)},Color::BLACK,Color::WHITE);
	View::printCharactors(L"██║████╗░██║██╔════╝╚══██╔══╝██╔══██╗██║░░░██║██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║",{short(x),short(y+1)},Color::BLACK,Color::WHITE);
	View::printCharactors(L"██║██╔██╗██║╚█████╗░░░░██║░░░██████╔╝██║░░░██║██║░░╚═╝░░░██║░░░██║██║░░██║██╔██╗██║",{short(x),short(y+2)},Color::BLACK,Color::WHITE);
	View::printCharactors(L"██║██║╚████║░╚═══██╗░░░██║░░░██╔══██╗██║░░░██║██║░░██╗░░░██║░░░██║██║░░██║██║╚████║",{short(x),short(y+3)},Color::BLACK,Color::WHITE);
	View::printCharactors(L"██║██║░╚███║██████╔╝░░░██║░░░██║░░██║╚██████╔╝╚█████╔╝░░░██║░░░██║╚█████╔╝██║░╚███║",{short(x),short(y+4)},Color::BLACK,Color::WHITE);
	View::printCharactors(L"╚═╝╚═╝░░╚══╝╚═════╝░░░░╚═╝░░░╚═╝░░╚═╝░╚═════╝░░╚════╝░░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝",{short(x),short(y+5)},Color::BLACK,Color::WHITE);
	
}
void View::drawFireWork(int k,int color, int x, int y) {

	switch (k)
	{
	case 0:
		View::printCharactors(L"▌", {short(x),short(y + 10) }, Color(color), Color::WHITE);
		break;
	case 1:
		View::printCharactors(L" ", { short(x),short(y + 10) }, Color(color), Color::WHITE);
		View::printCharactors(L"▌", { short(x),short(y + 9) }, Color(color), Color::WHITE);
		break;
	case 2:
		View::printCharactors(L" ", { short(x),short(y + 9) }, Color(color), Color::WHITE);
		View::printCharactors(L"▌", { short(x),short(y + 8) }, Color(color), Color::WHITE);
		break;
	case 3:
		View::printCharactors(L" ", { short(x),short(y + 8) }, Color(color), Color::WHITE);
		View::printCharactors(L"▌", { short(x),short(y + 7) }, Color(color), Color::WHITE);
		break;
	case 4:
		View::printCharactors(L" ", { short(x),short(y + 7) }, Color(color), Color::WHITE);
		View::printCharactors(L"▌", { short(x),short(y + 6) }, Color(color), Color::WHITE);
		break;
	case 5:
		View::printCharactors(L" ", { short(x),short(y + 6) }, Color(color), Color::WHITE);
		View::printCharactors(L"▌", { short(x),short(y + 5) }, Color(color), Color::WHITE);
		break;
	case 6:
		View::printCharactors(L" ", { short(x),short(y + 5) }, Color(color), Color::WHITE);
		break;
	case 7:

		View::printCharactors(L"             ", { short(x - 6),short(y + 6) }, Color(color), Color::WHITE);
		View::printCharactors(L"             ", { short(x-6),short(y + 5) }, Color(color), Color::WHITE);
		View::printCharactors(L"             ", { short(x-6),short(y + 4) }, Color(color), Color::WHITE);
		View::printCharactors(L"      ♪      ", { short(x-6),short(y + 3) }, Color(color), Color::WHITE);
		View::printCharactors(L"             ", { short(x-6),short(y + 2) }, Color(color), Color::WHITE);
		View::printCharactors(L"             ", { short(x-6),short(y + 1) }, Color(color), Color::WHITE);
		View::printCharactors(L"             ", { short(x-6),short(y + 0) }, Color(color), Color::WHITE);
		break;
	case 8:
		View::printCharactors(L"             ", { short(x - 6),short(y + 6) }, Color(color), Color::WHITE);
		View::printCharactors(L"             ", { short(x - 6),short(y + 5) }, Color(color), Color::WHITE);
		View::printCharactors(L"      ♪      ", { short(x - 6),short(y + 4) }, Color(color), Color::WHITE);
		View::printCharactors(L"    ♪ ♪ ♪    ", { short(x - 6),short(y + 3) }, Color(color), Color::WHITE);
		View::printCharactors(L"      ♪      ", { short(x - 6),short(y + 2) }, Color(color), Color::WHITE);
		View::printCharactors(L"             ", { short(x - 6),short(y + 1) }, Color(color), Color::WHITE);
		View::printCharactors(L"             ", { short(x - 6),short(y + 0) }, Color(color), Color::WHITE);
		break;
	case 9:
		View::printCharactors(L"      ♪      ", { short(x - 6),short(y + 6) }, Color(color), Color::WHITE);
		View::printCharactors(L"  ♪       ♪  ", { short(x - 6),short(y + 5) }, Color(color), Color::WHITE);
		View::printCharactors(L"      ♪      ",{ short(x - 6),short(y + 4) }, Color(color), Color::WHITE);
		View::printCharactors(L"♪   ♪   ♪   ♪", { short(x - 6),short(y + 3) }, Color(color), Color::WHITE);
		View::printCharactors(L"      ♪      ", { short(x - 6),short(y + 2) }, Color(color), Color::WHITE);
		View::printCharactors(L"  ♪       ♪  ", { short(x - 6),short(y + 1) }, Color(color), Color::WHITE);
		View::printCharactors(L"      ♪      ", { short(x - 6),short(y + 0) }, Color(color), Color::WHITE);

		break;
	case 10:
		View::printCharactors(L"      ♪      ", { short(x - 6),short(y + 6) }, Color(color), Color::WHITE);
		View::printCharactors(L"  ♪       ♪  ", { short(x - 6),short(y + 5) }, Color(color), Color::WHITE);
		View::printCharactors(L"      ♪      ", { short(x - 6),short(y + 4) }, Color(color), Color::WHITE);
		View::printCharactors(L"♪   ♪   ♪   ♪", { short(x - 6),short(y + 3) }, Color(color), Color::WHITE);
		View::printCharactors(L"      ♪      ", { short(x - 6),short(y + 2) }, Color(color), Color::WHITE);
		View::printCharactors(L"  ♪       ♪  ", { short(x - 6),short(y + 1) }, Color(color), Color::WHITE);
		View::printCharactors(L"      ♪      ", { short(x - 6),short(y + 0) }, Color(color), Color::WHITE);

		break;
	case 11:
		View::printCharactors(L"      ♪      ", { short(x - 6),short(y + 6) }, Color(color), Color::WHITE);
		View::printCharactors(L"  ♪       ♪  ", { short(x - 6),short(y + 5) }, Color(color), Color::WHITE);
		View::printCharactors(L"             ", { short(x - 6),short(y + 4) }, Color(color), Color::WHITE);
		View::printCharactors(L"♪           ♪", { short(x - 6),short(y + 3) }, Color(color), Color::WHITE);
		View::printCharactors(L"             ", { short(x - 6),short(y + 2) }, Color(color), Color::WHITE);
		View::printCharactors(L"  ♪       ♪  ", { short(x - 6),short(y + 1) }, Color(color), Color::WHITE);
		View::printCharactors(L"      ♪      ", { short(x - 6),short(y + 0) }, Color(color), Color::WHITE);
		break;
	case 12:
		View::printCharactors(L"               ", { short(x - 6),short(y + 6) }, Color(color), Color::WHITE);
		View::printCharactors(L"               ", { short(x - 6),short(y + 5) }, Color(color), Color::WHITE);
		View::printCharactors(L"               ", { short(x - 6),short(y + 4) }, Color(color), Color::WHITE);
		View::printCharactors(L"               ", { short(x - 6),short(y + 3) }, Color(color), Color::WHITE);
		View::printCharactors(L"               ", { short(x - 6),short(y + 2) }, Color(color), Color::WHITE);
		View::printCharactors(L"               ", { short(x - 6),short(y + 1) }, Color(color), Color::WHITE);
		View::printCharactors(L"               ", { short(x - 6),short(y + 0) }, Color(color), Color::WHITE);
		break;

	default:
		break;
	}
}
//k =1 : win, k = 0: draw
void View::drawFireWorkList(int k) {
	int x, y;
	int p1 = 0, p2 = 0, p3 = 0;
	int count = 0;

	std::vector<int>color = { 10,11,12,13,14 };
	std::wstring key = L"";
	if (k == 1) {
		while (key != L"ESC") {
			if (count >= 0) {
				x = 74, y = 8;
				drawFireWork(p1 % 13, color[rand() % 5], x, y);

				x = 125, y = 7;
				drawFireWork(p1 % 13, color[rand() % 5], x, y);
				x = 80, y = 0;
				drawFireWork(p1 % 15, color[rand() % 5], x, y);
				p1++;
			}
			if (count >= 8) {
				x = 84, y = 5;
				drawFireWork(p2 % 13, color[rand() % 5], x, y);
				x = 135, y = 4;
				drawFireWork(p2 % 13, color[rand() % 5], x, y);
				p2++;

			}
			if (count >= 16) {
				x = 108, y = 0;
				drawFireWork(7 + (p3 % 6), color[rand() % 5], x, y);
				p3++;
			}
			count++;
			if (count >= 60) break;
			View::gotoXY(90, 35);
			if (count % 10 == 0) std::cout << "***** Game end in " << 5 - (count / 10) + 1 << "s *****";
			Sleep(100);
		}
	}
	else if (k == 0) {
		while (key != L"ESC") {
			if (count >= 0) {
				x = 74, y = 0;
				drawFireWork(p1 % 13, color[rand() % 5], x, y);
				x = 132, y = 0;
				drawFireWork(p1 % 13, color[rand() % 5], x, y);
				p1++;
			}
			if (count >= 12) {
				x = 88, y = 0;
				drawFireWork(7 + (p2 % 6), color[rand() % 5], x, y);
				p2++;

			}
			if (count >= 16) {
				x = 115, y = 0;
				drawFireWork(7 + (p3 % 6), color[rand() % 5], x, y);
				p3++;
			}
			if (count >= 60) break;
			View::gotoXY(90, 35);
			if (count % 10 == 0) std::cout << "***** Game end in " << 5 - (count / 10) + 1 << "s *****";
			Sleep(100);
		}
	}
}

void View::displayGameResult(
	int player, 
	std::vector<COORD> winning_moves, 
	std::wstring name1, 
	Avatar avatar1,
	std::wstring name2,
	Avatar avatar2
) {
	std::wstring sound = L"";
	if (player == 1) {
		sound = Sound::WIN;
	}
	else if (player == 2) {
		sound = Sound::LOSE;
	}
	else {
		sound = Sound::WIN;
	}
	Sound::playSound(sound);
	
	View::showWinningMoves(player, winning_moves);
	View::clearRectangleArea({ 70, 0 }, 70, 40); 
	View::drawWinner(player, name1, avatar1, name2, avatar2);
	
	Sound::closeSound(sound);
}
//who win, 1 :player1, 2:player2 , 0 draw
void View::drawWinner(int winplayer, std::wstring player1_name, Avatar avatar1, std::wstring player2_name, Avatar avatar2) {
	int x, y;
	//avatar coordinate: x = 88, y = 5
	//banner coordinate: x = 75, y = 20
	
	if (winplayer == 1) {
		View::drawBorder3(94, 94 + 20, 7, 7 + 10, player1_name);
		View::DrawAvatar(avatar1, 88, 5);
		View::drawWinDrawBanner(1, 75, 20);
		View::drawFireWorkList(1);
	}
	else if (winplayer == 2) {
		View::drawBorder3(94, 94 + 20, 7, 7 + 10, player2_name);
		View::DrawAvatar(avatar2, 88, 5);
		View::drawWinDrawBanner(1, 75, 20);
		View::drawFireWorkList(1);
	}
	else {
		View::drawBorder3(94 - 15, 94 - 15 + 20, 7, 7 + 10, player1_name);
		View::DrawAvatar(avatar1, 88 - 15, 5);
		View::drawBorder3(94 + 15, 94 + 15 + 20, 7, 7 + 10, player2_name);
		View::DrawAvatar(avatar2, 88 + 15, 5);
		View::drawWinDrawBanner(0, 75, 20);
		View::drawFireWorkList(0);
	}
}
void View::drawWinDrawBanner(bool win,int x, int y) {
	//x = 75;
	//y = 20;
	int color;
	std::vector<int> a = { 2,3,4,5,9,11,14 };
	if (win == 1) {

		for (int i = 0; i <= 20; i++) {
			View::printCharactors(L"██████████████████████████████████████████████████████████", { char(x), char(y) }, Color::BLACK, Color::WHITE); color=rand()%7;
			View::printCharactors(L"█░░░░░░██████████░░░░░░█░░░░░░░░░░█░░░░░░██████████░░░░░░█", { char(x), char(y + 1) }, Color::BLACK, Color(a[color])); color=rand()%7;
			View::printCharactors(L"█░░▄▀░░██████████░░▄▀░░█░░▄▀▄▀▄▀░░█░░▄▀░░░░░░░░░░██░░▄▀░░█", { char(x), char(y + 2) }, Color::BLACK, Color(a[color])); color=rand()%7;

			View::printCharactors(L"█░░▄▀░░██████████░░▄▀░░█░░░░▄▀░░░░█░░▄▀▄▀▄▀▄▀▄▀░░██░░▄▀░░█", { char(x), char(y + 3) }, Color::BLACK, Color(a[color]));; color=rand()%7;
			View::printCharactors(L"█░░▄▀░░██████████░░▄▀░░███░░▄▀░░███░░▄▀░░░░░░▄▀░░██░░▄▀░░█", { char(x), char(y + 4) }, Color::BLACK, Color(a[color])); color=rand()%7; 
			View::printCharactors(L"█░░▄▀░░██░░░░░░██░░▄▀░░███░░▄▀░░███░░▄▀░░██░░▄▀░░██░░▄▀░░█", { char(x), char(y + 5) }, Color::BLACK, Color(a[color])); color=rand()%7;

			View::printCharactors(L"█░░▄▀░░██░░▄▀░░██░░▄▀░░███░░▄▀░░███░░▄▀░░██░░▄▀░░██░░▄▀░░█", { char(x), char(y + 6) }, Color::BLACK, Color(a[color]));; color=rand()%7;
			View::printCharactors(L"█░░▄▀░░██░░▄▀░░██░░▄▀░░███░░▄▀░░███░░▄▀░░██░░▄▀░░██░░▄▀░░█", { char(x), char(y + 7) }, Color::BLACK, Color(a[color])); color=rand()%7;
			View::printCharactors(L"█░░▄▀░░░░░░▄▀░░░░░░▄▀░░███░░▄▀░░███░░▄▀░░██░░▄▀░░░░░░▄▀░░█", { char(x), char(y + 8) }, Color::BLACK, Color(a[color])); color=rand()%7; 

			View::printCharactors(L"█░░▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀░░█░░░░▄▀░░░░█░░▄▀░░██░░▄▀▄▀▄▀▄▀▄▀░░█", { char(x), char(y + 9) }, Color::BLACK, Color(a[color])); color=rand()%7;
			View::printCharactors(L"█░░▄▀░░░░░░▄▀░░░░░░▄▀░░█░░▄▀▄▀▄▀░░█░░▄▀░░██░░░░░░░░░░▄▀░░█", { char(x), char(y + 10) }, Color::BLACK, Color(a[color])); color=rand()%7;	
			View::printCharactors(L"█░░░░░░██░░░░░░██░░░░░░█░░░░░░░░░░█░░░░░░██████████░░░░░░█", { char(x), char(y + 11) }, Color::BLACK, Color(a[color])); color=rand()%7;

			View::printCharactors(L"██████████████████████████████████████████████████████████", { char(x), char(y + 12) }, Color::BLACK, Color::WHITE);
			Sleep(10);
		}

	}
	else {

		x -= 6;
		
		for (int i = 0; i <= 20; i++) {
			View::printCharactors(L"█████████████████████████████████████████████████████████████████████████", { char(x),char(y + 0) }, Color::BLACK, Color::WHITE); color = rand() % 7;
			View::printCharactors(L"█░░░░░░░░░░░░███░░░░░░░░░░░░░░░░███░░░░░░░░░░░░░░█░░░░░░██████████░░░░░░█", { char(x),char(y + 1) }, Color::BLACK, Color(a[color]));	 color = rand() % 7;
			View::printCharactors(L"█░░▄▀▄▀▄▀▄▀░░░░█░░▄▀▄▀▄▀▄▀▄▀▄▀░░███░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀░░██████████░░▄▀░░█", { char(x),char(y + 2) }, Color::BLACK, Color(a[color]));	 color = rand() % 7;
			View::printCharactors(L"█░░▄▀░░░░▄▀▄▀░░█░░▄▀░░░░░░░░▄▀░░███░░▄▀░░░░░░▄▀░░█░░▄▀░░██████████░░▄▀░░█", { char(x),char(y + 3) }, Color::BLACK, Color(a[color]));	 color = rand() % 7;
			View::printCharactors(L"█░░▄▀░░██░░▄▀░░█░░▄▀░░████░░▄▀░░███░░▄▀░░██░░▄▀░░█░░▄▀░░██████████░░▄▀░░█", { char(x),char(y + 4) }, Color::BLACK, Color(a[color]));	 color = rand() % 7;
			View::printCharactors(L"█░░▄▀░░██░░▄▀░░█░░▄▀░░░░░░░░▄▀░░███░░▄▀░░░░░░▄▀░░█░░▄▀░░██░░░░░░██░░▄▀░░█", { char(x),char(y + 5) }, Color::BLACK, Color(a[color]));	 color = rand() % 7;
			View::printCharactors(L"█░░▄▀░░██░░▄▀░░█░░▄▀▄▀▄▀▄▀▄▀▄▀░░███░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀░░██░░▄▀░░██░░▄▀░░█", { char(x),char(y + 6) }, Color::BLACK, Color(a[color]));	 color = rand() % 7;
			View::printCharactors(L"█░░▄▀░░██░░▄▀░░█░░▄▀░░░░░░▄▀░░░░███░░▄▀░░░░░░▄▀░░█░░▄▀░░██░░▄▀░░██░░▄▀░░█", { char(x),char(y + 7) }, Color::BLACK, Color(a[color]));	 color = rand() % 7;
			View::printCharactors(L"█░░▄▀░░██░░▄▀░░█░░▄▀░░██░░▄▀░░█████░░▄▀░░██░░▄▀░░█░░▄▀░░░░░░▄▀░░░░░░▄▀░░█", { char(x),char(y + 8) }, Color::BLACK, Color(a[color]));	 color = rand() % 7;
			View::printCharactors(L"█░░▄▀░░░░▄▀▄▀░░█░░▄▀░░██░░▄▀░░░░░░█░░▄▀░░██░░▄▀░░█░░▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀░░█", { char(x),char(y + 9) }, Color::BLACK, Color(a[color]));	 color = rand() % 7;
			View::printCharactors(L"█░░▄▀▄▀▄▀▄▀░░░░█░░▄▀░░██░░▄▀▄▀▄▀░░█░░▄▀░░██░░▄▀░░█░░▄▀░░░░░░▄▀░░░░░░▄▀░░█", { char(x),char(y + 10) }, Color::BLACK, Color(a[color]));	 color = rand() % 7;
			View::printCharactors(L"█░░░░░░░░░░░░███░░░░░░██░░░░░░░░░░█░░░░░░██░░░░░░█░░░░░░██░░░░░░██░░░░░░█", { char(x),char(y + 11) }, Color::BLACK, Color(a[color]));	 color = rand() % 7;
			View::printCharactors(L"█████████████████████████████████████████████████████████████████████████", { char(x),char(y + 12) }, Color::BLACK, Color::WHITE);	 color = rand() % 7;
			Sleep(10);
		}

	}	
}
void View::LoadGameBorder(int left, int right, int top , int bot) {
	
	View::printCharactors(L"Load Games", { (short)(left - 5 + (right - left)/2),(short)(top+1) }, Color::BLACK, Color::WHITE);


	for (int i = left + 1; i <= right - 1; i++) {
		View::printCharactors(L"═", { (short)(i),(short)(top) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"═", { (short)(i),(short)(top + 2) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"═", { (short)(i),(short)(bot) }, Color::BLACK, Color::WHITE);
	}
	for (int i = top + 1; i <= bot - 1; i++) {
		View::printCharactors(L"║", { (short)(left),(short)(i) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"║", { (short)(right),(short)(i) }, Color::BLACK, Color::WHITE);
	}
	View::printCharactors(L"╗", { (short)(right),(short)(top) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"╝", { (short)(right),(short)(bot) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"╔", { (short)(left),(short)(top) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"╚", { (short)(left),(short)(bot) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"╣", { (short)(right),(short)(top + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"╠", { (short)(left),(short)(top + 2) }, Color::BLACK, Color::WHITE);

}
void View::drawGameBoard() {
	int x = View::LEFT, y = View::TOP;
	int space_row = View::BOARD_SIZE, space_col = View::BOARD_SIZE;
	
	//draw coordinate border
	View::printCharactors(L"a", { (short)(x + 2),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"b", { (short)(x + 6),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"c", { (short)(x + 10),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"d", { (short)(x + 14),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"e", { (short)(x + 18),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"f", { (short)(x + 22),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"g", { (short)(x + 26),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"h", { (short)(x + 30),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"i", { (short)(x + 34),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"j", { (short)(x + 38),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"k", { (short)(x + 42),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"l", { (short)(x + 46),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"m", { (short)(x + 50),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"n", { (short)(x + 54),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"o", { (short)(x + 58),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	//View::printCharactors(L"p", { (short)(x + 62),(short)(y + 2 * space_row - 1 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"15", { (short)(x - 3),(short)(y + 2 * space_row - 29) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"14", { (short)(x - 3),(short)(y + 2 * space_row - 27) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"13", { (short)(x - 3),(short)(y + 2 * space_row - 25) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"12", { (short)(x - 3),(short)(y + 2 * space_row - 23) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"11", { (short)(x - 3),(short)(y + 2 * space_row - 21) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"10", { (short)(x - 3 ),(short)(y + 2 * space_row - 19 ) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"9", { (short)(x - 2 ),(short)(y + 2 * space_row - 17 ) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"8", { (short)(x - 2 ),(short)(y + 2 * space_row - 15 ) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"7", { (short)(x - 2 ),(short)(y + 2 * space_row - 13 ) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"6", { (short)(x - 2 ),(short)(y + 2 * space_row - 11 ) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"5", { (short)(x - 2 ),(short)(y + 2 * space_row - 9 ) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"4", { (short)(x - 2 ),(short)(y + 2 * space_row - 7 ) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"3", { (short)(x - 2 ),(short)(y + 2 * space_row - 5 ) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"2", { (short)(x - 2 ),(short)(y + 2 * space_row - 3 ) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"1", { (short)(x - 2 ),(short)(y + 2 * space_row - 1 ) }, Color::BLACK, Color::WHITE);
	//col = 4*space_col -1
	//row = 2*space_row -1
	//inside
	int k = 1;
	while (1) {
		for (int i = 1; i <= 4 * space_col - 1; i++) {
			if (i % 4 == 0) View::printCharactors(L"║", { (short)(x + i),(short)(y + k) }, Color::BLACK, Color::WHITE);
		}
		k++;
		if (k > 2 * space_row - 1) break;

		for (int i = 1; i <= 4 * space_col - 1; i++) {
			if (i % 4 == 0) View::printCharactors(L"╬", { (short)(x  + i),(short)(y + k) }, Color::BLACK, Color::WHITE);
			else View::printCharactors(L"═", { (short)(x  + i),(short)(y + k) }, Color::BLACK, Color::WHITE);
		}
		k++;
	}

	//border
	for (int i = 1; i <= 4 * space_col - 1; i++) {			//top
		if (i % 4 == 0) View::printCharactors(L"╦", { (short)(x + i),(short)(y + 0) }, Color::BLACK, Color::WHITE);
		else View::printCharactors(L"═", { (short)(x + i),(short)(y + 0) }, Color::BLACK, Color::WHITE);
	}
	for (int i = 1; i <= 4 * space_col - 1; i++) {			//bot
		if (i % 4 == 0) View::printCharactors(L"╩", { (short)(x + i),(short)(y + 2*space_row -1 +1) }, Color::BLACK, Color::WHITE);
		else View::printCharactors(L"═", { (short)(x + i),(short)(y + 2 * space_row - 1 + 1) }, Color::BLACK, Color::WHITE);
	}
	for (int i = 1; i <= 2 * space_row - 1; i++) {			//left
		if (i % 2 == 0) View::printCharactors(L"╠", { (short)(x + 0),(short)(y + i) }, Color::BLACK, Color::WHITE);
		else View::printCharactors(L"║", { (short)(x + 0),(short)(y + i) }, Color::BLACK, Color::WHITE);
	}
	for (int i = 1; i <= 2 * space_row - 1; i++) {			//right
		if (i % 2 == 0) View::printCharactors(L"╣", { (short)(x + 4*space_col -1 +1),(short)(y + i) }, Color::BLACK, Color::WHITE);
		else View::printCharactors(L"║", { (short)(x + 4 * space_col - 1 + 1),(short)(y + i) }, Color::BLACK, Color::WHITE);
	}

	View::printCharactors(L"╔", { (short)(x + 0),(short)(y + 0) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"╗", { (short)(x + 4 * space_col - 1 + 1),(short)(y + 0) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"╚", { (short)(x + 0),(short)(y + 2 * space_row - 1 + 1) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"╝", { (short)(x + 4 * space_col - 1 + 1),(short)(y + 2 * space_row - 1 + 1) }, Color::BLACK, Color::WHITE);
}
void View::drawTurnBoard() {
	int x, y;		//x+10 , y+2
	x = 80;
	y = 9;

	View::printCharactors(L"\x2554", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);			//4 corners
	View::printCharactors(L"\x2557", { (short)(x + 10 + 16),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x255a", { (short)(x + 10 + 2),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x255d", { (short)(x + 10 + 16),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2551", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2551", { (short)(x + 10 + 16),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2551", { (short)(x + 10 + 2),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2551", { (short)(x + 10 + 16),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2551", { (short)(x + 10 + 2),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2551", { (short)(x + 10 + 16),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2560", { (short)(x + 10 + 2),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2563", { (short)(x + 10 + 16),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2560", { (short)(x + 10 + 2),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2563", { (short)(x + 10 + 16),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);

	for (int i = 3; i <= 15; i++) {
		View::printCharactors(L"\x2550", { (short)(x + 10 + i),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2550", { (short)(x + 10 + i),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2550", { (short)(x + 10 + i),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2550", { (short)(x + 10 + i),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	}

	View::printCharactors(L"\x2566", { (short)(x + 10 + 9),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2569", { (short)(x + 10 + 9),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2551", { (short)(x + 10 + 9),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);

	//content
	View::printCharactors(L"0:12", { (short)(x + 10 + 8),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"X Turn", { (short)(x + 10 + 7),(short)(y + 2 + 5) }, Color::RED, Color::WHITE);

	View::printCharactors(L"X:", { (short)(x + 10 + 4),(short)(y + 2 + 7) }, Color::RED, Color::WHITE);
	View::printCharactors(L"Y:", { (short)(x + 10 + 11),(short)(y + 2 + 7) }, Color::CYAN, Color::WHITE);

	View::printCharactors(L"11", { (short)(x + 10 + 6),(short)(y + 2 + 7) }, Color::RED, Color::WHITE);
	View::printCharactors(L"12", { (short)(x + 10 + 13),(short)(y + 2 + 7) }, Color::CYAN, Color::WHITE);
}
void View::drawRectangleBorder(COORD spot, int width, int height, Color color) {

	for (short i = spot.X; i < spot.X + width; i++) {
		for (short j = spot.Y; j < spot.Y + height; j++) {
			View::printCharactors(L" ", { i, j }, Color::BLACK, Color::WHITE);
		}
	}
	
	for (short i = spot.X; i < spot.X + width; i++) {
		View::printCharactors(L"=", { i, spot.Y}, color, Color::WHITE);
		View::printCharactors(L"=", { i, short(spot.Y + height - 1) }, color, Color::WHITE);
	}

	for (short i = spot.Y + 1; i < spot.Y + height - 1; i++) {
		View::printCharactors(L"||", { spot.X, i }, color, Color::WHITE);
		View::printCharactors(L"||", { short(spot.X + width - 2), i }, color, Color::WHITE);
	}
}
void View::drawBorder2(int left, int right, int top , int bot) {

	for (int i = left+1; i <= right-1; i++) {
		View::printCharactors(L"═", { (short)( i),(short)(top) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"═", { (short)( i),(short)(bot) }, Color::BLACK, Color::WHITE);
	}
	for (int i = top+1; i <= bot-1; i++) {
		View::printCharactors(L"║", { (short)(left),(short)(i) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"║", { (short)(right),(short)(i) }, Color::BLACK, Color::WHITE);
	}
	View::printCharactors(L"╗", { (short)(right),(short)(top) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"╝", { (short)(right),(short)(bot) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"╔", { (short)(left),(short)(top) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"╚", { (short)(left),(short)(bot) }, Color::BLACK, Color::WHITE);
}
void View::drawXOart(COORD spot,bool isFirstPlayerTurn) {
	int x = int(spot.X);
	int y = int(spot.Y);
	if(!isFirstPlayerTurn){
		View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 2) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 10),(short)(y + 2 + 2) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 10),(short)(y + 2 + 3) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 4) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 4) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 10),(short)(y + 2 + 4) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 5) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 5) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 10),(short)(y + 2 + 5) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 6) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 6) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 10),(short)(y + 2 + 6) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 2) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 3) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 4) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 5) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 6) }, Color::BLACK, Color::BLACK);

		View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2584", { (short)(x + 10 + 5),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2584", { (short)(x + 10 + 6),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2584", { (short)(x + 10 + 7),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2584", { (short)(x + 10 + 8),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2584", { (short)(x + 10 + 9),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);

		View::printCharactors(L"\x2584", { (short)(x + 10 + 5),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2584", { (short)(x + 10 + 6),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2584", { (short)(x + 10 + 7),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);

		View::printCharactors(L"\x2580", { (short)(x + 10 + 4),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 6),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 7),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 8),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 9),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);


		View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 6),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 7),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);

		View::printCharactors(L"\x2580", { (short)(x + 10 + 8),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2584", { (short)(x + 10 + 8),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);

		View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::LIGHT_CYAN, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::LIGHT_CYAN, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 4) }, Color::LIGHT_CYAN, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::LIGHT_CYAN, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 6) }, Color::LIGHT_CYAN, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 9),(short)(y + 2 + 3) }, Color::LIGHT_CYAN, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 9),(short)(y + 2 + 4) }, Color::LIGHT_CYAN, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 9),(short)(y + 2 + 5) }, Color::LIGHT_CYAN, Color::BLACK);

		View::printCharactors(L"\x2584", { (short)(x + 10 + 9),(short)(y + 2 + 2) }, Color::LIGHT_CYAN, Color::BLACK);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 9),(short)(y + 2 + 6) }, Color::LIGHT_CYAN, Color::BLACK);


		View::printCharactors(L"\x2584", { (short)(x + 10 + 3),(short)(y + 2 + 1) }, Color::LIGHT_CYAN, Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 3),(short)(y + 2 + 7) }, Color::LIGHT_CYAN, Color::WHITE);


		View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 2) }, Color::LIGHT_RED, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 3) }, Color::LIGHT_RED, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 4) }, Color::LIGHT_RED, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 5) }, Color::LIGHT_RED, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 6) }, Color::LIGHT_RED, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 3) }, Color::LIGHT_RED, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 4) }, Color::LIGHT_RED, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 5) }, Color::LIGHT_RED, Color::BLACK);

		View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 2) }, Color::LIGHT_RED, Color::BLACK);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 4),(short)(y + 2 + 6) }, Color::LIGHT_RED, Color::BLACK);

		View::printCharactors(L"\x2584", { (short)(x + 10 + 10),(short)(y + 2 + 1) }, Color::LIGHT_RED, Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 10),(short)(y + 2 + 7) }, Color::LIGHT_RED, Color::WHITE);
	}
	
	else {
		View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 4) }, Color::BLACK, Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 4) }, Color::BLACK, Color::BLACK);

		for (int i = 4; i <= 9; i++) {
			View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 3) }, Color::BLACK, Color::BLACK);
			View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 5) }, Color::BLACK, Color::BLACK);
		}

		for (int i = 2; i <= 11; i++) {
			if (i >= 5 && i <= 8) continue;
			View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 2) }, Color::BLACK, Color::BLACK);
			View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 6) }, Color::BLACK, Color::BLACK);

			View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
			View::printCharactors(L"\x2580", { (short)(x + 10 + i),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
		}

		View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::LIGHT_CYAN, Color::WHITE);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::LIGHT_CYAN, Color::WHITE);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 4) }, Color::LIGHT_CYAN, Color::WHITE);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 5) }, Color::LIGHT_CYAN, Color::WHITE);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 6) }, Color::LIGHT_CYAN, Color::WHITE);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 2) }, Color::LIGHT_CYAN, Color::WHITE);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 6) }, Color::LIGHT_CYAN, Color::WHITE);

		View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 2) }, Color::LIGHT_RED, Color::WHITE);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 10),(short)(y + 2 + 3) }, Color::LIGHT_RED, Color::WHITE);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 4) }, Color::LIGHT_RED, Color::WHITE);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 10),(short)(y + 2 + 5) }, Color::LIGHT_RED, Color::WHITE);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 6) }, Color::LIGHT_RED, Color::WHITE);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 2) }, Color::LIGHT_RED, Color::WHITE);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 6) }, Color::LIGHT_RED, Color::WHITE);


		View::printCharactors(L"\x2584", { (short)(x + 10 + 12),(short)(y + 2 + 1) }, Color::LIGHT_RED, Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 12),(short)(y + 2 + 7) }, Color::LIGHT_RED, Color::WHITE);
		View::printCharactors(L"\x2584", { (short)(x + 10 + 5),(short)(y + 2 + 1) }, Color::LIGHT_RED, Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 7) }, Color::LIGHT_RED, Color::WHITE);

		View::printCharactors(L"\x2584", { (short)(x + 10 + 1),(short)(y + 2 + 1) }, Color::LIGHT_CYAN, Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 7) }, Color::LIGHT_CYAN, Color::WHITE);
		View::printCharactors(L"\x2584", { (short)(x + 10 + 8),(short)(y + 2 + 1) }, Color::LIGHT_CYAN, Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 8),(short)(y + 2 + 7) }, Color::LIGHT_CYAN, Color::WHITE);
	}
}
void View::drawF1F2list(int x, int y) {
	//int x, y;
	//x = 80;
	//y = 23;

	//info board

	View::printCharactors(L"F1 : Return home", { (short)(x),(short)(y) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"F2 : Save game", { (short)(x + 25),(short)(y) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"F3 : Load game", { (short)(x),(short)(y + 1) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"F4 : Undo", { (short)(x + 25),(short)(y + 1 ) }, Color::BLACK, Color::WHITE);	
}

void View::DrawAvatar(View::Avatar avatar, int x, int y) {
	switch (avatar) {
	case View::Avatar::CROCODILE:
		View::DrawCrocodileAvatar(x, y);
		break;
	case View::Avatar::MARIO:
		View::DrawMarioAvatar(x, y);
		break;
	case View::Avatar::JAKE:
		View::DrawDuckAvatar(x, y);
		break;
	case View::Avatar::AMONGUS:
		View::DrawAmongUsAvatar(x, y);
		break;
	case View::Avatar::BMO:
		View::DrawBMOAvatar(x, y);
		break;
	case View::Avatar::FINN:
		View::DrawFinnAvatar(x, y);
		break;
	case View::Avatar::DOGE:
		View::DrawDogeAvatar(x, y);
		break;
	case View::Avatar::BOT:
		View::DrawBotAvatar(x, y);
		break;
	case View::Avatar::SPIDERMAN:
		View::DrawSpidermanAvatar(x, y);
		break;
	case View::Avatar::IRONMAN:
		View::DrawIronmanAvatar(x, y);
		break;
	}
}

void View::DrawCrocodileAvatar(int x, int y) {
	x += 1;
	View::printCharactors(L"▄", { (short)(x + 10 + 2),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 3),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 6),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 7),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"▄", { (short)(x + 10),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::GREEN, Color::BLACK);
	View::printCharactors(L"▀", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color::GREEN, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 3),(short)(y + 2 + 2) }, Color::GREEN, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 4),(short)(y + 2 + 2) }, Color::GREEN, Color::BLACK);
	View::printCharactors(L"▄", { (short)(x + 10 + 5),(short)(y + 2 + 2) }, Color::GREEN, Color::BLACK);
	View::printCharactors(L"▀", { (short)(x + 10 + 6),(short)(y + 2 + 2) }, Color::GREEN, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 7),(short)(y + 2 + 2) }, Color::GREEN, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 8),(short)(y + 2 + 2) }, Color::GREEN, Color::BLACK);
	View::printCharactors(L"▄", { (short)(x + 10 + 9),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"█", { (short)(x + 10),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 6),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 9),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"▄", { (short)(x + 10 - 2),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 - 1),(short)(y + 2 + 4) }, Color::GREEN, Color::BLACK);
	View::printCharactors(L"▄", { (short)(x + 10),(short)(y + 2 + 4) }, Color::GREEN, Color::BLACK);
	View::printCharactors(L"▄", { (short)(x + 10 + 1),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 2),(short)(y + 2 + 4) }, Color::GREEN, Color::BLACK);
	for (int i = 3; i <= 7; i++)
	{
		View::printCharactors(L"▄", { (short)(x + 10 + i),(short)(y + 2 + 4) }, Color::GREEN, Color::BLACK);
	}
	View::printCharactors(L"▄", { (short)(x + 10 + 8),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 9),(short)(y + 2 + 4) }, Color::GREEN, Color::BLACK);
	View::printCharactors(L"▄", { (short)(x + 10 + 10),(short)(y + 2 + 4) }, Color::GREEN, Color::BLACK);
	View::printCharactors(L"▄", { (short)(x + 10 + 11),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"█", { (short)(x + 10 - 3),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 - 2),(short)(y + 2 + 5) }, Color::GREEN, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 - 1),(short)(y + 2 + 5) }, Color::GREEN, Color::BLACK);
	View::printCharactors(L"▄", { (short)(x + 10),(short)(y + 2 + 5) }, Color::GREEN, Color::BLACK);
	View::printCharactors(L"█", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::GREEN, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 2),(short)(y + 2 + 5) }, Color::GREEN, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 3),(short)(y + 2 + 5) }, Color::GREEN, Color::BLACK);
	View::printCharactors(L"█", { (short)(x + 10 + 4),(short)(y + 2 + 5) }, Color::GREEN, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 5),(short)(y + 2 + 5) }, Color::GREEN, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 6),(short)(y + 2 + 5) }, Color::GREEN, Color::BLACK);
	View::printCharactors(L"█", { (short)(x + 10 + 7),(short)(y + 2 + 5) }, Color::GREEN, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 8),(short)(y + 2 + 5) }, Color::GREEN, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 9),(short)(y + 2 + 5) }, Color::GREEN, Color::BLACK);
	View::printCharactors(L"▀", { (short)(x + 10 + 10),(short)(y + 2 + 5) }, Color::GREEN, Color::BLACK);
	View::printCharactors(L"▀", { (short)(x + 10 + 11),(short)(y + 2 + 5) }, Color::GREEN, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 12),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"█", { (short)(x + 10 - 3),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 - 2),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 - 1),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10),(short)(y + 2 + 6) }, Color::GREEN, Color::WHITE);
	for (int i = 1; i <= 8; i++)
	{
		View::printCharactors(L"▀", { (short)(x + 10 + i),(short)(y + 2 + 6) }, Color::GREEN, Color::BLACK);
	}
	View::printCharactors(L"█", { (short)(x + 10 + 9),(short)(y + 2 + 6) }, Color::GREEN, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 10),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 11),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 12),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"▀", { (short)(x + 10 - 2),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 - 1),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10),(short)(y + 2 + 7) }, Color::YELLOW, Color::BLACK);
	View::printCharactors(L"█", { (short)(x + 10 + 1),(short)(y + 2 + 7) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 2),(short)(y + 2 + 7) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 3),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 4),(short)(y + 2 + 7) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 5),(short)(y + 2 + 7) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 6),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 7),(short)(y + 2 + 7) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 8),(short)(y + 2 + 7) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 9),(short)(y + 2 + 7) }, Color::YELLOW, Color::BLACK);
	View::printCharactors(L"▄", { (short)(x + 10 + 10),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 11),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"▀", { (short)(x + 10 - 1),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10),(short)(y + 2 + 8) }, Color::YELLOW, Color::BLACK);
	for (int i = 1; i <= 8; i++)
	{
		View::printCharactors(L"█", { (short)(x + 10 + i),(short)(y + 2 + 8) }, Color::YELLOW, Color::WHITE);
	}
	View::printCharactors(L"▀", { (short)(x + 10 + 9),(short)(y + 2 + 8) }, Color::YELLOW, Color::BLACK);
	View::printCharactors(L"▀", { (short)(x + 10 + 10),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);

	for (int i = 1; i <= 8; i++)
	{
		View::printCharactors(L"▀", { (short)(x + 10 + i),(short)(y + 2 + 9) }, Color::BLACK, Color::WHITE);
	}

}
void View::DrawMarioAvatar(int x, int y) {
	//LINE 1
	View::printCharactors(L"▄▄▄▄", { (short)(x + 10 + 3),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);

	//LINE 2
	View::printCharactors(L"▄", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color::RED, Color::BLACK);
	View::printCharactors(L"▀", { (short)(x + 10 + 3),(short)(y + 2 + 2) }, Color::RED, Color::WHITE);
	View::printCharactors(L"███", { (short)(x + 10 + 4),(short)(y + 2 + 2) }, Color::RED, Color::BLACK);
	View::printCharactors(L"▄▄", { (short)(x + 10 + 7),(short)(y + 2 + 2) }, Color::RED, Color::BLACK);
	View::printCharactors(L"▄", { (short)(x + 10 + 9),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);

	//LINE 3
	View::printCharactors(L"▄", { (short)(x + 10 + 0),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄▄▄", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 5),(short)(y + 2 + 3) }, Color::RED, Color::BLACK);
	View::printCharactors(L"████", { (short)(x + 10 + 6),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 10),(short)(y + 2 + 3) }, Color::RED, Color::BLACK);
	View::printCharactors(L"▄▄", { (short)(x + 10 + 11),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);

	//LINE 4
	View::printCharactors(L"▀", { (short)(x + 10 + -1),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀▀", { (short)(x + 10 + 0),(short)(y + 2 + 4) }, Color::RED, Color::BLACK);
	View::printCharactors(L"▀▀", { (short)(x + 10 + 2),(short)(y + 2 + 4) }, Color::RED, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 4),(short)(y + 2 + 4) }, Color::RED, Color::YELLOW);
	View::printCharactors(L"▀", { (short)(x + 10 + 5),(short)(y + 2 + 4) }, Color::RED, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 6),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀▀", { (short)(x + 10 + 7),(short)(y + 2 + 4) }, Color::RED, Color::BLACK);
	View::printCharactors(L"████", { (short)(x + 10 + 9),(short)(y + 2 + 4) }, Color::RED, Color::BLACK);
	View::printCharactors(L"█", { (short)(x + 10 + 13),(short)(y + 2 + 4) }, Color::BLACK, Color::BLACK);

	//LINE 5
	View::printCharactors(L"▀", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 3),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 4),(short)(y + 2 + 5) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 5),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"██", { (short)(x + 10 + 7),(short)(y + 2 + 5) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"██", { (short)(x + 10 + 9),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀▀", { (short)(x + 10 + 11),(short)(y + 2 + 5) }, Color::RED, Color::BLACK);
	View::printCharactors(L"▀", { (short)(x + 10 + 13),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	//LINE 6
	View::printCharactors(L"█", { (short)(x + 10 + 0),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█████", { (short)(x + 10 + 1),(short)(y + 2 + 6) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 6),(short)(y + 2 + 6) }, Color::YELLOW, Color::BLACK);
	View::printCharactors(L"█", { (short)(x + 10 + 7),(short)(y + 2 + 6) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 8),(short)(y + 2 + 6) }, Color::YELLOW, Color::BLACK);
	View::printCharactors(L"█", { (short)(x + 10 + 9),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 12),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"██", { (short)(x + 10 + 10),(short)(y + 2 + 6) }, Color::YELLOW, Color::WHITE);

	//LINE 7
	View::printCharactors(L"▀", { (short)(x + 10 + 0),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 1),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀▀▀", { (short)(x + 10 + 2),(short)(y + 2 + 7) }, Color::YELLOW, Color::BLACK);
	View::printCharactors(L"██", { (short)(x + 10 + 5),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 7),(short)(y + 2 + 7) }, Color::YELLOW, Color::BLACK);
	View::printCharactors(L"███", { (short)(x + 10 + 8),(short)(y + 2 + 7) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 11),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);

	//LINE 8
	View::printCharactors(L"▀", { (short)(x + 10 + 2),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀▀▀▀▀", { (short)(x + 10 + 3),(short)(y + 2 + 8) }, Color::YELLOW, Color::BLACK);
	View::printCharactors(L"█", { (short)(x + 10 + 8),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀▀", { (short)(x + 10 + 9),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);

}
void View::DrawDuckAvatar(int x, int y) {
	x += 2;
	
	for (int i = 0; i <= 3; i++)
	{
		View::printCharactors(L"▄", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	}


	View::printCharactors(L"█", { (short)(x + 10 - 1),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 3),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 4),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);


	View::printCharactors(L"█", { (short)(x + 10 - 3),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	for (int i = -2; i <= 0; i++)
	{
		View::printCharactors(L"▄", { (short)(x + 10 + i),(short)(y + 2 + 3) }, Color::BROWN, Color::BLACK);
	}
	View::printCharactors(L"▄", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::BROWN, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::BROWN, Color::BLACK);
	View::printCharactors(L"█", { (short)(x + 10 + 4),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);


	View::printCharactors(L"▀", { (short)(x + 10 - 3),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 - 2),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 - 1),(short)(y + 2 + 4) }, Color::BROWN, Color::BLACK);
	for (int i = 0; i <= 2; i++)
	{
		View::printCharactors(L"▀", { (short)(x + 10 + i),(short)(y + 2 + 4) }, Color::BROWN, Color::WHITE);
	}
	View::printCharactors(L"█", { (short)(x + 10 + 4),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);


	View::printCharactors(L"█", { (short)(x + 10 - 1),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	for (int i = 4; i <= 9; i++)
	{
		View::printCharactors(L"▀", { (short)(x + 10 + i),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	}
	View::printCharactors(L"█", { (short)(x + 10 + 10),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 11),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);


	View::printCharactors(L"█", { (short)(x + 10 - 1),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 3),(short)(y + 2 + 6) }, Color::DARK_GRAY, Color::WHITE);
	for (int i = 5; i <= 9; i = i + 2)
	{
		View::printCharactors(L"▄", { (short)(x + 10 + i),(short)(y + 2 + 6) }, Color::DARK_GRAY, Color::WHITE);
	}
	View::printCharactors(L"▀", { (short)(x + 10 + 11),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 12),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);


	View::printCharactors(L"█", { (short)(x + 10 - 1),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	for (int i = 4; i <= 10; i++)
	{
		View::printCharactors(L"▀", { (short)(x + 10 + i),(short)(y + 2 + 7) }, Color::DARK_GRAY, Color::WHITE);
	}
	View::printCharactors(L"█", { (short)(x + 10 + 11),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 12),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);


	View::printCharactors(L"█", { (short)(x + 10 - 1),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 9),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 10),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 11),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);


	View::printCharactors(L"▀", { (short)(x + 10),(short)(y + 2 + 9) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 1),(short)(y + 2 + 9) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 2),(short)(y + 2 + 9) }, Color::BROWN, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 3),(short)(y + 2 + 9) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 4),(short)(y + 2 + 9) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 5),(short)(y + 2 + 9) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 6),(short)(y + 2 + 9) }, Color::BROWN, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 7),(short)(y + 2 + 9) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 8),(short)(y + 2 + 9) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 9),(short)(y + 2 + 9) }, Color::BLACK, Color::WHITE);
}
void View::DrawAmongUsAvatar(int x, int y) {
	x += 2;
	/*x = 50;
	y = 10;*/

	for (int i = 1; i <= 5; i++)
	{
		View::printCharactors(L"▄", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	}

	View::printCharactors(L"▄", { (short)(x + 10 - 1),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10),(short)(y + 2 + 2) }, Color::BLACK, Color::RED);
	for (int i = 1; i <= 5; i++)
	{
		View::printCharactors(L"█", { (short)(x + 10 + i),(short)(y + 2 + 2) }, Color::RED, Color::WHITE);
	}
	View::printCharactors(L"▀", { (short)(x + 10 + 6),(short)(y + 2 + 2) }, Color::BLACK, Color::RED);
	View::printCharactors(L"▄", { (short)(x + 10 + 7),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"█", { (short)(x + 10 - 2),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 - 1),(short)(y + 2 + 3) }, Color::BLACK, Color::LIGHT_BLUE);
	View::printCharactors(L"▀", { (short)(x + 10),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::BLACK, Color::LIGHT_BLUE);
	View::printCharactors(L"▀", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::BLACK, Color::LIGHT_BLUE);
	View::printCharactors(L"▀", { (short)(x + 10 + 4),(short)(y + 2 + 3) }, Color::RED, Color::BLACK);
	View::printCharactors(L"█", { (short)(x + 10 + 5),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 6),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 7),(short)(y + 2 + 3) }, Color::BLACK, Color::RED);
	View::printCharactors(L"▀", { (short)(x + 10 + 8),(short)(y + 2 + 3) }, Color::WHITE, Color::BLACK);

	View::printCharactors(L"█", { (short)(x + 10 - 3),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 - 2),(short)(y + 2 + 4) }, Color::LIGHT_BLUE, Color::WHITE);
	for (int i = -1; i <= 1; i++)
	{
		View::printCharactors(L"▄", { (short)(x + 10 + i),(short)(y + 2 + 4) }, Color::LIGHT_BLUE, Color::WHITE);
	}
	View::printCharactors(L"█", { (short)(x + 10 + 2),(short)(y + 2 + 4) }, Color::LIGHT_BLUE, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 3),(short)(y + 2 + 4) }, Color::DARK_GRAY, Color::LIGHT_BLUE);
	View::printCharactors(L"█", { (short)(x + 10 + 4),(short)(y + 2 + 4) }, Color::DARK_GRAY, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 5),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 6),(short)(y + 2 + 4) }, Color::RED, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 7),(short)(y + 2 + 4) }, Color::RED, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 8),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 9),(short)(y + 2 + 4) }, Color::RED, Color::BLACK);
	View::printCharactors(L"▄", { (short)(x + 10 + 10),(short)(y + 2 + 4) }, Color::RED, Color::BLACK);
	View::printCharactors(L"▄", { (short)(x + 10 + 11),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"█", { (short)(x + 10 - 2),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	for (int i = -1; i <= 3; i++)
	{
		View::printCharactors(L"▄", { (short)(x + 10 + i),(short)(y + 2 + 5) }, Color::BLACK, Color::DARK_GRAY);
	}
	View::printCharactors(L"▄", { (short)(x + 10 + 4),(short)(y + 2 + 5) }, Color::RED, Color::BLACK);
	for (int i = 5; i <= 7; i++)
	{
		View::printCharactors(L"█", { (short)(x + 10 + i),(short)(y + 2 + 5) }, Color::RED, Color::WHITE);
	}
	View::printCharactors(L"█", { (short)(x + 10 + 8),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 9),(short)(y + 2 + 5) }, Color::RED, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 10),(short)(y + 2 + 5) }, Color::RED, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 11),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"█", { (short)(x + 10 - 2),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	for (int i = -1; i <= 7; i++)
	{
		View::printCharactors(L"█", { (short)(x + 10 + i),(short)(y + 2 + 6) }, Color::RED, Color::WHITE);
	}
	View::printCharactors(L"█", { (short)(x + 10 + 8),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 9),(short)(y + 2 + 6) }, Color::RED, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 10),(short)(y + 2 + 6) }, Color::RED, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 11),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"█", { (short)(x + 10 - 2),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 - 1),(short)(y + 2 + 7) }, Color::RED, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10),(short)(y + 2 + 7) }, Color::RED, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 1),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	for (int i = 2; i <= 4; i++)
	{
		View::printCharactors(L"▀", { (short)(x + 10 + i),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	}
	View::printCharactors(L"█", { (short)(x + 10 + 5),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 6),(short)(y + 2 + 7) }, Color::RED, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 7),(short)(y + 2 + 7) }, Color::RED, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 8),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 9),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 10),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"▀", { (short)(x + 10 - 2),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 - 1),(short)(y + 2 + 8) }, Color::RED, Color::BLACK);
	View::printCharactors(L"▀", { (short)(x + 10),(short)(y + 2 + 8) }, Color::RED, Color::BLACK);
	View::printCharactors(L"▀", { (short)(x + 10 + 1),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 5),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 6),(short)(y + 2 + 8) }, Color::RED, Color::BLACK);
	View::printCharactors(L"▀", { (short)(x + 10 + 7),(short)(y + 2 + 8) }, Color::RED, Color::BLACK);
	View::printCharactors(L"▀", { (short)(x + 10 + 8),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
}
void View::DrawBMOAvatar(int x, int y) {
	x += 2;
	/*x = 50;
	y = 10;*/

	for (int i = -1; i <= 9; i++)
	{
		View::printCharactors(L"▄", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLUE, Color::WHITE);
	}

	for (int i = 2; i <= 8; i++)
	{
		View::printCharactors(L"█", { (short)(x + 10 - 2),(short)(y + 2 + i) }, Color::BLUE, Color::WHITE);
		View::printCharactors(L"█", { (short)(x + 10 - 1),(short)(y + 2 + i) }, Color::LIGHT_BLUE, Color::WHITE);
	}


	for (int i = 0; i <= 8; i++)
	{
		View::printCharactors(L"▀", { (short)(x + 10 + i),(short)(y + 2 + 2) }, Color::LIGHT_BLUE, Color::WHITE);
	}

	for (int i = 2; i <= 8; i++)
	{
		View::printCharactors(L"█", { (short)(x + 10 + 9),(short)(y + 2 + i) }, Color::LIGHT_BLUE, Color::WHITE);
		View::printCharactors(L"█", { (short)(x + 10 + 10),(short)(y + 2 + i) }, Color::BLUE, Color::WHITE);
	}

	View::printCharactors(L"▄", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::BLUE, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 7),(short)(y + 2 + 3) }, Color::BLUE, Color::WHITE);

	for (int i = 3; i <= 5; i++)
	{
		View::printCharactors(L"▀", { (short)(x + 10 + i),(short)(y + 2 + 4) }, Color::BLUE, Color::WHITE);
	}

	for (int i = 0; i <= 8; i++)
	{
		View::printCharactors(L"▄", { (short)(x + 10 + i),(short)(y + 2 + 5) }, Color::LIGHT_BLUE, Color::WHITE);
	}

	View::printCharactors(L"█", { (short)(x + 10 - 1),(short)(y + 2 + 6) }, Color::LIGHT_BLUE, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 5),(short)(y + 2 + 6) }, Color::LIGHT_BLUE, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 6),(short)(y + 2 + 6) }, Color::LIGHT_BLUE, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 7),(short)(y + 2 + 6) }, Color::BLUE, Color::LIGHT_BLUE);
	View::printCharactors(L"█", { (short)(x + 10 + 8),(short)(y + 2 + 6) }, Color::LIGHT_BLUE, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 9),(short)(y + 2 + 6) }, Color::LIGHT_BLUE, Color::WHITE);

	for (int i = 0; i <= 4; i++)
	{
		View::printCharactors(L"▀", { (short)(x + 10 + i),(short)(y + 2 + 6) }, Color::BLUE, Color::LIGHT_BLUE);
	}

	View::printCharactors(L"█", { (short)(x + 10 - 1),(short)(y + 2 + 7) }, Color::LIGHT_BLUE, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10),(short)(y + 2 + 7) }, Color::YELLOW, Color::LIGHT_BLUE);
	View::printCharactors(L"█", { (short)(x + 10 + 1),(short)(y + 2 + 7) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 2),(short)(y + 2 + 7) }, Color::YELLOW, Color::LIGHT_BLUE);
	View::printCharactors(L"█", { (short)(x + 10 + 3),(short)(y + 2 + 7) }, Color::LIGHT_BLUE, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 4),(short)(y + 2 + 7) }, Color::LIGHT_BLUE, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 5),(short)(y + 2 + 7) }, Color::BLUE, Color::LIGHT_BLUE);
	View::printCharactors(L"▄", { (short)(x + 10 + 6),(short)(y + 2 + 7) }, Color::RED, Color::LIGHT_BLUE);
	View::printCharactors(L"▀", { (short)(x + 10 + 7),(short)(y + 2 + 7) }, Color::LIGHT_GREEN, Color::LIGHT_BLUE);
	View::printCharactors(L"█", { (short)(x + 10 + 8),(short)(y + 2 + 7) }, Color::LIGHT_BLUE, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 9),(short)(y + 2 + 7) }, Color::LIGHT_BLUE, Color::WHITE);

	View::printCharactors(L"█", { (short)(x + 10 - 1),(short)(y + 2 + 8) }, Color::LIGHT_BLUE, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10),(short)(y + 2 + 8) }, Color::LIGHT_BLUE, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 1),(short)(y + 2 + 8) }, Color::YELLOW, Color::LIGHT_BLUE);

	for (int i = 2; i <= 9; i++)
	{
		View::printCharactors(L"█", { (short)(x + 10 + i),(short)(y + 2 + 8) }, Color::LIGHT_BLUE, Color::WHITE);
	}

	for (int i = -1; i <= 9; i++)
	{
		View::printCharactors(L"▀", { (short)(x + 10 + i),(short)(y + 2 + 9) }, Color::BLUE, Color::WHITE);
	}
}
void View::DrawFinnAvatar(int x, int y) {
	//x = 50;
	//y = 10;
	//
	//LINE 1
	View::printCharactors(L"▄▄", { (short)(x + 10 + 1),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄▄", { (short)(x + 10 + 10),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);

	//LINE 2
	View::printCharactors(L"█", { (short)(x + 10 + 0),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀▀▀▀▀▀▀", { (short)(x + 10 + 3),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 12),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);

	//LINE 3
	View::printCharactors(L"█", { (short)(x + 10 + 0),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 10),(short)(y + 2 + 3) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"███████", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 12),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);

	//LINE 4
	View::printCharactors(L"█", { (short)(x + 10 + 2),(short)(y + 2 + 4) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 10),(short)(y + 2 + 4) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 3),(short)(y + 2 + 4) }, Color::YELLOW, Color::BLACK);
	View::printCharactors(L"▄", { (short)(x + 10 + 9),(short)(y + 2 + 4) }, Color::YELLOW, Color::BLACK);
	View::printCharactors(L"█", { (short)(x + 10 + 4),(short)(y + 2 + 4) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 8),(short)(y + 2 + 4) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"▀▀▀", { (short)(x + 10 + 5),(short)(y + 2 + 4) }, Color::YELLOW, Color::BLACK);
	View::printCharactors(L"█", { (short)(x + 10 + 0),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 12),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);

	//LINE 5
	View::printCharactors(L"▄", { (short)(x + 10 + -1),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 13),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 0),(short)(y + 2 + 5) }, Color::LIGHT_GREEN, Color::BLACK);
	View::printCharactors(L"▄", { (short)(x + 10 + 12),(short)(y + 2 + 5) }, Color::LIGHT_GREEN, Color::BLACK);
	View::printCharactors(L"▄", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::LIGHT_GREEN, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 11),(short)(y + 2 + 5) }, Color::LIGHT_GREEN, Color::WHITE);
	View::printCharactors(L"▀▀▀▀▀▀▀", { (short)(x + 10 + 3),(short)(y + 2 + 5) }, Color::YELLOW, Color::WHITE);

	//LINE 6
	View::printCharactors(L"█", { (short)(x + 10 + -1),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 13),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 0),(short)(y + 2 + 6) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 12),(short)(y + 2 + 6) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 1),(short)(y + 2 + 6) }, Color::LIGHT_GREEN, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 11),(short)(y + 2 + 6) }, Color::LIGHT_GREEN, Color::WHITE);
	for (int i = 2; i <= 10; i++) {
		View::printCharactors(L"█", { (short)(x + 10 + i),(short)(y + 2 + 6) }, Color::LIGHT_BLUE, Color::WHITE);

	}

	//LINE 7
	View::printCharactors(L"▀", { (short)(x + 10 + -1),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 13),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 0),(short)(y + 2 + 7) }, Color::YELLOW, Color::BLACK);
	View::printCharactors(L"▀", { (short)(x + 10 + 12),(short)(y + 2 + 7) }, Color::YELLOW, Color::BLACK);
	for (int i = 1; i <= 11; i++) {
		View::printCharactors(L"█", { (short)(x + 10 + i),(short)(y + 2 + 7) }, Color::LIGHT_BLUE, Color::WHITE);

	}

	//LINE 8
	View::printCharactors(L"█", { (short)(x + 10 + 0),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 12),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"███", { (short)(x + 10 + 1),(short)(y + 2 + 8) }, Color::BLUE, Color::WHITE);
	View::printCharactors(L"███", { (short)(x + 10 + 9),(short)(y + 2 + 8) }, Color::BLUE, Color::WHITE);
	View::printCharactors(L"▀▀▀▀▀", { (short)(x + 10 + 4),(short)(y + 2 + 8) }, Color::BLUE, Color::BLACK);



}
void View::DrawDogeAvatar(int x, int y) {
	y += 1;
	x += 2;
	/*x = 50;
	y = 10;*/


	//LINE 1

	View::printCharactors(L"▄", { (short)(x + 10 + 3),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 4),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 8),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);

	//LINE 2
	View::printCharactors(L"█", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 3),(short)(y + 2 + 2) }, Color::BROWN, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 4),(short)(y + 2 + 2) }, Color::BROWN, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 5),(short)(y + 2 + 2) }, Color::BROWN, Color::BLACK);
	View::printCharactors(L"▄", { (short)(x + 10 + 6),(short)(y + 2 + 2) }, Color::BROWN, Color::BLACK);
	View::printCharactors(L"▄", { (short)(x + 10 + 7),(short)(y + 2 + 2) }, Color::BROWN, Color::BLACK);
	View::printCharactors(L"█", { (short)(x + 10 + 8),(short)(y + 2 + 2) }, Color::BROWN, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 9),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);

	//LINE 3
	View::printCharactors(L"█", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	for (int i = 3; i <= 8; i++) {
		View::printCharactors(L"█", { (short)(x + 10 + i),(short)(y + 2 + 3) }, Color::BROWN, Color::WHITE);
	}
	View::printCharactors(L"▀", { (short)(x + 10 + 9),(short)(y + 2 + 3) }, Color::BROWN, Color::BLACK);
	View::printCharactors(L"▀", { (short)(x + 10 + 10),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 11),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);

	//LINE 4
	View::printCharactors(L"▄", { (short)(x + 10 + -3),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + -2),(short)(y + 2 + 4) }, Color::YELLOW, Color::BLACK);
	View::printCharactors(L"▄", { (short)(x + 10 + -1),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 1),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 2),(short)(y + 2 + 4) }, Color::BROWN, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 3),(short)(y + 2 + 4) }, Color::BROWN, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 4),(short)(y + 2 + 4) }, Color::BROWN, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 5),(short)(y + 2 + 4) }, Color::BROWN, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 6),(short)(y + 2 + 4) }, Color::BLACK, Color::BROWN);
	View::printCharactors(L"▄", { (short)(x + 10 + 7),(short)(y + 2 + 4) }, Color::BROWN, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 8),(short)(y + 2 + 4) }, Color::BROWN, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 9),(short)(y + 2 + 4) }, Color::BROWN, Color::BLACK);
	View::printCharactors(L"▀", { (short)(x + 10 + 10),(short)(y + 2 + 4) }, Color::BROWN, Color::BLACK);
	View::printCharactors(L"▀", { (short)(x + 10 + 11),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 12),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	//LINE 5 
	View::printCharactors(L"█", { (short)(x + 10 + -3),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + -2),(short)(y + 2 + 5) }, Color::YELLOW, Color::BROWN);
	View::printCharactors(L"█", { (short)(x + 10 + -1),(short)(y + 2 + 5) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 0),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"███", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::BROWN, Color::WHITE);
	View::printCharactors(L"▄", { (short)(x + 10 + 4),(short)(y + 2 + 5) }, Color::DARK_GRAY, Color::WHITE);
	View::printCharactors(L"▄▄▄▀", { (short)(x + 10 + 7),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 12),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);

	//LINE 6
	View::printCharactors(L"▀", { (short)(x + 10 + -2),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▄▄", { (short)(x + 10 + -1),(short)(y + 2 + 6) }, Color::BLACK, Color::BROWN);
	View::printCharactors(L"█", { (short)(x + 10 + 1),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 2),(short)(y + 2 + 6) }, Color::BROWN, Color::BLACK);
	View::printCharactors(L"██", { (short)(x + 10 + 3),(short)(y + 2 + 6) }, Color::BROWN, Color::WHITE);
	View::printCharactors(L"█", { (short)(x + 10 + 5),(short)(y + 2 + 6) }, Color::DARK_GRAY, Color::WHITE);
	View::printCharactors(L"▄▄▄▄▄", { (short)(x + 10 + 6),(short)(y + 2 + 6) }, Color::DARK_GRAY, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 11),(short)(y + 2 + 6) }, Color::DARK_GRAY, Color::BLACK);
	View::printCharactors(L"▀", { (short)(x + 10 + 12),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);

	//LINE 7
	for (int i = 2; i <= 10; i++) {
		View::printCharactors(L"▀", { (short)(x + 10 + i),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	}

	View::printCharactors(L"█", { (short)(x + 10 + 3),(short)(y + 2 + 2) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"▀", { (short)(x + 10 + 4),(short)(y + 2 + 2) }, Color::YELLOW, Color::BROWN);
	View::printCharactors(L"▀", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::YELLOW, Color::BROWN);

}
void View::DrawBotAvatar(int x, int y) {
	//int x, y;
	//x = 113;		
	//y = 0;
	//View::drawBackGroundAvatar(4, x + 6, x + 6 + 18, y , y  + 10);
	//blue
	y += 2;
	for (int i = 3; i <= 8; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 2) }, Color::BLUE, Color::WHITE);
	}

	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::BLUE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 4) }, Color::BLUE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 10),(short)(y + 2 + 3) }, Color::BLUE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 10),(short)(y + 2 + 4) }, Color::BLUE, Color::WHITE);

	for (int i = 2; i <= 9; i++) {
		if (i == 5 || i == 6) 	View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 5) }, Color::LIGHT_CYAN, Color::BLACK);
		else View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 5) }, Color::BLUE, Color::BLACK);
	}
	for (int i = 2; i <= 9; i++) {
		if (i == 2 || i == 9) 	View::printCharactors(L"\x2580", { (short)(x + 10 + i),(short)(y + 2 + 6) }, Color::LIGHT_CYAN, Color::BLACK);
		else View::printCharactors(L"\x2580", { (short)(x + 10 + i),(short)(y + 2 + 6) }, Color::BLUE, Color::BLACK);
	}

	//cyan
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 3) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 4) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 3) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 4) }, Color::LIGHT_CYAN, Color::WHITE);

	//blue + cyan
	View::printCharactors(L"\x2584", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color::BLUE, Color::LIGHT_CYAN);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 9),(short)(y + 2 + 2) }, Color::BLUE, Color::LIGHT_CYAN);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::BLUE, Color::LIGHT_CYAN);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 10),(short)(y + 2 + 5) }, Color::BLUE, Color::LIGHT_CYAN);


	//cyan + black
	View::printCharactors(L"\x2584", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::LIGHT_CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 10),(short)(y + 2 + 2) }, Color::LIGHT_CYAN, Color::BLACK);

	View::printCharactors(L"\x2580", { (short)(x + 10 + 0),(short)(y + 2 + 5) }, Color::LIGHT_CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 11),(short)(y + 2 + 5) }, Color::LIGHT_CYAN, Color::BLACK);

	//black
	for (int i = 2; i <= 9; i++) {
		if (i == 7) View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
		else View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	}

	View::printCharactors(L"\x2584", { (short)(x + 10 + 0),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 11),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2580", { (short)(x + 10 + -1),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 12),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 10),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2588", { (short)(x + 10 + -1),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + -1),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);

	for (int i = 2; i <= 9; i++) {
		if (i == 3 || i == 8) 	View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 3) }, Color::LIGHT_CYAN, Color::BLACK);
		else View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	}

	for (int i = 2; i <= 9; i++) {
		if (i == 3 || i == 8) 	View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 4) }, Color::LIGHT_CYAN, Color::BLACK);
		else View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 4) }, Color::BLACK, Color::BLACK);
	}
	View::printCharactors(L"\x2580", { (short)(x + 10 + 9),(short)(y + 2 + 0) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 8),(short)(y + 2 + 0) }, Color::BLACK, Color::WHITE);
}
void View::DrawSpidermanAvatar(int x, int y) {
	//red
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	for (int i = 2; i <= 10; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 2) }, Color::RED, Color::WHITE);

	}
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 4) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 4) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 5) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 5) }, Color::RED, Color::WHITE);

	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 6) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 6) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 6) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 6) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 6) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);

	for (int i = 3; i <= 9; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 7) }, Color::RED, Color::WHITE);
	}

	//black

	for (int i = 2; i <= 10; i++) {
		View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	}
	View::printCharactors(L"\x2588", { (short)(x + 10 + -1),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 13),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + -1),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 13),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + -1),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 13),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 0),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 12),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 5),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 7),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 11),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 3),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 9),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 7),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 10),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 9),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);

	//red + black
	View::printCharactors(L"\x2584", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 11),(short)(y + 2 + 2) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 2),(short)(y + 2 + 6) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 3),(short)(y + 2 + 6) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 6) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 8),(short)(y + 2 + 6) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 9),(short)(y + 2 + 6) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 10),(short)(y + 2 + 6) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 6),(short)(y + 2 + 5) }, Color::RED, Color::BLACK);

	for (int i = 4; i <= 8; i++) {
		View::printCharactors(L"\x2580", { (short)(x + 10 + i),(short)(y + 2 + 8) }, Color::RED, Color::BLACK);
	}
	View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 7) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 10),(short)(y + 2 + 7) }, Color::RED, Color::BLACK);


	View::printCharactors(L"\x2580", { (short)(x + 10 + 6),(short)(y + 2 + 4) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 11),(short)(y + 2 + 3) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 4),(short)(y + 2 + 3) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 8),(short)(y + 2 + 3) }, Color::RED, Color::BLACK);
}
void View::DrawIronmanAvatar(int x, int y) {
	//red
	for (int i = 4; i <= 8; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 2) }, Color::RED, Color::WHITE);
	}
	View::printCharactors(L"█", { (short)(x + 10 + 5),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 3) }, Color::RED, Color::WHITE);

	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 4) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 5) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 5) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 4) }, Color::RED, Color::WHITE);

	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 6) }, Color::RED, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 6) }, Color::RED, Color::WHITE);

	//black
	for (int i = 2; i <= 10; i++) {
		View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	}

	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + -1),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 13),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + -1),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 13),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);


	//YELLOW + BLACK
	for (int i = 2; i <= 10; i++) {
		View::printCharactors(L"\x2580", { (short)(x + 10 + i),(short)(y + 2 + 4) }, Color::YELLOW, Color::BLACK);

	}
	for (int i = 2; i <= 10; i++) {
		if (i >= 5 && i <= 7) View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 5) }, Color::YELLOW, Color::BLACK);
		else {
			View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 5) }, Color::YELLOW, Color::WHITE);						//----------------WHITE
		}
	}
	for (int i = 4; i <= 8; i++) {
		View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 7) }, Color::YELLOW, Color::BLACK);
	}
	View::printCharactors(L"\x2580", { (short)(x + 10 + 3),(short)(y + 2 + 7) }, Color::YELLOW, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 9),(short)(y + 2 + 7) }, Color::YELLOW, Color::BLACK);

	//yellow
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 9),(short)(y + 2 + 3) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 10),(short)(y + 2 + 3) }, Color::YELLOW, Color::WHITE);

	View::printCharactors(L"\x2588", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::YELLOW, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 5) }, Color::YELLOW, Color::WHITE);
	for (int i = 2; i <= 10; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 6) }, Color::YELLOW, Color::WHITE);
	}


	// yellow+ red
	View::printCharactors(L"\x2584", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color::YELLOW, Color::RED);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 3),(short)(y + 2 + 2) }, Color::YELLOW, Color::RED);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 9),(short)(y + 2 + 2) }, Color::YELLOW, Color::RED);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 10),(short)(y + 2 + 2) }, Color::YELLOW, Color::RED);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 3) }, Color::YELLOW, Color::RED);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 8),(short)(y + 2 + 3) }, Color::YELLOW, Color::RED);

	//red + black
	View::printCharactors(L"\x2584", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 11),(short)(y + 2 + 2) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 7) }, Color::RED, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 10),(short)(y + 2 + 7) }, Color::RED, Color::BLACK);
	for (int i = 4; i <= 8; i++) {
		View::printCharactors(L"\x2580", { (short)(x + 10 + i),(short)(y + 2 + 8) }, Color::RED, Color::BLACK);
	}

	//black + WHITE
	View::printCharactors(L"\x2584", { (short)(x + 10 + 0),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 12),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 11),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2580", { (short)(x + 10 + 3),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 9),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
}
void View::DrawPacman() {
	int x, y;
	x = -5;
	y = 25;
	int color;
	//srand((unsigned int)time(NULL));				//?
	for (int i = 1; i <= 14; i++) {				//number of ghosts

		color = View::GetRandom(1, 13);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color(color), Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 2) }, Color(color), Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 2) }, Color(color), Color::BLACK);

		View::printCharactors(L"\x2588", { (short)(x + 10 + 0),(short)(y + 2 + 3) }, Color(color), Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color(color), Color::BLACK);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 3) }, Color(color), Color::BLACK);

		for (int i = 0; i <= 6; i++) {
			View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 4) }, Color(color), Color::BLACK);
		}

		View::printCharactors(L"\x2584", { (short)(x + 10 + 1),(short)(y + 2 + 2) }, Color(color), Color::WHITE);
		View::printCharactors(L"\x2584", { (short)(x + 10 + 5),(short)(y + 2 + 2) }, Color(color), Color::WHITE);

		View::printCharactors(L"\x2580", { (short)(x + 10 + 0),(short)(y + 2 + 5) }, Color(color), Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 5) }, Color(color), Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 4),(short)(y + 2 + 5) }, Color(color), Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 6),(short)(y + 2 + 5) }, Color(color), Color::WHITE);

		View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
		Sleep(100);

		x += 10;
	}
}
void View::drawTrophy() {
	int x, y;
	x = 82;
	y = 10;

	for (int i = 3; i <= 10; i++) {
		if (i == 4) continue;
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 3) }, Color::LIGHT_CYAN, Color::WHITE);
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 4) }, Color::LIGHT_CYAN, Color::WHITE);
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 5) }, Color::LIGHT_CYAN, Color::WHITE);
	}
	View::printCharactors(L"\x2588", { (short)(x + 10 + 4),(short)(y + 2 + 5) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 7) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 8) }, Color::LIGHT_CYAN, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 9) }, Color::LIGHT_CYAN, Color::WHITE);
	for (int i = 5; i <= 8; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + i),(short)(y + 2 + 6) }, Color::LIGHT_CYAN, Color::WHITE);
	}

	View::printCharactors(L"\x2584", { (short)(x + 10 + 7),(short)(y + 2 + 3) }, Color::PURPLE, Color::LIGHT_CYAN);		//1
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 4) }, Color::PURPLE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 7),(short)(y + 2 + 5) }, Color::PURPLE, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 6),(short)(y + 2 + 4) }, Color::LIGHT_CYAN, Color::PURPLE);

	for (int i = 2; i <= 5; i++) {
		View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + i) }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2588", { (short)(x + 10 + 12),(short)(y + 2 + i) }, Color::BLACK, Color::WHITE);
	}

	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 12),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
								 
	View::printCharactors(L"\x2580", { (short)(x + 10 + 4),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 9),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 10),(short)(y + 2 + 7) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 8),(short)(y + 2 + 8) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 9) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 10),(short)(y + 2 + 9) }, Color::BLACK, Color::WHITE);

	for (int i = 4; i <= 10; i++) {
		View::printCharactors(L"\x2580", { (short)(x + 10 + i),(short)(y + 2 + 10) }, Color::BLACK, Color::WHITE);
	}
	//2 mau main+black
	for (int i = 3; i <= 10; i++) {
		View::printCharactors(L"\x2584", { (short)(x + 10 + i),(short)(y + 2 + 2) }, Color::LIGHT_CYAN, Color::BLACK);
	}
	View::printCharactors(L"\x2580", { (short)(x + 10 + 4),(short)(y + 2 + 6) }, Color::LIGHT_CYAN, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 6),(short)(y + 2 + 7) }, Color::LIGHT_CYAN, Color::BLACK);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 5),(short)(y + 2 + 9) }, Color::LIGHT_CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 6),(short)(y + 2 + 9) }, Color::LIGHT_CYAN, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 8),(short)(y + 2 + 9) }, Color::LIGHT_CYAN, Color::BLACK);

	//2 mau shadow + black
	View::printCharactors(L"\x2580", { (short)(x + 10 + 10),(short)(y + 2 + 6) }, Color::LIGHT_PURPLE, Color::BLACK);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 8),(short)(y + 2 + 7) }, Color::LIGHT_PURPLE, Color::BLACK);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 9),(short)(y + 2 + 9) }, Color::LIGHT_PURPLE, Color::BLACK);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 11),(short)(y + 2 + 2) }, Color::LIGHT_PURPLE, Color::BLACK);

	//2 mau main + shadow
	View::printCharactors(L"\x2580", { (short)(x + 10 + 9),(short)(y + 2 + 6) }, Color::LIGHT_CYAN, Color::LIGHT_PURPLE);
	
	//shadow
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 3) }, Color::LIGHT_PURPLE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 4) }, Color::LIGHT_PURPLE, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 11),(short)(y + 2 + 5) }, Color::LIGHT_PURPLE, Color::WHITE);

	//handle
	View::printCharactors(L"\x2580", { (short)(x + 10 + 0),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 13),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 14),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 0),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 1),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 13),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 14),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 0),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 14),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2588", { (short)(x + 10 + -1),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 15),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + -1),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 15),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);


}

void View::drawBorder3( int left, int right,int top, int bot, std::wstring winnerName) {
	for (int i = left+1 ; i <= right -1 ; i++) {
		View::printCharactors(L"\x2584", { (short)i,(short)top }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2580", { (short)i,(short)bot }, Color::BLACK, Color::WHITE);
	}

	for (int i = top + 1; i <= bot - 1; i++) {
		View::printCharactors(L"\x2588", { (short)left,(short)i }, Color::BLACK, Color::WHITE);
		View::printCharactors(L"\x2588", { (short)right,(short)i }, Color::BLACK, Color::WHITE);
	}
	short x = (short)left+((right - left) / 2 - winnerName.length() / 2);
		
	View::printCharactors(winnerName, {(short)(x),(short)(bot + 1)}, Color::BLACK, Color::WHITE);
}

void View::drawBackGroundAvatar(int n,int left , int right, int top , int bot) {
	
	switch (n)
	{
	case 1:
		for (int i = top + 1; i <= bot - 1; i++) {
			for (int j = left; j <= right; j++) {
				View::printCharactors(L"\x2588", { (short)(j),(short)(i) }, Color::LIGHT_BLUE, Color::WHITE);
			}
		}
		break;
	case 2:
		for (int i = top + 1; i <= bot - 1; i++) {
			for (int j = left; j <= right; j++) {
				View::printCharactors(L"\x2588", { (short)(j),(short)(i) }, Color::LIGHT_CYAN, Color::WHITE);
			}
		}
		break;
	case 3:
		for (int i = top + 1; i <= bot - 1; i++) {
			for (int j = left; j <= right; j++) {
				View::printCharactors(L"\x2588", { (short)(j),(short)(i) }, Color::GREEN, Color::WHITE);
			}
		}
		break;
	default:
		break;
	}

	
}
void View::drawVSText() {
	int x, y;
	x = 91;
	y = 1;
	//chu V
	View::printCharactors(L"\x2588", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 6),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2588", { (short)(x + 10 + 5),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 4),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);

	x = 96;
	y = 3;
	//chu S
	View::printCharactors(L"\x2580", { (short)(x + 10 + 2),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 3),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 2),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 3),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2580", { (short)(x + 10 + 5),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);

	View::printCharactors(L"\x2584", { (short)(x + 10 + 3),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 4),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	View::printCharactors(L"\x2584", { (short)(x + 10 + 5),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);

}
void View::splashScreenInfo() {
	int x, y;
	x = 50;
	y = 12;

	View::printCharactors(L"        NHÓM 10", { (short)(x + 10),(short)(y + 2) }, Color::BLACK, Color::WHITE); Sleep(300);
	View::printCharactors(L" GV: Trương Toàn Thịnh", { (short)(x + 10),(short)(y + 4) }, Color::BLACK, Color::WHITE); Sleep(100);

	View::printCharactors(L" Huỳnh Anh Huy          ", { (short)(x + 10),(short)(y + 6) }, Color::BLACK, Color::WHITE); Sleep(100);
	View::printCharactors(L" Phan Nguyễn Hoàng Quân ", { (short)(x + 10),(short)(y + 7) }, Color::BLACK, Color::WHITE); Sleep(100);
	View::printCharactors(L" Nguyễn Lâm Anh Duy     ", { (short)(x + 10),(short)(y + 8) }, Color::BLACK, Color::WHITE); Sleep(100);
	View::printCharactors(L" Lê Hải Nam             ", { (short)(x + 10),(short)(y + 9) }, Color::BLACK, Color::WHITE); Sleep(300);
}
void View::splashScreen() {
	int x, y;
	x = 25;
	y = 2;

	Sleep(300);
	View::printCharactors(L"	░█████╗░░█████╗░██████╗░░█████╗░  ░██████╗░░█████╗░███╗░░░███╗███████╗		", { (short)(10 + x),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	Sleep(100);
	View::printCharactors(L"	██╔══██╗██╔══██╗██╔══██╗██╔══██╗  ██╔════╝░██╔══██╗████╗░████║██╔════╝	    ", { (short)(10 + x),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	Sleep(100);
	View::printCharactors(L"	██║░░╚═╝███████║██████╔╝██║░░██║  ██║░░██╗░███████║██╔████╔██║█████╗░░	    ", { (short)(10 + x),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	Sleep(100);
	View::printCharactors(L"	██║░░██╗██╔══██║██╔══██╗██║░░██║  ██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░	    ", { (short)(10 + x),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	Sleep(100);
	View::printCharactors(L"	╚█████╔╝██║░░██║██║░░██║╚█████╔╝  ╚██████╔╝██║░░██║██║░╚═╝░██║███████╗	    ", { (short)(10 + x),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	Sleep(100);
	View::printCharactors(L"	░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝░╚════╝░  ░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝		", { (short)(10 + x),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	Sleep(100);

	View::splashScreenInfo();
	View::DrawPacman();

	InputHandle::GetKey();
}
//random function in range
int View::GetRandom(int min, int max) {							
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

void View::gotoXY(short x, short y) {
	static HANDLE h = NULL;
	if (!h) h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { x, y };
	SetConsoleCursorPosition(h, coord);
}
void View::fixConsoleWindow() {
	system("color f0");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void View::textColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void View::textStyle(int fontSize) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = fontSize;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}
void View::clearRectangleArea(
	COORD start, 
	int width, 
	int height
) {
	short x = start.X;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			View::printCharactors(L"X", start, Color::WHITE, Color::WHITE);
			start.X++;
		}
		start.Y++;
		start.X = x;
	}
}

void View::printCharactors(
	std::wstring content, 
	COORD spot, 
	Color text_color,
	Color background_color,
	short maxLength
) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD Written;

	// convert text color and background color to WORD that in range of 0-265 in color code table
	int color = (int)text_color + (int)background_color * 16;
	
	// if the content is too long
	if (maxLength != -1) {
		content = content.substr(0, maxLength) + L"...";
	}
	
	for (int i = 0; i < content.length(); i++) {
		// set text background color
		FillConsoleOutputAttribute(hOut, color, 1, spot, &Written);
		
		// print 1 character 
		FillConsoleOutputCharacterW(hOut, content[i], 1, spot, &Written);
		spot.X++;
	}
}

void View::printVerticalCenteredCharactors(
	std::wstring content,
	SMALL_RECT box,
	short y_offset,
	View::Color text_color,
	View::Color background_color,
	short maxLength
) {
	// if content is too long
	if (maxLength != -1) {
		content = content.substr(0, maxLength) + L"...";
	}

	short x = box.Left + (box.Right - box.Left) / 2 - content.length() / 2;
 	printCharactors(content, { x, short(box.Top + y_offset) }, text_color, background_color);
}

PCHAR_INFO View::getScreenBuffer() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	PCHAR_INFO buffer = new CHAR_INFO[View::SCREEN_WIDTH * View::SCREEN_HEIGHT];
	SMALL_RECT readRegion = { 0, 0, View::SCREEN_WIDTH - 1, View::SCREEN_HEIGHT - 1 };

	ReadConsoleOutput(hOut, buffer, { View::SCREEN_WIDTH, View::SCREEN_HEIGHT }, { 0, 0 }, &readRegion);
	
	return buffer;
}

void View::writeScreenBuffer(PCHAR_INFO buffer) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT writeRegion = { 0, 0, View::SCREEN_WIDTH - 1, View::SCREEN_HEIGHT - 1 };

	WriteConsoleOutput(hOut, buffer, { View::SCREEN_WIDTH, View::SCREEN_HEIGHT }, { 0, 0 }, &writeRegion);
}

void View::confirmDialog(
	std::wstring content,
	SMALL_RECT box,
	std::function<void()> positiveAction,
	std::function<void()> negativeAction
) {
	int width = content.size() + 20;
	COORD spot = View::getCenteredSpot(content, box);
	spot.X -= 10; spot.Y -= 5;
	View::drawRectangleBorder(spot, width, 10, View::Color::BLACK);
	// print dialog title
	View::printVerticalCenteredCharactors(
		L"Confirm Dialog",
		{ spot.X, spot.Y, short(spot.X + width), short(spot.Y + 10) },
		2,
		View::Color::WHITE,
		View::Color::BLACK
	);
	
	// print dialog content
	View::printVerticalCenteredCharactors(
		content,
		{ spot.X, spot.Y, short(spot.X + width), short(spot.Y + 10) },
		4,
		View::Color::BLACK,
		View::Color::WHITE
	);

	// print dialog buttons
	int indx = 0;
	std::vector<MenuItem> items = {
		{ 0, L"YES", MenuOption::YES },
		{ 1, L"NO", MenuOption::NO }
	};

	short center_x = spot.X + width / 2;
	
	DrawMenu(items, { center_x, short(spot.Y + 6) }, View::Color::BLACK, View::Color::PURPLE, &indx, items.size());
	menuOptionChanged(items, { center_x, short(spot.Y + 6) }, View::Color::BLACK, View::Color::PURPLE, &indx, items.size());

	switch (items[indx].menu_option) {
	case MenuOption::YES:
		positiveAction();
		break;
	case MenuOption::NO:
		negativeAction();
		break;

	default:
		negativeAction();
		break;
	}
}

COORD View::getCenteredSpot(std::wstring content, SMALL_RECT box) {
	short x = box.Left + (box.Right - box.Left) / 2 - content.length() / 2;
	short y = box.Top + (box.Bottom - box.Top) / 2;
	return { x, y };
}

void View::printCenteredToast(std::wstring content, SMALL_RECT box, View::Color text_color, View::Color background_color) {
	COORD spot = View::getCenteredSpot(content, box);
	View::printCharactors(content, spot, text_color, background_color);
	Sleep(1000);
	View::clearRectangleArea(spot, content.length(), 1);
}

void View::showWinningMoves(int player, std::vector<COORD> winning_moves) {
	std::wstring winner_ws = player == 1 ? L"X" : L"O";
	for (int i = 0; i < winning_moves.size(); i++) {
		View::printCharactors(winner_ws, winning_moves[i], View::Color::BLACK, View::Color::YELLOW);
	}
}

void View::drawCaroGameText(int delayTime) {
	int x, y;
	x = 25;
	y = 2;
	Sleep(delayTime);
	View::printCharactors(L"	░█████╗░░█████╗░██████╗░░█████╗░  ░██████╗░░█████╗░███╗░░░███╗███████╗		", { (short)(10 + x),(short)(y + 2 + 1) }, Color::BLACK, Color::WHITE);
	Sleep(delayTime);
	View::printCharactors(L"	██╔══██╗██╔══██╗██╔══██╗██╔══██╗  ██╔════╝░██╔══██╗████╗░████║██╔════╝	    ", { (short)(10 + x),(short)(y + 2 + 2) }, Color::BLACK, Color::WHITE);
	Sleep(delayTime);
	View::printCharactors(L"	██║░░╚═╝███████║██████╔╝██║░░██║  ██║░░██╗░███████║██╔████╔██║█████╗░░	    ", { (short)(10 + x),(short)(y + 2 + 3) }, Color::BLACK, Color::WHITE);
	Sleep(delayTime);
	View::printCharactors(L"	██║░░██╗██╔══██║██╔══██╗██║░░██║  ██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░	    ", { (short)(10 + x),(short)(y + 2 + 4) }, Color::BLACK, Color::WHITE);
	Sleep(delayTime);
	View::printCharactors(L"	╚█████╔╝██║░░██║██║░░██║╚█████╔╝  ╚██████╔╝██║░░██║██║░╚═╝░██║███████╗	    ", { (short)(10 + x),(short)(y + 2 + 5) }, Color::BLACK, Color::WHITE);
	Sleep(delayTime);
	View::printCharactors(L"	░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝░╚════╝░  ░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝		", { (short)(10 + x),(short)(y + 2 + 6) }, Color::BLACK, Color::WHITE);
	Sleep(delayTime);
}

std::wstring format(int t) {
	std::wstring time = std::to_wstring(t);
	if (t < 10) {
		time = L"0" + std::to_wstring(t);
	}
	return time;
}

void View::drawBox(COORD spot, int width, int height, Color color) {
	short x = spot.X + width;
	short y = spot.Y + height;
	for (short i = spot.X; i <= x; i++) {
		View::printCharactors(L"═", { i,spot.Y }, color, Color::WHITE);
		View::printCharactors(L"═", { i,y }, color, Color::WHITE);
	}

	for (short j = spot.Y; j <= y; j++) {
		View::printCharactors(L"║", { spot.X,j }, color, Color::WHITE);
		View::printCharactors(L"║", { x,j }, color, Color::WHITE);
	}
	View::printCharactors(L"╔", spot, color, Color::WHITE);

	View::printCharactors(L"╗", { x,spot.Y }, color, Color::WHITE);

	View::printCharactors(L"╚", { spot.X,y }, color, Color::WHITE);

	View::printCharactors(L"╝", { x,y }, color, Color::WHITE);
}

void View::drawBoxLoad(COORD spot, int width, int height, Color color) {
	short x = spot.X + width;
	short y = spot.Y + height;
	for (short i = spot.X + 1; i <= x - 1; i++) {
		View::printCharactors(L"▀", { i,spot.Y  }, Color::WHITE,color);
		View::printCharactors(L"▄", { i,y }, Color::WHITE, color);
	}

	for (short j = spot.Y; j <= y; j++) {
		View::printCharactors(L"║", { spot.X,j }, color, Color::BLACK);
		View::printCharactors(L"║", { x,j }, color, Color::BLACK);
	}
	View::printCharactors(L" ", spot, color, Color::BLACK);

	View::printCharactors(L" ", { x,spot.Y }, color, Color::BLACK);

	View::printCharactors(L" ", { spot.X,y }, color, Color::BLACK);

	View::printCharactors(L" ", { x,y }, color, Color::BLACK);
}

void View::drawGamePlayInfoBox(COORD spot, int width, int height, Color color) {
	short maxX = spot.X + width;
	short maxY = spot.Y + height;

	drawBox(spot, width, height, color);
	drawBox(spot, width, int(4), color);
	drawBox(spot, int((width - 4) / 3 + 1), int(4), color);
	drawBox(spot, int(((width - 4) / 3) * 2 + 3), int(4), color);
	drawBox(spot, int((width - 4) / 3 + 1), int((4) / 2), color);

	short x = spot.X + (width - 4) / 3 + 1;
	short y = spot.Y + (4);

	drawBox({ x ,spot.Y }, int((width - 4) / 3 + 2), int((4) / 2), color);

	x = spot.X + (((width - 4) / 3) * 2 + 3);
	drawBox({ x ,spot.Y }, int(width - 4) / 3 + 1, int((4) / 2), color);

	y = spot.Y + 4;
	drawBox({ spot.X,y }, 21 , int(height - (4)), color);
	x = spot.X;
	y = spot.Y + (4);

	View::printCharactors(L"╠", { x,y }, color, Color::WHITE);
	View::printCharactors(L"╣", { maxX,y }, color, Color::WHITE);

	y = spot.Y + (4) / 2;
	View::printCharactors(L"╠", { x,y }, color, Color::WHITE);
	View::printCharactors(L"╣", { maxX,y }, color, Color::WHITE);

	x = spot.X + (width - 4) / 3 + 1;
	y = spot.Y + ((4) / 2);

	View::printCharactors(L"╬", { x,y }, color, Color::WHITE);
	View::printCharactors(L"╦", { x,spot.Y }, color, Color::WHITE);

	y = spot.Y + (4);
	View::printCharactors(L"╩", { x,y }, color, Color::WHITE);

	x = spot.X + (((width - 4) / 3) * 2 + 3);
	y = spot.Y + (4);
	View::printCharactors(L"╦", { x,spot.Y }, color, Color::WHITE);
	View::printCharactors(L"╩", { x,y }, color, Color::WHITE);

	y = spot.Y + (4) / 2;
	View::printCharactors(L"╬", { x,y }, color, Color::WHITE);

	x = spot.X + 21;
	y = spot.Y + (4);
	View::printCharactors(L"╬", { x,y }, color, Color::WHITE);
	View::printCharactors(L"╩", { x,maxY }, color, Color::WHITE);


	x = spot.X + ((width - 4) / 3 + 1);
	View::printVerticalCenteredCharactors(
		L"SCORE",
		{ x,spot.Y,short(x + ((width - 4) / 3 + 3)),short(spot.Y + ((height / 2 - 2) / 2)) },
		short(((height / 2 - 2) / 2) / 2),
		View::Color::BLACK,
		View::Color::WHITE
	);

	View::printVerticalCenteredCharactors(
		L"X MOVE",
		{ spot.X,spot.Y,short(spot.X + ((width - 4) / 3 + 2)),short(spot.Y + ((height / 2 - 2) / 2)) },
		short(((height / 2 - 2) / 2) / 2),
		View::Color::BLACK,
		View::Color::WHITE
	);

	x = spot.X + (((width - 4) / 3) * 2 + 2);
	y = spot.Y;

	View::printVerticalCenteredCharactors(
		L"O MOVE",
		{ x,y,short(x + (width - 4) / 3 + 4),short(y + ((height / 2 - 2) / 2)) },
		short(((height / 2 - 2) / 2) / 2),
		View::Color::BLACK,
		View::Color::WHITE
	);

	x = spot.X;
	y = spot.Y + (4) - 1;

	View::printVerticalCenteredCharactors(
		L"TURN",
		{ short(x + 2),y,short(x + 21),short(y + ((height / 2 - 2) / 2))},
		2,
		View::Color::BLACK,
		View::Color::WHITE
	);

	x = spot.X + 21;
	y = spot.Y + (4) - 1;

	View::printVerticalCenteredCharactors(
		L"HISTORY",
		{ x,y,short(x + width - 21 + 2),short(y + ((height / 2 - 2) / 2)) },
		2,
		View::Color::BLACK,
		View::Color::WHITE
	);
	int moveX = 0, moveY = 0;
	int count = 0;
	x = spot.X;
	y = spot.Y + (height / 2 - 2) / 2;
	std::wstring xMoves = format(moveX);
	View::printVerticalCenteredCharactors(
		xMoves,
		{ x,y,short(x + (width - 4) / 3 + 2),short(y + ((height / 2 - 2) / 2)) },
		short(((height / 2 - 2) / 2) / 2),
		View::Color::BLACK,
		View::Color::WHITE
	);
	x = spot.X + (((width - 4) / 3) * 2 + 3);
	y = spot.Y + (height / 2 - 2) / 2;
	std::wstring yMoves = format(moveY);
	View::printVerticalCenteredCharactors(
		yMoves,
		{ x,y,short(x + (width - 4) / 3 + 2),short(y + ((height / 2 - 2) / 2)) },
		short(((height / 2 - 2) / 2) / 2),
		View::Color::BLACK,
		View::Color::WHITE
	);
}

void View::pressAnyKey(SMALL_RECT box) {
	std::wstring message = L"Press any key to continue...";
	COORD spot = View::getCenteredSpot(message, box);
	View::printCharactors(message, spot, Color::BLACK, Color::WHITE);
	InputHandle::GetKey();
}

