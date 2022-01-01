#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <array>
#include <vector>

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
	static constexpr size_t BOARD_SIZE = 16;
	static constexpr size_t NUM_BOARDS = 4;
	static constexpr size_t ROW_SIZE = 4;
	static constexpr size_t COL_SIZE = 4;
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
	bool isMoveLegal(int row, int col, int board);
	bool isMoveLegal(int index);
	GameOver checkVictory();
	std::vector<int> getLegalSpotsToPlay();
};

