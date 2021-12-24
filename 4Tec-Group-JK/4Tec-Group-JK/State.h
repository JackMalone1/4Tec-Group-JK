#pragma once

#include <SFML/Graphics.hpp>
#include <map>

enum class CheckerType
{
	None = 0,
	Yellow,
	Red
};

enum class GameOver
{
	Tie,
	Red,
	Yellow,
	None
};

class State
{
private:
	std::vector<CheckerType> m_pieces;
public:
	State();
	CheckerType getPieceAtPosition(int row, int col, int board);
	void setPieceAtPosition(int row, int col, int board, CheckerType type);
	GameOver checkVictory();
};

