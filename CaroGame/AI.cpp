#include "AI.h"
#include "Model.h"
// black is computer
// white is human

static int evaluationCount = 0;

int AI::getWinScore() {
	return AI::MAX_SCORE;
}

/*
	playersTurn = 1: human's turn
	playersTurn = 0: computer's turn
*/
int AI::getScore(Model::Board board, bool playerTurn) {
	evaluationCount++;
	View::clearRectangleArea({ 0, 0 }, 50, 1);
	View::gotoXY(0, 0);
	cout << "Evaluation count: " << evaluationCount << endl;
	double playerScore = AI::evaluateHorizontal(board, true, playerTurn)
		+ AI::evaluateVertical(board, true, playerTurn)
		+ AI::evaluateDiagonal(board, true, playerTurn);

	double computerScore = AI::evaluateHorizontal(board, false, playerTurn)
		+ AI::evaluateVertical(board, false, playerTurn)
		+ AI::evaluateDiagonal(board, false, playerTurn);

	/*cout << "Player score: " << playerScore << endl;
	cout << "Computer score: " << computerScore << endl;*/

	return computerScore - playerScore;
}

COORD AI::calculateNextMove(int depth, Model::Board board) {
	COORD move = { -1, -1 };
	AI::EvaluatedMove bestMove = AI::searchWinningMove(board);

	if (bestMove.move.X != -1) {
		move = bestMove.move;
	}
	else {
		bestMove = minimaxSearchAB(depth, Model::Board(board), true, AI::MIN_SCORE, AI::MAX_SCORE);
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
AI::EvaluatedMove AI::minimaxSearch(int depth, Model::Board dummyBoard, bool max) {
	if (depth == 0) {
		/*cout << "Score: " << AI::getScore(dummyBoard, !max) << endl;
		for (int i = 0; i < sz; i++) {
			for (int j = 0; j < sz; j++) {
				cout << dummyBoard[i][j] << " ";
			}
			cout << endl;
		}*/
		return AI::EvaluatedMove({ getScore(dummyBoard, !max), { -1, -1} });
	}

	std::vector<COORD> allPossibleMoves = dummyBoard.generateMoves();
	AI::EvaluatedMove bestMove;

	if (max) {
		bestMove.score = AI::MIN_SCORE;
		for (COORD move : allPossibleMoves) {
			//std::cout << "Max: " << move.X << ", " << move.Y << std::endl;
			dummyBoard.addStoneNoGUI(move.X, move.Y, true);

			AI::EvaluatedMove tempMove = AI::minimaxSearch(depth - 1, dummyBoard, false);

			dummyBoard.removeStoneNoGUI(move.X, move.Y);

			if ((double)(tempMove.score) > (double)(bestMove.score)) {
				bestMove = tempMove;
				bestMove.move = move;
			}
		}
	}
	else {
		bestMove.score = AI::MAX_SCORE;
		bestMove.move = allPossibleMoves[0];

		for (COORD move : allPossibleMoves) {
			//std::cout << "Min: " << move.X << ", " << move.Y << std::endl;
			dummyBoard.addStoneNoGUI(move.X, move.Y, false);

			AI::EvaluatedMove tempMove = minimaxSearch(depth - 1, dummyBoard, true);

			dummyBoard.removeStoneNoGUI(move.X, move.Y);

			if ((double)(tempMove.score) < (double)(bestMove.score)) {
				bestMove = tempMove;
				bestMove.move = move;
			}
		}
	}

	return bestMove;
}

AI::EvaluatedMove AI::minimaxSearchAB(int depth, Model::Board dummyBoard, bool max, double alpha, double beta) {
	if (depth == 0) {
		cout << "Score: " << AI::getScore(dummyBoard, !max) << endl;
		for (int i = 0; i < sz; i++) {
			for (int j = 0; j < sz; j++) {
				cout << dummyBoard[i][j] << " ";
			}
			cout << endl;
		}
		return AI::EvaluatedMove({ getScore(dummyBoard, !max), { -1, -1} });
	}

	std::vector<COORD> allPossibleMoves = dummyBoard.generateMoves();
	AI::EvaluatedMove bestMove;

	if (max) {
		bestMove.score = AI::MIN_SCORE;
		for (COORD move : allPossibleMoves) {
			//std::cout << "Max: " << move.X << ", " << move.Y << std::endl;
			dummyBoard.addStoneNoGUI(move.X, move.Y, true);

			AI::EvaluatedMove tempMove = AI::minimaxSearchAB(depth - 1, dummyBoard, false, alpha, beta);

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
		bestMove.score = AI::MAX_SCORE;
		bestMove.move = allPossibleMoves[0];

		for (COORD move : allPossibleMoves) {
			//std::cout << "Min: " << move.X << ", " << move.Y << std::endl;
			dummyBoard.addStoneNoGUI(move.X, move.Y, false);

			AI::EvaluatedMove tempMove = minimaxSearch(depth - 1, dummyBoard, true);

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


AI::EvaluatedMove AI::searchWinningMove(Model::Board board) {
	std::vector<COORD> allPossibleMoves = board.generateMoves();
	AI::EvaluatedMove winningMove = EvaluatedMove();

	// generate all possible moves for first player
	for (COORD move : allPossibleMoves) {
		evaluationCount++;
		Model::Board dummyBoard = Model::Board(board);

		dummyBoard.addStoneNoGUI(move.X, move.Y, false);

		// if first player wins then return winning move
		if (AI::getScore(dummyBoard, false) >= AI::WIN_SCORE) {
			winningMove.move = move;
			winningMove.score = AI::WIN_SCORE;
			return winningMove;
		}
	}

	return winningMove;
}

int AI::evaluateHorizontal(Model::Board board, bool isHuman, bool playerTurn) {
	AI::Evaluation evaluation = AI::Evaluation(0, 2, 0);
	AI::Evaluation preEvaluation = AI::Evaluation(0, 2, 0);
	for (int i = 0; i < sz; i++) {
		for (int j = 0; j < sz; j++) {
			evaluateDirections(board, i, j, isHuman, playerTurn, evaluation, preEvaluation);
			//std::cout << "Evaluation: " << i << " " << j << ": " << evaluation.third << std::endl;
		}
		preEvaluation = AI::Evaluation(0, 2, 0);
		evaluateDirectionAfterOnePass(evaluation, isHuman, playerTurn);
	}

	return evaluation.third;
}

int AI::evaluateVertical(Model::Board board, bool isHuman, bool playerTurn) {
	AI::Evaluation evaluation = AI::Evaluation(0, 2, 0);
	AI::Evaluation preEvaluation = AI::Evaluation(0, 2, 0);
	for (int j = 0; j < sz; j++) {
		for (int i = 0; i < sz; i++) {
			evaluateDirections(board, i, j, isHuman, playerTurn, evaluation, preEvaluation);
		}
		evaluateDirectionAfterOnePass(evaluation, isHuman, playerTurn);
		preEvaluation = AI::Evaluation(0, 2, 0);
	}

	return evaluation.third;
}

int AI::evaluateDiagonal(Model::Board board, bool isHuman, bool playerTurn) {
	AI::Evaluation evaluation = AI::Evaluation(0, 2, 0);
	AI::Evaluation preEvaluation = AI::Evaluation(0, 2, 0);
	// from bottom-left to top-right
	for (int k = 0; k <= 2 * (sz - 1); k++) {
		int iStart = max(0, k - sz + 1);
		int iEnd = min(sz - 1, k);
		for (int i = iStart; i <= iEnd; ++i) {
			evaluateDirections(board, i, k - i, isHuman, playerTurn, evaluation, preEvaluation);
			//cout << i << " " << k-i << " " << evaluation.first << " " << evaluation.second << " " << evaluation.third << endl;
		}
		preEvaluation = AI::Evaluation(0, 2, 0);
		evaluateDirectionAfterOnePass(evaluation, isHuman, playerTurn);
	}

	// from top-left to bottom-right
	for (int k = 1 - sz; k < sz; k++) {
		int iStart = max(0, k);
		int iEnd = min(sz + k - 1, sz - 1);
		for (int i = iStart; i <= iEnd; i++) {
			evaluateDirections(board, i, i - k, isHuman, playerTurn, evaluation, preEvaluation);
			//cout << i << " " << i - k << " " << evaluation.first << " " << evaluation.second << " " << evaluation.third << endl;

		}
		preEvaluation = AI::Evaluation(0, 2, 0);
		evaluateDirectionAfterOnePass(evaluation, isHuman, playerTurn);
	}


	return evaluation.third;
}

void AI::evaluateDirections(Model::Board board, int i, int j, bool isHuman, bool playerTurn, AI::Evaluation& evaluation, AI::Evaluation& preEvaluation) {
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
			evaluation.third += AI::getConsecutiveSetScore(evaluation.first, evaluation.second, preEvaluation.first, preEvaluation.second, isHuman == playerTurn);
			if (preEvaluation.second != 2) preEvaluation = evaluation;
			// set consecutive marks to 0
			evaluation.first = 0;
		}
		evaluation.second = 1;
	}

	// cell is occupied by opponent
	else if (evaluation.first > 0) {
		evaluation.third += AI::getConsecutiveSetScore(evaluation.first, evaluation.second, preEvaluation.first, preEvaluation.second, isHuman == playerTurn);
		evaluation.first = 0;
		evaluation.second = 2;
		preEvaluation = AI::Evaluation(0, 2, 0);
	}
	else {
		evaluation.second = 2;
	}
}

void AI::evaluateDirectionAfterOnePass(AI::Evaluation& evaluation, bool isHuman, bool playerTurn) {
	if (evaluation.first > 0) {
		evaluation.third += AI::getConsecutiveSetScore(evaluation.first, evaluation.second, 0, 2, isHuman == playerTurn);
	}
	evaluation.first = 0;
	evaluation.second = 2;
}

/*
This function will return the evaluation of a particular consecutive set of move
*/
int AI::getConsecutiveSetScore(int count, int blocks, int preCount, int preBlocks, bool currentTurn) {
	int winGuarantee = 1000000;

	if (blocks == 2 && count < 5) return 0;

	switch (count) {
	case 5:
		return AI::WIN_SCORE;
	case 4:
		if (currentTurn) return winGuarantee;
		else {
			if (blocks == 0) return winGuarantee / 4;
			else return 200;
		}
	case 3:
		// consecutive 3
		// ?XXX?
		if (preBlocks == 2) {
			if (blocks == 0) {
				if (currentTurn) return 50000;
				else return 200;
			}
			else {
				if (currentTurn) return 10;
				else return 5;
			}
		}
		// inconsecutive 
		// no block
		else if (blocks == 0) {
			if (currentTurn) {
				if (preBlocks == 1) {
					// OX_XXX_
					if (preCount > 0) return AI::WIN_SCORE;
					// O_XXX_
					else return 50000;
				}
				else if (preBlocks == 0) {
					// _XX_XXX_
					if (preCount > 0) return AI::WIN_SCORE * 2;
					// _O_XXX_
					else return 50000;
				}
			}
			else return 200;
		}
		// block in the end
		else if (blocks == 1) {
			if (currentTurn) {
				if (preBlocks == 1) {
					// OX_XXXO
					if (preCount > 0) return AI::WIN_SCORE;
					// O_XXXO
					else return 1;
				}
				else if (preBlocks == 0) {
					// _XX_XXXO
					if (preCount > 0) return AI::WIN_SCORE;
					// _O_XXXO
					else return 1;
				}
			}
			// opponent's turn
			else {
				if (preBlocks == 1) {
					// OX_XXXO
					if (preCount > 0) return 200;
					// O_XXXO
					else return 1;
				}
				else if (preBlocks == 0) {
					// _X_XXXO
					if (preCount > 0) return 200;
					// O_XXXO
					else return 1;
				}
			}
		}
		else return 5;
	case 2:
		// consecutive 2
		if (preBlocks == 2) {
			if (blocks == 0) {
				if (currentTurn) return 7;
				else return 5;
			}
			else return 3;
		}
		else if (blocks == 0) {
			if (currentTurn) {
				if (preBlocks == 1) {
					// OXX_XX_
					if (preCount > 1) return AI::WIN_SCORE;
					// OX_XX_
					else if (preCount == 1) return 200;
					// O_XX_
					else return 7;
				}
				else if (preBlocks == 0) {
					// _XX_XX_
					if (preCount > 0) return AI::WIN_SCORE;
					// _O_XX_
					else return 7;
				}
			}
			// opponent's turn
			else {
				if (preBlocks == 1) {
					// OXX_XX_
					if (preCount > 1) return 200;
					// OX_XX_
					else if (preCount == 1) return 5;
					// O_XX_
					else return 7;
				}
				else if (preBlocks == 0) {
					// _XX_XX_
					if (preCount > 0) return 200;
					// _O_XX_
					else return 5;
				}
			}
		}
		else if (blocks == 1) {
			if (currentTurn) {
				if (preBlocks == 1) {
					// OXX_XXO
					if (preCount > 1) return AI::WIN_SCORE;
					else return 1;
				}
				else if (preBlocks == 0) {
					// _XX_XXO
					if (preCount > 0) return AI::WIN_SCORE;
					// _O_XXO
					else return 1;
				}
			}
			// opponent's turn
			else {
				if (preBlocks == 1) {
					// OXX_XXO
					if (preCount > 1) return 200;
					else return 1;
				}
				else if (preBlocks == 0) {
					// _XX_XXO
					if (preCount > 0) return 200;
					else return 1;
				}
			}
		}
		else return 3;
	case 1:
		return 1;
	}

	return AI::WIN_SCORE * 2;
}