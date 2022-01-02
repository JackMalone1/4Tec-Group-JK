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
	static constexpr size_t BOARD_SIZE = 16;
	static constexpr size_t NUM_BOARDS = 4;
	static constexpr size_t ROW_SIZE = 4;
	static constexpr size_t COL_SIZE = 4;
private:
	std::vector<CheckerType> m_pieces;
	std::array<int, 4> m_diagonalIndices = { 0,21,42,63 };
	std::array<int, 4> m_oppositeDiagonalIndices = { 3,22,41,60 };
	std::array<int, 16> m_corners = { 0,3,12,15,16,19,28,31,32,35,44,47,48,51,60,63 };
private:

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
	CheckerType getPieceAtPosition(int index);
	void setPieceAtPosition(int index, CheckerType type);
	bool isMoveLegal(int row, int col, int board);
	bool isMoveLegal(int index);
	GameOver checkVictory();
	std::vector<int> getLegalSpotsToPlay();
	std::array<CheckerType, 3> getAllOnSameRow(int index);
	std::array<CheckerType, 3> getAllOnSameColumn(int index);
	std::array<CheckerType, 3> getAllStraightDown(int index);
	std::array<CheckerType, 3> getAllOnSameBoardDiagonal(int index);
	std::array<CheckerType, 3> getAllOnSameDiagonal(int index);
	bool isOnBoardDiagonal(int index);
	bool isOnDiagonal(int index);
	bool isCorner(int index);
	std::vector<CheckerType> getPieces();
};

