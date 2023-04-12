#include "Model.h"
#include "InputHandle.h"
#include "View.h"
#include "Control.h"
#include "AI.h"

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
	game_info.curX = preX; game_info.curY = preY;
	View::printCharactors(L" ", { game_info.curX, game_info.curY }, View::Color::WHITE, View::Color::WHITE);
	View::gotoXY(game_info.curX, game_info.curY);
	Model::updateInform(game_info, { 75, 13 }, 64, 15, View::Color::BLACK);
}

void Model::makePlayerMove(std::wstring key, Model::GameInformation& game_info) {
	// move up
	if (key == L"UP" || key == L"w") {
		if (game_info.curY > View::TOP + 1) {
			game_info.curY -= 2;
		}
		else {
			game_info.curY = View::BOT - 1;
		}
	}

	// move down
	else if (key == L"DOWN" || key == L"s") {
		if (game_info.curY < View::BOT - 1) {
			game_info.curY += 2;
		}
		else {
			game_info.curY = View::TOP + 1;
		}
	}

	// move left
	else if (key == L"LEFT" || key == L"a") {
		if (game_info.curX > View::LEFT + 2) {
			game_info.curX -= 4;
		}
		else {
			game_info.curX = View::RIGHT - 2;
		}
	}

	// move right
	else if (key == L"RIGHT" || key == L"d") {
		if (game_info.curX < View::RIGHT - 2) {
			game_info.curX += 4;
		}
		else {
			game_info.curX = View::LEFT + 2;
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
		if (game_info.isFirstPlayerTurn) {
			game_info.player1.numberOfMoves++;
			View::printCharactors(L"X", { spot.X, spot.Y }, View::Color::RED, View::Color::WHITE);
		}
		else {
			game_info.player2.numberOfMoves++;
			View::printCharactors(L"O", { spot.X, spot.Y }, View::Color::BLUE, View::Color::WHITE);
		}
		// change player turn
		game_info.isFirstPlayerTurn = !game_info.isFirstPlayerTurn;
		endTurn = true;
	}
}

void Model::playerTurn(Model::Player player, Model::GameInformation& game_info) {
	View::gotoXY(game_info.curX, game_info.curY);
	std::wstring key;
	endTurn = false;

	while (!endTurn) {
		key = InputHandle::GetKey();
		// if is a player move
		if (key == L"ENTER") {
			// mark the move on the board and update game's information
			int playerNum = game_info.isFirstPlayerTurn ? 1 : 2;
			Model::markPlayerMove({ game_info.curX, game_info.curY }, playerNum, game_info);
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
					Control::ReturnMenu();
					},
				[&]() -> void {
					// if click NO then continue game
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
					// if click YES then save game
					system("cls");
					Control::SaveGame(game_info);
					// restore screen's information
					View::writeScreenBuffer(buffer);
				},
				[&]() -> void {
					// if click NO then continue game
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
					Control::SaveGame(game_info);
					// restore screen's information
					Control::LoadGame();
				},
				[&]() -> void {
					// if click NO then continue game
					// restore screen's information
					system("cls");
					Control::LoadGame();
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
			Model::makePlayerMove(key, game_info);
			View::gotoXY(game_info.curX, game_info.curY);
		}
	}
}

void Model::computerTurn(Model::Player player, Model::GameInformation& game_info) {
	COORD move = AI::findNextMove(2	, game_info.board);

	COORD spot = game_info.board.getSpot(move.X, move.Y);
	game_info.curX = spot.X;
	game_info.curY = spot.Y;
	markPlayerMove({game_info.curX, game_info.curY}, 2, game_info);
	updateInform(game_info, { 75, 13 }, 64, 15, View::Color::BLACK);
}

// 0: game not ended
// 1 : player 1 win
// 2 : player 2 win
// 3 : draw
// if game ended, return a pair of result and a vector of coordinates of winning line
std::pair<int, std::vector<COORD>> Model::checkResult(int player, int board[sz][sz]) {
	std::vector<COORD> winPos;
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

// format number to two digits
std::wstring formats(int t) {
	std::wstring time = std::to_wstring(t);
	if (t < 10) {
		time = L"0" + std::to_wstring(t);
	}
	return time;
}

void Model::updateInform(GameInformation &game_info, COORD spot, int width, int height, View::Color color) {
	for (int i = int(spot.X + 1); i <int(spot.X + 20); i++) {
		for (int j = int(spot.Y + 6); j < int(spot.Y + height); j++) {
			View::printCharactors(L"\x2588", { (short)(i),(short)(j) }, View::Color::WHITE, View::Color::WHITE);
		}
	}	

	// display current turn: X or O
	View::drawXOart({short(spot.X - 6),short(spot.Y + 4) }, game_info.isFirstPlayerTurn);

	// update total move of player
	int moveX = game_info.player1.numberOfMoves;
	short x = spot.X;
	short y = spot.Y + (height / 2 - 2) / 2;
	std::wstring xMoves = formats(moveX);
	// display total move of player X
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
	std::wstring yMoves = formats(moveY);
	// display total move of player Y
	View::printVerticalCenteredCharactors(
		yMoves,
		{ x,y,short(x + (width - 4) / 3 + 2),short(y + ((height / 2 - 2) / 2)) },
		short(((height / 2 - 2) / 2) / 2),
		View::Color::BLACK,
		View::Color::WHITE
	);

	// display game score
	std::wstring score = std::to_wstring(game_info.player1.score) + L" - " + std::to_wstring(game_info.player2.score);
	View::printVerticalCenteredCharactors(
		score,
		{ short(spot.X + ((width - 4) / 3 + 1)),short(spot.Y + 2),short((spot.X + ((width - 4) / 3 + 1)) + ((width - 4) / 3 + 3)),short(spot.Y + 4) },
		short(((height / 2 - 2) / 2) / 2),
		View::Color::BLACK,
		View::Color::WHITE
	);
	
	// clear history table
	int w = int(spot.X + width) - int(spot.X + 22);
	int h = int(spot.Y + height) - int(spot.Y + 6);
	View::clearRectangleArea({ short(spot.X + 22),short(spot.Y + 6) }, w, h);
	// display game history
	x = spot.X + 44;
	y = spot.Y + 7;
	int totalMoves = game_info.player1.numberOfMoves + game_info.player2.numberOfMoves;
	int idx = game_info.totalStep;
	for (int i = 3, cnt = 0; i >= 0; i--, cnt++) {
		if (game_info.displayedHistory[i].playerMove.move.X == -1) continue;

		std::wstring history = L" " + std::to_wstring(idx);
		idx--;
		history += L". ";
		PlayerMove move = game_info.displayedHistory[i].playerMove;
		if (move.player == 1) {
			std::string player_name = game_info.player1.name;
			std::wstring name(player_name.begin(), player_name.end());
			history += name;
			history += L"(X)";
		}
		else {
			std::string player_name = game_info.player2.name;
			std::wstring name(player_name.begin(), player_name.end());
			history += name;
			history += L"(O)";
		}
		if (game_info.displayedHistory[i].isPrevious) {
			history += L": Undo";
		}
		char character = char((move.move.X - 6) / 4 + 97);
		std::string tmp_string(1, character);
		std::wstring moveX(tmp_string.begin(), tmp_string.end());
		std::wstring moveY = std::to_wstring(int(16 - (move.move.Y - 1) / 2));
		history += L" - (" + moveY + L"," + moveX + L")" + L" ";
		x = short(spot.X + 22 + (width-22)/2 - (history.length() / 2));
		View::printCharactors(history, { x, short(y + cnt * 2) }, View::Color::BLACK, View::Color::WHITE);
	}
}