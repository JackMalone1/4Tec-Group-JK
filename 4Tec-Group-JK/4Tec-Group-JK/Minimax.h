#pragma once

#include "State.h"
#include <iostream>
#include <chrono>
using namespace std::chrono;

/// <summary>
/// Struct that represents a single move that the minimax algorithm could play
/// </summary>
struct Move
{
	/// <summary>
	/// sets the score to 0
	/// </summary>
	Move() : score{0}
	{

	}
	/// <summary>
	/// takes in a score to set up the move
	/// </summary>
	Move(int t_score) : score{t_score} {};

	int index;
	int score;
	int depth;
};

/// <summary>
/// Class used to work out the correct moves to play for the ai
/// It uses the minimax alogrithm to evaluate a certain board position and return the best move for the ai
/// </summary>
class Minimax
{
public:
	Move doMove(State state);
	void SetMaxDepth(int t_maxDepth);
private:
	Move getBestMove(State& state, CheckerType& player, int depth, Move& move, int alpha, int beta);
	CheckerType m_aiColour;
	int evaluate(State& state, CheckerType player, Move& move);
	void evaluateGroup(CheckerType& player, int& score, std::array<CheckerType, 3>& group);
	bool areAllColour(CheckerType& colour, std::array<CheckerType, 3>& arr);
	int MAX_DEPTH = 1;
	std::vector<Move> moves;
};

