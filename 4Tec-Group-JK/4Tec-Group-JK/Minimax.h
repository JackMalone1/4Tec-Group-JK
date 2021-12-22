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
	void doMove(State& state);
private:
	Move getBestMove(State state, CheckerType player);
	CheckerType m_aiColour;
};

