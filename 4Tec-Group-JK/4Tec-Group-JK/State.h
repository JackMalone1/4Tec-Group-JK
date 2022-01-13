#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <array>
#include <vector>
#include "Globals.h"

/// <summary>
/// Used to be able to check if either of the players won the game, if there was a tie or if the game is still on going
/// </summary>
enum class GameOver
{
	Tie,
	Red,
	Yellow,
	None
};

/// <summary>
/// Used to store where all of the pieces are on the current board as well as being able to check for a win on the board
/// it also has some functionality for getting all of the other pieces on a particular axis as a particular index for the evaluation function so that it 
/// is able to check how good a move is
/// </summary>
class State
{
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

