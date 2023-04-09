#include "Model.h"
#include "InputHandle.h"
#include "View.h"
#include "Control.h"
#include "AI.h"
using namespace std;

short curX = View::LEFT + 38;
short curY = View::TOP + 19;
bool endTurn = false;

void Model::previousMove(Model::GameInformation& game_info) {
	int n = game_info.moveHistorySize;

	if (n == 0) return;

	short preX = game_info.playerMoveHistory[n - 1].move.X;
	short preY = game_info.playerMoveHistory[n - 1].move.Y;
	int player = game_info.playerMoveHistory[n - 1].player;
	game_info.updateDisplayedHistory({ { preX, preY, player }, true } );
	
	// pop the last from the move history 
	game_info.playerMoveHistory[n - 1] = { { 0, 0 }, 0 };
	game_info.moveHistorySize--;
	if (game_info.isFirstPlayerTurn) game_info.player2.numberOfMoves--;
	else game_info.player1.numberOfMoves--;
	game_info.totalStep++;
	// change player turn
	game_info.isFirstPlayerTurn = !game_info.isFirstPlayerTurn;

	int i = (preY - View::TOP - 1) / 2;
	int j = (preX - View::LEFT - 2) / 4;

	// mark the previous move as empty
	game_info.board[i][j] = 0;
	curX = preX; curY = preY;
	View::printCharactors(L" ", { curX, curY }, View::Color::WHITE, View::Color::WHITE);
	View::gotoXY(curX, curY);
	Model::updateInform(game_info, { 75, 13 }, 64, 15, View::Color::BLACK);
}

void Model::makePlayerMove(std::wstring key) {	
	// move up
	if (key == L"UP") {
		if (curY > View::TOP + 1) {
			curY -= 2;
		}
		else {
			curY = View::BOT - 1;
		}
	}

	// move down
	else if (key == L"DOWN") {
		if (curY < View::BOT - 1) {
			curY += 2;
		}
		else {
			curY = View::TOP + 1;
		}
	}

	// move left
	else if (key == L"LEFT") {
		if (curX > View::LEFT + 2) {
			curX -= 4;
		}
		else {
			curX = View::RIGHT - 2;
		}
	}

	// move right
	else if (key == L"RIGHT") {
		if (curX < View::RIGHT - 2) {
			curX += 4;
		}
		else {
			curX = View::LEFT + 2;
		}
	}
}

void Model::markPlayerMove(COORD spot, int playerNum, Model::GameInformation &game_info) {
	int i = (spot.Y - View::TOP - 1) / 2;
	int j = (spot.X - View::LEFT - 2) / 4;
	
	// if the board is empty
	if (game_info.board[i][j] == 0) {
		// mark move
		game_info.board[i][j] = playerNum;
		// add move to history
		game_info.playerMoveHistory[game_info.moveHistorySize] = { spot, playerNum };
		game_info.moveHistorySize++; 
		game_info.totalStep++;
		game_info.updateDisplayedHistory({ { spot.X, spot.Y, playerNum }, false });
		// show move on the game board
		wstring playerMark = playerNum == 1 ? L"X" : L"O";
		View::printCharactors(playerMark, { curX, curY }, View::Color::BLACK, View::Color::WHITE);
		if (game_info.isFirstPlayerTurn) {
			game_info.player1.numberOfMoves++;
		}
		else {
			game_info.player2.numberOfMoves++;
		}
		// change player turn
		game_info.isFirstPlayerTurn = !game_info.isFirstPlayerTurn;
		endTurn = true;
	}
}

