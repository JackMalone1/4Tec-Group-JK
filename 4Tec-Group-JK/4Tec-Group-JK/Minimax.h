#pragma once

#include "State.h"


struct Move
{
	Move()
	{

	}
	Move(int t_score) : score{t_score} {};

	int row;
	int col;
	int board;
	int score;
};

class Minimax
{
public:
	void doMove(State& state, int currentDepth);
private:
	Move getBestMove(State state, CheckerType player);
	CheckerType m_aiColour;
	Move evaluate(State state, CheckerType player);
	static constexpr int MAX_DEPTH = 10;
};

