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
	GameOver checkForDraw()const;
	GameOver checkForWinForPieces(std::array<CheckerType, ROW_SIZE>& checkers);
public:
	State();
	CheckerType getPieceAtPosition(int row, int col, int board) const;
	void setPieceAtPosition(int row, int col, int board, CheckerType type);
	CheckerType getPieceAtPosition(int index)const;
	void setPieceAtPosition(int index, CheckerType type);
	bool isMoveLegal(int row, int col, int board)const;
	bool isMoveLegal(int index)const;
	GameOver checkVictory();
	std::vector<int> getLegalSpotsToPlay()const;
	std::array<CheckerType, 3> getAllOnSameRow(int index)const;
	std::array<CheckerType, 3> getAllOnSameColumn(int index)const;
	std::array<CheckerType, 3> getAllStraightDown(int index)const;
	std::array<CheckerType, 3> getAllOnSameBoardDiagonal(int index)const;
	std::array<CheckerType, 3> getAllOnSameDiagonal(int index)const;
	bool isOnBoardDiagonal(int index)const;
	bool isOnDiagonal(int index)const;
	bool isCorner(int index)const;
	std::vector<CheckerType> getPieces()const;
};

