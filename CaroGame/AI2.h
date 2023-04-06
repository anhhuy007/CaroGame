#pragma once
#include "Model.h"

namespace AI2 {
	const int MAX_NUMBER_OF_MOVES = 400;
	const int BOARD_SZ = 15;
	const int WIN_SCORE = 100000000;

	struct EvaluatedMove {
		int score = 0;
		COORD move = { -1, -1 };
		EvaluatedMove() = default;
		EvaluatedMove(int score, COORD move) {
			this->score = score;
			this->move = move;
		}
	};
	
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

	int getWinScore();
	int getScore(Model::Board board, bool playerTurn);
	COORD calculateNextMove(int depth, Model::Board board);
	AI2::EvaluatedMove minimaxSearch(int depth, Model::Board dummyBoard, bool max);
	AI2::EvaluatedMove minimaxSearchAB(int depth, Model::Board dummyBoard, bool max, double alpha, double beta);
	AI2::EvaluatedMove searchWinningMove(Model::Board board);
	int evaluateHorizontal(Model::Board board, bool isHuman, bool playerTurn);
	int evaluateVertical(Model::Board board, bool isHuman, bool playerTurn);
	int evaluateDiagonal(Model::Board board, bool isHuman, bool playerTurn);
	void evaluateDirections(Model::Board board, int i, int j, bool isHuman, bool playerTurn, AI2::Evaluation& evaluation);
	void evaluateDirectionAfterOnePass(AI2::Evaluation& evaluation, bool isHuman, bool playerTurn);
	int getConsecutiveSetScore(int count, int blocks, bool currentTurn);
}

