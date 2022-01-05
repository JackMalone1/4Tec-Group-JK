#pragma once

#include "State.h"
#include <iostream>

struct Move
{
	Move() : score{0}
	{

	}
	Move(int t_score) : score{t_score} {};

	int index;
	int score;

	int z, y, x;
};

class Minimax
{
public:
	Move doMove(State state);
private:
	Move getBestMove(State& state, CheckerType player, int depth, Move move);
	CheckerType m_aiColour;
	int evaluate(State& state, CheckerType player, Move& move);
	void evaluateGroup(CheckerType player, int& score, std::array<CheckerType, 3> group);
	bool areAllColour(CheckerType colour, std::array<CheckerType, 3> arr);
	static constexpr int MAX_DEPTH = 2;

	std::vector<Move> moves;
};

