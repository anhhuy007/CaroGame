#include "AI2.h"
#include "Model.h"
// black is computer
// white is human

static int evaluationCount = 0;

int AI2::getWinScore() {
	return AI2::WIN_SCORE;
}

/*
	playersTurn = 1: human's turn
	playersTurn = 0: computer's turn
*/
int AI2::getScore(Model::Board board, bool playerTurn) {
	evaluationCount++;
	View::clearRectangleArea({ 0, 0 }, 50, 1);
	View::gotoXY(0, 0);	
	cout << "Evaluation count: " << evaluationCount << endl;
	double playerScore = AI2::evaluateHorizontal(board, true, playerTurn) 
		+ AI2::evaluateVertical(board, true, playerTurn) 
		+ AI2::evaluateDiagonal(board, true, playerTurn);
	
	double computerScore = AI2::evaluateHorizontal(board, false, playerTurn) 
		+ AI2::evaluateVertical(board, false, playerTurn)
		+ AI2::evaluateDiagonal(board, false, playerTurn);

	/*cout << "Player score: " << playerScore << endl;
	cout << "Computer score: " << computerScore << endl;*/

	return computerScore - playerScore;
}

COORD AI2::calculateNextMove(int depth, Model::Board board) {
	COORD move = { -1, -1 };
	AI2::EvaluatedMove bestMove = AI2::searchWinningMove(board);

	if (bestMove.move.X != -1) {
		move = bestMove.move;
	}
	else {
		bestMove = minimaxSearchAB(depth, Model::Board(board), true, -100000000, AI2::getWinScore());
		if (bestMove.move.X != -1) {
			move = bestMove.move;
		}
	}

	return move;
}
/*
if max: -> computer's turn
if !max: -> human's turn
*/
AI2::EvaluatedMove AI2::minimaxSearch(int depth, Model::Board dummyBoard, bool max) {
	if (depth == 0) {
		/*cout << "Score: " << AI2::getScore(dummyBoard, !max) << endl;
		for (int i = 0; i < sz; i++) {
			for (int j = 0; j < sz; j++) {
				cout << dummyBoard[i][j] << " ";
			}
			cout << endl;
		}*/
		return AI2::EvaluatedMove({ getScore(dummyBoard, !max), { -1, -1} });
	}
	
	std::vector<COORD> allPossibleMoves = dummyBoard.generateMoves();
	AI2::EvaluatedMove bestMove;
	
	if (max) {
		bestMove.score = -100000000;
		for (COORD move : allPossibleMoves) {
			//std::cout << "Max: " << move.X << ", " << move.Y << std::endl;
			dummyBoard.addStoneNoGUI(move.X, move.Y, true);

			AI2::EvaluatedMove tempMove = AI2::minimaxSearch(depth - 1, dummyBoard, false);

			dummyBoard.removeStoneNoGUI(move.X, move.Y);

			if ((double)(tempMove.score) > (double)(bestMove.score)) {
				bestMove = tempMove;
				bestMove.move = move;
			}
		}
	}
	else {
		bestMove.score = 100000000.0;
		bestMove.move = allPossibleMoves[0];

		for (COORD move : allPossibleMoves) {
			//std::cout << "Min: " << move.X << ", " << move.Y << std::endl;
			dummyBoard.addStoneNoGUI(move.X, move.Y, false);

			AI2::EvaluatedMove tempMove = minimaxSearch(depth - 1, dummyBoard, true);

			dummyBoard.removeStoneNoGUI(move.X, move.Y);

			if ((double)(tempMove.score) < (double)(bestMove.score)) {
				bestMove = tempMove;
				bestMove.move = move;
			}
		}
	}

	return bestMove;
}

AI2::EvaluatedMove AI2::minimaxSearchAB(int depth, Model::Board dummyBoard, bool max, double alpha, double beta) {
	if (depth == 0) {
		cout << "Score: " << AI2::getScore(dummyBoard, !max) << endl;
		for (int i = 0; i < sz; i++) {
			for (int j = 0; j < sz; j++) {
				cout << dummyBoard[i][j] << " ";
			}
			cout << endl;
		}
		return AI2::EvaluatedMove({ getScore(dummyBoard, !max), { -1, -1} });
	}

	std::vector<COORD> allPossibleMoves = dummyBoard.generateMoves();
	AI2::EvaluatedMove bestMove;

	if (max) {
		bestMove.score = -100000000;
		for (COORD move : allPossibleMoves) {
			//std::cout << "Max: " << move.X << ", " << move.Y << std::endl;
			dummyBoard.addStoneNoGUI(move.X, move.Y, true);

			AI2::EvaluatedMove tempMove = AI2::minimaxSearchAB(depth - 1, dummyBoard, false, alpha, beta);

			dummyBoard.removeStoneNoGUI(move.X, move.Y);

			if ((double)(tempMove.score) > (double)(bestMove.score)) {
				bestMove = tempMove;
				bestMove.move = move;
			}

			if ((double)(tempMove.score) > alpha) {
				alpha = tempMove.score;
			}

			if (alpha >= beta) {
				break;
			}
		}
	}
	else {
		bestMove.score = 100000000.0;
		bestMove.move = allPossibleMoves[0];

		for (COORD move : allPossibleMoves) {
			//std::cout << "Min: " << move.X << ", " << move.Y << std::endl;
			dummyBoard.addStoneNoGUI(move.X, move.Y, false);

			AI2::EvaluatedMove tempMove = minimaxSearch(depth - 1, dummyBoard, true);

			dummyBoard.removeStoneNoGUI(move.X, move.Y);

			if ((double)(tempMove.score) < (double)(bestMove.score)) {
				bestMove = tempMove;
				bestMove.move = move;
			}
			
			if ((double)(tempMove.score < beta)) {
				beta = tempMove.score;
			}

			if (alpha >= beta) {
				break;
			}
		}
	}

	return bestMove;
}


