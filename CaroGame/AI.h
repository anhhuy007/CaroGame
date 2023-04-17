#pragma once
#include "Model.h"

namespace AI {
	const int MAX_SCORE = 100000000;
	const int MIN_SCORE = -100000000;

	// store the information of a move with evaluated score
	struct EvaluatedMove {
		int score = 0;
		COORD move = { -1, -1 };
		EvaluatedMove() = default;
		EvaluatedMove(int score, COORD move) {
			this->score = score;
			this->move = move;
		}
	};

	// store the information of a consecutive set of moves
	struct Evaluation {
		int first; // -> consecutive count
		int second; // -> block count
		int third; // -> score

		Evaluation(int first, int second, int third) {
			this->first = first;
			this->second = second;
			this->third = third;
		}
	};

	// evaluate the score of a particular player from current board
	int getScore(Model::Board board, bool playerTurn);
	
	// find next intelligent move for AI
	COORD findNextMove(int depth, Model::Board board);
	
	// minimax algorithm with alpha-beta pruning to find the best move
	AI::EvaluatedMove minimaxSearchAB(
		int depth, 
		Model::Board dummyBoard, 
		bool max, 
		double alpha, 
		double beta
	);
	
	// check if there is any winning move for player
	AI::EvaluatedMove findWinningMove(Model::Board board);
	
	// three functions to evaluate the score in a particular direction
	int evaluateHorizontal(Model::Board board, bool isHuman, bool playerTurn);
	int evaluateVertical(Model::Board board, bool isHuman, bool playerTurn);
	int evaluateDiagonal(Model::Board board, bool isHuman, bool playerTurn);

	// evaluate the score of all consecuive sets of moves in a particular direction
	void evaluateDirections(
		Model::Board board,
		int i,
		int j,
		bool isHuman,
		bool playerTurn,
		AI::Evaluation& evaluation,
		AI::Evaluation& preEvaluation
	);
	void evaluateDirectionAfterOnePass(AI::Evaluation& evaluation, bool isHuman, bool playerTurn);

	// return the evaluation of a consecutive set of moves
	int evaluateConsecutiveSetScore(int count, int blocks, int preCount, int preBlocks, bool currentTurn);
}

