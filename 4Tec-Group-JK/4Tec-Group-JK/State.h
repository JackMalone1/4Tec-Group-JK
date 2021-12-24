#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <array>

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

	GameOver checkHorizontals();
	GameOver checkVerticals();
	GameOver checkStraightDown();
	GameOver checkDiagonals();
	GameOver checkForDraw();
	GameOver checkForWinForPieces(std::array<CheckerType, 4> checkers);
public:
	State();
	CheckerType getPieceAtPosition(int row, int col, int board);
	void setPieceAtPosition(int row, int col, int board, CheckerType type);
	GameOver checkVictory();
};