void Model::playerTurn(Model::Player player, Model::GameInformation& game_info) {
	View::gotoXY(curX, curY);
	wstring key;
	endTurn = false;

	while (!endTurn) {
		key = InputHandle::Get();
		// if is a player move
		if (key == L"ENTER") {
			// mark the move on the board and update game's information
			int playerNum = game_info.isFirstPlayerTurn ? 1 : 2;
			Model::markPlayerMove({ curX, curY }, playerNum, game_info);
			Model::updateInform(game_info, { 75, 13 }, 64, 15, View::Color::BLACK);

		} 
		
		// quit game
		else if (key == L"F1") {
			// show a dialog that ask user to confirm to exit
			// get current screen's information before display confirm dialog
			PCHAR_INFO buffer = View::getScreenBuffer();
			
			system("cls");
			View::confirmDialog(
				L"Your current game will not be saved. Are you sure you want to exit?",
				{ 25, 10 },
				[]() -> void {
					// if click YES then return menu
					endTurn = true;
					Control::quitGame();
				},
				[&]() -> void {
					// continue game
					// restore screen's information
					View::writeScreenBuffer(buffer);
				}
			);
		}

		// save game
		else if (key == L"F2") {
			// save current screen buffers
			PCHAR_INFO buffer = View::getScreenBuffer();
			system("cls");

			// show a dialog that ask user to confirm to save
			View::confirmDialog(
				L"Are you sure you want to save this game?",
				{ 40, 10 },
				[&]() -> void {
					// if click YES then return menu
					system("cls");
					Control::saveGame(game_info);
					// restore screen's information
					View::writeScreenBuffer(buffer);
				},
				[&]() -> void {
					// continue game
					// restore screen's information
					View::writeScreenBuffer(buffer);
				}
			);
		}

		else if (key == L"F3") {
			// show a dialog that ask user to confirm to exit
			// get current screen's information before display confirm dialog
			PCHAR_INFO buffer = View::getScreenBuffer();

			system("cls");
			View::confirmDialog(
				L"Do you want to save this game before loading another game?",
				{ 35, 10 },
				[&]() -> void {
					// if click YES then return menu
					system("cls");
					endTurn = true;
					Control::saveGame(game_info);
					// restore screen's information
					Control::loadGame();
				},
				[&]() -> void {
					// continue game
					// restore screen's information
					system("cls");
					Control::loadGame();
				}
				);
		}

		// undo move
		else if (key == L"F4") {
			// if two players mode then undo 1 time
			if (game_info.gameMode.isPlayWithHuman) {
				previousMove(game_info);
				if (game_info.isFirstPlayerTurn != player.isFirstPlayer) endTurn = true;
			}
			else {
				// if one player mode then undo 2 times
				previousMove(game_info);
				previousMove(game_info);
				if (game_info.isFirstPlayerTurn != player.isFirstPlayer) endTurn = true;
			}
			
		}
		
		// player's move
		else {
			Model::makePlayerMove(key);
			View::gotoXY(curX, curY);
		}
	}
}

void Model::computerTurn(Model::Player player, Model::GameInformation& game_info) {
	COORD move = AI::calculateNextMove(2, game_info.board);

	COORD spot = game_info.board.getSpot(move.X, move.Y);
	curX = spot.X;
	curY = spot.Y;
	markPlayerMove({curX, curY}, 2, game_info);
	updateInform(game_info, { 75, 13 }, 64, 15, View::Color::BLACK);
}

// 0: game not ended
// 1 : player 1 win
// 2 : player 2 win
// 3 : draw
// if game ended, return a pair of result and a vector of coordinates of winning line
pair<int, vector<COORD>> Model::checkResult(int player, int board[sz][sz]) {
	vector<COORD> winPos;
	int count = 0;
	for (int i = 0; i < View::BOARD_SIZE; i++) {
		for (int j = 0; j < View::BOARD_SIZE; j++) {
			if (board[i][j] != 0) count++;

			if (board[i][j] == player) {
				if (Model::checkRow(i, j, player, board) == true) {
					for (int k = 0; k < 5; k++) {
						short x = View::LEFT + 2 + 4 * (j + k);
						short y = View::TOP + 1 + 2 * i;
						winPos.push_back({ x, y });
					}
					return { player, winPos };
				}
				else if (Model::checkCol(i, j, player, board) == true) {
					for (int k = 0; k < 5; k++) {
						short x = View::LEFT + 2 + 4 * j;
						short y = View::TOP + 1 + 2 * (i + k);
						winPos.push_back({ x, y });
					}
					return { player, winPos };
				}
				else if (Model::checkMainDiagonal(i, j, player, board) == true) {
					for (int k = 0; k < 5; k++) {
						short x = View::LEFT + 2 + 4 * (j + k);
						short y = View::TOP + 1 + 2 * (i + k);
						winPos.push_back({ x, y });
					}
					return { player, winPos };
				}
				else if (Model::checkSubDiagonal(i, j, player, board) == true) {
					for (int k = 0; k < 5; k++) {
						short x = View::LEFT + 2 + 4 * (j + k);
						short y = View::TOP + 1 + 2 * (i - k);
						winPos.push_back({ x, y });
					}
					return { player, winPos };
				}
			}
		}
	}

	int result = count == View::BOARD_SIZE * View::BOARD_SIZE ? 3 : 0;
	return { result, winPos };	
}

bool Model::checkRow(int i, int j, int player, int board[sz][sz]) {
	if (j + 4 > View::BOARD_SIZE) {
		return false;
	}

	return (board[i][j] == player &&
		board[i][j + 1] == player &&
		board[i][j + 2] == player &&
		board[i][j + 3] == player &&
		board[i][j + 4] == player
		);
}

bool Model::checkCol(int i, int j, int player, int board[sz][sz]) {
	if (i + 4 > View::BOARD_SIZE) {
		return false;
	}

	return (board[i][j] == player &&
		board[i + 1][j] == player &&
		board[i + 2][j] == player &&
		board[i + 3][j] == player &&
		board[i + 4][j] == player
		);
}

