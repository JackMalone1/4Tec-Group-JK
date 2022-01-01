#pragma once

#include "State.h"


struct Move
{
	Move()
	{

	}
	Move(int t_score) : score{t_score} {};

	int index;
	int score;
};

class Minimax
{
public:
	Move doMove(State& state, int currentDepth);
private:
	Move getBestMove(State state, CheckerType player);
	CheckerType m_aiColour;
	int evaluate(State state, CheckerType player, Move move);
	void evaluateGroup(CheckerType player, int& score, std::array<CheckerType, 3> group);
	bool areAllColour(CheckerType colour, std::array<CheckerType, 3> arr);
	static constexpr int MAX_DEPTH = 10;
};

