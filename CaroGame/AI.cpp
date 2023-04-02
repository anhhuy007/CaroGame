#include "AI.h"

// black is computer
// white is human

static int evaluationCount = 0;;

int AI::getWinScore() {
	return AI::WIN_SCORE;
}

double AI::evaluateBoardForWhite(Board board, bool blacksTurn) {	
	evaluationCount++;
	double blackScore = getScore(board, true, blacksTurn);
	double whiteScore = getScore(board, false, blacksTurn);

	if (blackScore == 0) blackScore = 1.0;

	return whiteScore / blackScore;
}

int AI::getScore(Board board, bool forBlack, bool blacksTurn) {
	return evaluateHorizontal(board, forBlack, blacksTurn) +
		evaluateVertical(board, forBlack, blacksTurn) +
		evaluateDiagonal(board, forBlack, blacksTurn);
}

COORD AI::calculateNextMove(int depth, AI::Board board) {
	COORD move = { -1, -1 };
	AI::EvaluatedMove bestMove = AI::searchWinningMove(board);

	if (bestMove.move.X != -1) {
		move = bestMove.move;
	}
	else {
		bestMove = minimaxSearchAB(depth, Board(board), true, -1.0, AI::getWinScore());
		if (bestMove.move.X != -1) {
			move = bestMove.move;
			std::cout << "Evaluation count: " << evaluationCount << std::endl;
			std::cout << "Best move score: " << bestMove.score << std::endl;
		}
	}

	return move;
}

AI::EvaluatedMove AI::minimaxSearchAB(int depth, Board dummyBoard, boolean max, double alpha, double beta) {
	if (depth == 0) {
		return AI::EvaluatedMove(evaluateBoardForWhite(dummyBoard, !max), { -1, -1 });
	}

	std::vector<COORD> allPossibleMoves = dummyBoard.generateMoves();
	
	if (allPossibleMoves.size() == 0) {
		return AI::EvaluatedMove(evaluateBoardForWhite(dummyBoard, !max), { -1, -1 });
	}

	AI::EvaluatedMove bestMove;
	if (max) {
		bestMove.score = -1.0;
		for (COORD move : allPossibleMoves) {
			//std::cout << "Max: " << move.X << ", " << move.Y << std::endl;
			dummyBoard.addStoneNoGUI(move.X, move.Y, false);
			
			AI::EvaluatedMove tempMove = minimaxSearchAB(depth - 1, dummyBoard, false, alpha, beta);
			
			dummyBoard.removeStoneNoGUI(move.X, move.Y);
			if ((double)(tempMove.score) > alpha) {
				alpha = (double)(tempMove.score);
			}

			if ((double)(tempMove.score) >= beta) {
				return tempMove;
			}

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
			dummyBoard.addStoneNoGUI(move.X, move.Y, true);

			AI::EvaluatedMove tempMove = minimaxSearchAB(depth - 1, dummyBoard, true, alpha, beta);

			dummyBoard.removeStoneNoGUI(move.X, move.Y);
			if ((double)(tempMove.score) < beta) {
				beta = (double)(tempMove.score);
			}

			if ((double)(tempMove.score) <= alpha) {
				return tempMove;
			}

			if ((double)(tempMove.score) < (double)(bestMove.score)) {
				bestMove = tempMove;
				bestMove.move = move;
			}
		}
	}

	return bestMove;
}

AI::EvaluatedMove AI::searchWinningMove(Board board) {
	std::vector<COORD> allPossibleMoves = board.generateMoves();
	AI::EvaluatedMove winningMove;

	for (COORD move : allPossibleMoves) {
		evaluationCount++;
		AI::Board dummyBoard = AI::Board(board);
		dummyBoard.addStoneNoGUI(move.X, move.Y, false);

		if (AI::getScore(dummyBoard, false, false) >= AI::WIN_SCORE) {
			winningMove.move = move;
			winningMove.score = AI::WIN_SCORE;
			return winningMove;
		}
	}
	
	return AI::EvaluatedMove(-1.0, { -1, -1 });
}

int AI::evaluateHorizontal(Board board, bool forBlack, bool playersTurn) {
	AI::Evaluation evaluation = AI::Evaluation(0, 2, 0);
	for (int i = 0; i < BOARD_SZ; i++) {
		for (int j = 0; j < BOARD_SZ; j++) {
			evaluateDirections(board, i, j, forBlack, playersTurn, evaluation);
		}

		evaluateDirectionAfterOnePass(evaluation, forBlack, playersTurn);
	}
	
	return evaluation.second;
}

int AI::evaluateVertical(Board board, bool forBlack, bool playersTurn) {
	AI::Evaluation evaluation = AI::Evaluation(0, 2, 0);
	
	for (int j = 0; j < BOARD_SZ; j++) {
		for (int i = 0; i < BOARD_SZ; i++) {
			evaluateDirections(board, i, j, forBlack, playersTurn, evaluation);
		}
		evaluateDirectionAfterOnePass(evaluation, forBlack, playersTurn); 
	}

	return evaluation.second;
}

int AI::evaluateDiagonal(Board board, bool forBlack, bool playersTurn) {
	AI::Evaluation evaluation = AI::Evaluation(0, 2, 0);
	// from bottom-left to top-right
	for (int k = 0; k <= 2 * (BOARD_SZ - 1); k++) {
		int iStart = max(0, k - BOARD_SZ + 1);
		int iEnd = min(BOARD_SZ - 1, k);
		for (int i = iStart; i <= iEnd; i++) {
			evaluateDirections(board, i, k - i, forBlack, playersTurn, evaluation);
		}
		evaluateDirectionAfterOnePass(evaluation, forBlack, playersTurn);
	}

	// from top-left to bottom-right
	for (int k = 1 - BOARD_SZ; k < BOARD_SZ; k++) {
		int iStart = max(0, k);
		int iEnd = min(BOARD_SZ + k - 1, BOARD_SZ - 1);
		for (int i = iStart; i <= iEnd; i++) {
			evaluateDirections(board, i, i - k, forBlack, playersTurn, evaluation);
		}
		evaluateDirectionAfterOnePass(evaluation, forBlack, playersTurn);
	}

	return evaluation.second;
}

void AI::evaluateDirections(Board board, int i, int j, bool isBot, bool botsTurn, AI::Evaluation& evaluation) {
	if (board[i][j] == (isBot ? 2 : 1)) {
		evaluation.first++;
	}
	else if (board[i][j] == 0) {
		if (evaluation.first > 0) {
			evaluation.second--;
			evaluation.third += getConsecutiveSetScore(evaluation.first, evaluation.second, isBot == botsTurn);
			evaluation.first = 0;
		}
		
		evaluation.second= 1;
	}
	else if (evaluation.first > 0) {
		evaluation.third += getConsecutiveSetScore(evaluation.first, evaluation.second, isBot == botsTurn);
		evaluation.first = 0;
		evaluation.second = 2;
	}
	else {
		evaluation.second = 2;
	}
}

void AI::evaluateDirectionAfterOnePass(AI::Evaluation& evaluation, bool isBot, bool playersTurn) {
	if (evaluation.first > 0) {
		evaluation.third += getConsecutiveSetScore(evaluation.first, evaluation.second, isBot == playersTurn);
	}
	evaluation.first = 0;
	evaluation.second = 2;
}

int AI::getConsecutiveSetScore(int count, int blocks, bool currentTurn) {
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

	return AI::WIN_SCORE * 2;
}