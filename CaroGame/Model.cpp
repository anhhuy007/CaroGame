#include "Model.h"
#include "InputHandle.h"
#include "View.h"
#include "Control.h"
#include <stack>
using namespace std;

short curX = View::LEFT + 38;
short curY = View::TOP + 19;
bool endTurn = false;

void Model::previousMove(Model::GameInformation& game_info) {
	int n = game_info.moveHistorySize;

	if (n == 0) return;

	int preX = game_info.playerMoveHistory[n - 1].move.X;
	int preY = game_info.playerMoveHistory[n - 1].move.Y;
	int player = game_info.playerMoveHistory[n - 1].player;
	
	// pop the last from the move history 
	game_info.playerMoveHistory[n - 1] = { { 0, 0 }, 0 };
	game_info.moveHistorySize--;
	if (game_info.isFirstPlayerTurn) game_info.player1.numberOfMoves--;
	else game_info.player2.numberOfMoves--;

	int i = (preY - View::TOP - 1) / 2;
	int j = (preX - View::LEFT - 2) / 4;

	// change player turn
	game_info.isFirstPlayerTurn = !game_info.isFirstPlayerTurn;

	// mark the previous move as empty
	game_info.board[i][j] = 0;
	curX = preX; curY = preY;
	View::printCharactors(L" ", { curX, curY }, View::Color::WHITE, View::Color::WHITE);
	View::gotoXY(curX, curY);
}

Model::PlayerMove Model::getMoveHistory(GameInformation game_info, int num)
{
	PlayerMove move;
	for (int i = game_info.moveHistorySize - 1; i >= max(0, game_info.moveHistorySize - num); i--) {
		move = game_info.playerMoveHistory[i];
	}

	return move;
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
	View::gotoXY(0, 0);
	cout << "Player: " << player.name << endl;
	cout << "Turn: " << game_info.isFirstPlayerTurn << endl;

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
			Model::updateInform(game_info, { 75, 12 }, 64, 18, View::Color::BLACK);

		} 
		
		// quit game
		else if (key == L"ESC") {
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
		
		// undo move
		else if (key == L"F4") {
			previousMove(game_info);
			if (game_info.isFirstPlayerTurn != player.isFirstPlayer) endTurn = true;
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
		// player's move
		else {
			Model::makePlayerMove(key);
			View::gotoXY(curX, curY);
		}
	}
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
	View::gotoXY(0, 0);
	cout << "Draw XO";
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
	/*View::clearRectangleArea({ short(spot.X + 2),short(spot.Y + (height / 3) + 2) }, int(15), int(height - height/3 - 2));*/
	for (int i = int(spot.X + 6); i <int(spot.X + 25); i++) {
		for (int j = int(spot.Y + (height / 3) + 3); j < int(spot.Y + height ); j++) {
			View::printCharactors(L"\x2588", { (short)(i),(short)(j) }, View::Color::WHITE, View::Color::WHITE);
		}
	}
	View::drawXOart({short(spot.X + 1),short(spot.Y + 6)}, game_info.isFirstPlayerTurn);
	
	if (!game_info.isFirstPlayerTurn) {
		short x = spot.X;
		short y = spot.Y + (height / 2 - 2) / 2;
		wstring xMoves = formats(game_info.player1.numberOfMoves);
		View::printVerticalCenteredCharactors(
			xMoves,
			{ x,y,short(x + (width - 4) / 3 + 2),short(y + ((height / 2 - 2) / 2)) },
			short(((height / 2 - 2) / 2) / 2),
			View::Color::BLACK,
			View::Color::WHITE
		);
	}
	else {
		short x = spot.X + (((width - 4) / 3) * 2 + 3);
		short y = spot.Y + (height / 2 - 2) / 2;
		View::gotoXY(10, 0);
		cout << game_info.player1.numberOfMoves << " " << game_info.player2.numberOfMoves << endl;
		wstring yMoves = formats(game_info.player2.numberOfMoves);
		View::printVerticalCenteredCharactors(
			yMoves,
			{ x,y,short(x + (width - 4) / 3 + 2),short(y + ((height / 2 - 2) / 2)) },
			short(((height / 2 - 2) / 2) / 2),
			View::Color::BLACK,
			View::Color::WHITE
		); 
	}
	//Print History
	//Move getMoveHistory
	//Print Turn
}