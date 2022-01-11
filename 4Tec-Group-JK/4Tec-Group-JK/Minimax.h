#pragma once

#include "State.h"
#include <iostream>
#include <chrono>
using namespace std::chrono;

/// <summary>
/// 
/// </summary>
struct Move
{
	/// <summary>
	/// 
	/// </summary>
	Move() : score{0}
	{

	}
	/// <summary>
	/// 
	/// </summary>
	Move(int t_score) : score{t_score} {};

	int index;
	int score;
	int depth;
};

/// <summary>
/// 
/// </summary>
class Minimax
{
public:
	Move doMove(State state);
private:
	Move getBestMove(State& state, CheckerType& player, int depth, Move& move, int alpha, int beta);
	CheckerType m_aiColour;
	int evaluate(State& state, CheckerType player, Move& move);
	void evaluateGroup(CheckerType& player, int score, std::array<CheckerType, 3>& group);
	bool areAllColour(CheckerType& colour, std::array<CheckerType, 3>& arr);
	static constexpr int MAX_DEPTH = 4;
	std::vector<Move> moves;
};

