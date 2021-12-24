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
	const int BOARD_SIZE = 16;
	const int NUM_BOARDS = 4;
	static constexpr int ROW_SIZE = 4;
	static constexpr int COL_SIZE = 4;
	GameOver checkHorizontals();
	GameOver checkVerticals();
	GameOver checkStraightDown();
	GameOver checkDiagonals();
	GameOver checkForDraw();
	GameOver checkForWinForPieces(std::array<CheckerType, ROW_SIZE> checkers);

public:
	State();
	CheckerType getPieceAtPosition(int row, int col, int board);
	void setPieceAtPosition(int row, int col, int board, CheckerType type);
	GameOver checkVictory();
};

