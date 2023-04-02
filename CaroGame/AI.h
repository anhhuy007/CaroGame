#pragma once
#include "View.h"
#include <iostream>
#include <vector>

namespace AI {
	const int MAX_NUMBER_OF_MOVES = 400;
	const int BOARD_SZ = View::BOARD_SIZE;
	const int WIN_SCORE = 100000000;
	
	struct Board {
		int boardData[BOARD_SZ][BOARD_SZ];
		COORD boardGUI[BOARD_SZ][BOARD_SZ];
		
		Board() {
			for (int i = 0; i < BOARD_SZ; i++) {
				for (int j = 0; j < BOARD_SZ; j++) {
					boardData[i][j] = 0;
					boardGUI[i][j] = { short(View::LEFT + 2 + 4 * j), short(View::TOP + 1 + 2 * i) };
				}
			}
		}

		Board(const Board& other) {
			for (int i = 0; i < BOARD_SZ; i++) {
				for (int j = 0; j < BOARD_SZ; j++) {
					boardData[i][j] = other.boardData[i][j];
					boardGUI[i][j] = other.boardGUI[i][j];
				}
			}
		}

		int* operator[](const int& i) {
			return boardData[i];
		}

		void removeStoneNoGUI(int x, int y) {
			boardData[x][y] = 0;
		}

		void addStoneNoGUI(int x, int y, bool black) {
			boardData[x][y] = black ? 2 : 1; 
		}

		bool addStone(int x, int y, bool black) {
			if (boardData[x][y] != 0) return false;
			
			boardData[x][y] = black ? 2 : 1; 
			View::drawMove(boardGUI[x][y].X, boardGUI[x][y].Y, boardData[x][y]);
			return true;
		}		

		// return data array 
		int** getDataArray() {
			return (int**)boardData;
		}

		std::vector<COORD> generateMoves() {
			std::vector<COORD> moveList;

			for (int i = 0; i < BOARD_SZ; i++) {
				for (int j = 0; j < BOARD_SZ; j++) {
					if (boardData[i][j] != 0) continue;

					if (i > 0) {
						if (j > 0) {
							if (boardData[i - 1][j - 1] > 0 ||
								boardData[i][j - 1] > 0) {
								COORD move = {i,j};
								moveList.push_back(move);
								continue;
							}
						}
						if (j < BOARD_SZ - 1) {
							if (boardData[i - 1][j + 1] > 0 ||
								boardData[i][j + 1] > 0) {
								COORD move = {i,j};
								moveList.push_back(move);
								continue;
							}
						}
						if (boardData[i - 1][j] > 0) {
							COORD move = {i,j};
							moveList.push_back(move);
							continue;
						}
					}
					if (i < BOARD_SZ - 1) {
						if (j > 0) {
							if (boardData[i + 1][j - 1] > 0 ||
								boardData[i][j - 1] > 0) {
								COORD move = { i,j };
								moveList.push_back(move);
								continue;
							}
						}
						if (j < BOARD_SZ - 1) {
							if (boardData[i + 1][j + 1] > 0 ||
								boardData[i][j + 1] > 0) {
								COORD move = { i,j };
								moveList.push_back(move);
								continue;
							}
						}
						if (boardData[i + 1][j] > 0) {
							COORD move = { i,j };
							moveList.push_back(move);
							continue;
						}
					}
				}
			}
			
			return moveList;
		}
	};
	struct EvaluatedMove {
		int score;
		COORD move;
		EvaluatedMove(int score, COORD move) {
			this->score = score;
			this->move = move;
		}
		EvaluatedMove() {
			score = 0;
			move = { -1, -1 };
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
	double evaluateBoardForWhite(Board board, bool blacksTurn);
	int getScore(Board board, bool forBlack, bool blacksTurn);
	COORD calculateNextMove(int depth, AI::Board board);
	AI::EvaluatedMove minimaxSearchAB(int depth, Board dummyBoard, boolean max, double alpha, double beta);
	AI::EvaluatedMove searchWinningMove(Board board);
	int evaluateHorizontal(Board board, bool forBlack, bool blacksTurn);
	int evaluateVertical(Board board, bool forBlack, bool blacksTurn);
	int evaluateDiagonal(Board board, bool forBlack, bool blackTurn);
	void evaluateDirections(Board board, int i, int j, bool isBot, bool botsTurn, AI::Evaluation& evaluations);
	void evaluateDirectionAfterOnePass(AI::Evaluation& evaluation, bool isBot, bool playersTurn);
	int getConsecutiveSetScore(int count, int blocks, bool currentTurn);
}