AI2::EvaluatedMove AI2::searchWinningMove(Model::Board board) {
	std::vector<COORD> allPossibleMoves = board.generateMoves();
	AI2::EvaluatedMove winningMove = EvaluatedMove();

	// generate all possible moves for first player
	for (COORD move : allPossibleMoves) {
		evaluationCount++;
		Model::Board dummyBoard = Model::Board(board);

		dummyBoard.addStoneNoGUI(move.X, move.Y, false);

		// if first player wins then return winning move
		if (AI2::getScore(dummyBoard, false) >= AI2::WIN_SCORE) {
			winningMove.move = move;
			winningMove.score = AI2::WIN_SCORE;
			return winningMove;
		}
	}

	return winningMove;
}

int AI2::evaluateHorizontal(Model::Board board, bool isHuman, bool playerTurn) {
	AI2::Evaluation evaluation = AI2::Evaluation(0, 2, 0);
	for (int i = 0; i < sz; i++) {
		for (int j = 0; j < sz; j++) {
			evaluateDirections(board, i, j, isHuman, playerTurn, evaluation);
			//std::cout << "Evaluation: " << i << " " << j << ": " << evaluation.third << std::endl;
		}

		evaluateDirectionAfterOnePass(evaluation, isHuman, playerTurn);
	}

	return evaluation.third;
}

int AI2::evaluateVertical(Model::Board board, bool isHuman, bool playerTurn) {
	AI2::Evaluation evaluation = AI2::Evaluation(0, 2, 0);

	for (int j = 0; j < sz; j++) {
		for (int i = 0; i < sz; i++) {
			evaluateDirections(board, i, j, isHuman, playerTurn, evaluation);
		}
		evaluateDirectionAfterOnePass(evaluation, isHuman, playerTurn);
	}

	return evaluation.third;
}

int AI2::evaluateDiagonal(Model::Board board, bool isHuman, bool playerTurn) {
	AI2::Evaluation evaluation = AI2::Evaluation(0, 2, 0);
	// from bottom-left to top-right
	for (int k = 0; k <= 2 * (sz - 1); k++) {
		int iStart = max(0, k - sz + 1);
		int iEnd = min(sz - 1, k);
		for (int i = iStart; i <= iEnd; ++i) {
			evaluateDirections(board, i, k - i, isHuman, playerTurn, evaluation);
			//cout << i << " " << k-i << " " << evaluation.first << " " << evaluation.second << " " << evaluation.third << endl;
		}
		evaluateDirectionAfterOnePass(evaluation, isHuman, playerTurn);
	}

	// from top-left to bottom-right
	for (int k = 1 - sz; k < sz; k++) {
		int iStart = max(0, k);
		int iEnd = min(sz + k - 1, sz - 1);
		for (int i = iStart; i <= iEnd; i++) {
			evaluateDirections(board, i, i - k, isHuman, playerTurn, evaluation);
			//cout << i << " " << i - k << " " << evaluation.first << " " << evaluation.second << " " << evaluation.third << endl;

		}
		evaluateDirectionAfterOnePass(evaluation, isHuman, playerTurn);
	}


	return evaluation.third;
}

void AI2::evaluateDirections(Model::Board board, int i, int j, bool isHuman, bool playerTurn, AI2::Evaluation& evaluation) {

	if (i == 3 && j == 6) {
		int here = 1;
	}
	
	int playerMark = board[i][j];
	// check if selected player has marked in this cell
	if (playerMark == (isHuman ? 1 : 2)) {
		evaluation.first++;
	}
	
	// check if the cell is empty
	else if (playerMark == 0) {
		// check if there were any consecutive marks before this empty cell
		if (evaluation.first > 0) {
			// decrease block count
			evaluation.second--;
			// calculate the score of previous consecutive marks
			evaluation.third += AI2::getConsecutiveSetScore(evaluation.first, evaluation.second, isHuman == playerTurn);
			// set consecutive marks to 0
			evaluation.first = 0;
		}
		evaluation.second = 1;
	}

	// cell is occupied by opponent
	else if (evaluation.first > 0) {
		evaluation.third += AI2::getConsecutiveSetScore(evaluation.first, evaluation.second, isHuman == playerTurn);
		evaluation.first = 0;
		evaluation.second = 2;
	}
	else {
		evaluation.second = 2;
	}
}

void AI2::evaluateDirectionAfterOnePass(AI2::Evaluation& evaluation, bool isHuman, bool playerTurn) {
	if (evaluation.first > 0) {
		evaluation.third += AI2::getConsecutiveSetScore(evaluation.first, evaluation.second, isHuman == playerTurn);
	}
	evaluation.first = 0;
	evaluation.second = 2;
}

int AI2::getConsecutiveSetScore(int count, int blocks, bool currentTurn) {
	int winGuarantee = 1000000;

	if (blocks == 2 && count < 5) return 0;

	switch (count) {
	case 5:
		return AI2::WIN_SCORE;
	case 4:
		if (currentTurn) return winGuarantee;
		else {
			if (blocks == 0) return winGuarantee / 4;
			else return 200;
		}
	case 3:
		if (blocks == 0) {
			if (currentTurn) return 50000;
			else return 200;
		}
		else {
			if (currentTurn) return 10;
			else return 5;
		}
	case 2:
		if (blocks == 0) {
			if (currentTurn) return 7;
			else return 5;
		}
		else return 3;
	case 1:
		return 1;
	}

	return AI2::WIN_SCORE * 2;
}