bool Model::checkMainDiagonal(int i, int j, int player, int board[sz][sz]) {
	if (i + 4 > View::BOARD_SIZE || j + 4 > View::BOARD_SIZE) {
		return false;
	}

	return (board[i][j] == player &&
		board[i + 1][j + 1] == player &&
		board[i + 2][j + 2] == player &&
		board[i + 3][j + 3] == player &&
		board[i + 4][j + 4] == player
		);
}

bool Model::checkSubDiagonal(int i, int j, int player, int board[sz][sz]) {

	if (i - 4 < 0 || j + 4 > View::BOARD_SIZE) {
		return false;
	}

	return (board[i][j] == player &&
		board[i - 1][j + 1] == player &&
		board[i - 2][j + 2] == player &&
		board[i - 3][j + 3] == player &&
		board[i - 4][j + 4] == player
		);
}

void Model::drawXO(Model::Board board) {
	for (int i = 0; i < View::BOARD_SIZE; i++) {
		for (int j = 0; j < View::BOARD_SIZE; j++) {
			if (board[i][j] == 0) continue;
			COORD spot = board.getSpot(i, j);
			View::printCharactors(
				board[i][j] == 1 ? L"X" : L"O",
				{ spot.X , spot.Y },
				View::Color::BLACK,
				View::Color::WHITE
			);
		}
	}
}

wstring formats(int t) {
	wstring time = to_wstring(t);
	if (t < 10) {
		time = L"0" + to_wstring(t);
	}
	return time;
}

void Model::updateInform(GameInformation &game_info, COORD spot, int width, int height, View::Color color) {
	for (int i = int(spot.X + 1); i <int(spot.X + 20); i++) {
		for (int j = int(spot.Y + 6); j < int(spot.Y + height); j++) {
			View::printCharactors(L"\x2588", { (short)(i),(short)(j) }, View::Color::WHITE, View::Color::WHITE);
		}
	}	
	View::drawXOart({short(spot.X - 6),short(spot.Y + 4) }, game_info.isFirstPlayerTurn);

	// update total move of player
	int moveX = game_info.player1.numberOfMoves;
	short x = spot.X;
	short y = spot.Y + (height / 2 - 2) / 2;
	wstring xMoves = formats(moveX);
	View::printVerticalCenteredCharactors(
		xMoves,
		{ x,y,short(x + (width - 4) / 3 + 2),short(y + ((height / 2 - 2) / 2)) },
		short(((height / 2 - 2) / 2) / 2),
		View::Color::BLACK,
		View::Color::WHITE
	);
	x = spot.X + (((width - 4) / 3) * 2 + 3);
	y = spot.Y + (height / 2 - 2) / 2;
	int moveY = game_info.player2.numberOfMoves;
	wstring yMoves = formats(moveY);
	View::printVerticalCenteredCharactors(
		yMoves,
		{ x,y,short(x + (width - 4) / 3 + 2),short(y + ((height / 2 - 2) / 2)) },
		short(((height / 2 - 2) / 2) / 2),
		View::Color::BLACK,
		View::Color::WHITE
	);
	x = spot.X + 44;
	y = spot.Y + 7;
	for (int i = int(spot.X + 22); i <int(spot.X + width); i++) {
		for (int j = int(spot.Y + 6); j < int(spot.Y + height); j++) {
			View::printCharactors(L"\x2588", { (short)(i),(short)(j) }, View::Color::WHITE, View::Color::WHITE);
		}
	}
	
	int totalMoves = game_info.player1.numberOfMoves + game_info.player2.numberOfMoves;
	int idx = game_info.totalStep;
	for (int i = 3, cnt = 0; i >= 0; i--, cnt++) {
		if (game_info.displayedHistory[i].playerMove.move.X == -1) continue;

		wstring history = L" " + to_wstring(idx);
		idx--;
		history += L". ";
		PlayerMove move = game_info.displayedHistory[i].playerMove;
		if (move.player == 1) {
			string player_name = game_info.player1.name;
			wstring name(player_name.begin(), player_name.end());
			history += name;
			history += L"(X)";
		}
		else {
			string player_name = game_info.player2.name;
			wstring name(player_name.begin(), player_name.end());
			history += name;
			history += L"(O)";
		}
		if (game_info.displayedHistory[i].isPrevious) {
			history += L": Undo";
		}
		char character = char((move.move.X - 6) / 4 + 97);
		string tmp_string(1, character);
		wstring moveX(tmp_string.begin(), tmp_string.end());
		wstring moveY = to_wstring(int(16 - (move.move.Y - 1) / 2));
		history += L" - (" + moveY + L"," + moveX + L")" + L" ";
		x = short(spot.X + 22 + (width-22)/2 - (history.length() / 2));
		View::printCharactors(history, { x, short(y + cnt * 2) }, View::Color::BLACK, View::Color::WHITE);
	}
}