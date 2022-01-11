#include "State.h"
#include <iostream>

/// <summary>
/// Goes through all of the horizontals on each of the boards individually and checks if there is a win on any of them.
/// It also checks all of the horizontals between the boards and checks if there is a win on any of those horizontals.
/// </summary>
/// <returns>Returns if the Red player won, the Yellow player won or if there was no win </returns>
GameOver State::checkHorizontals()
{
	int offset = ROW_SIZE;
	for (int initialPosition = 0; initialPosition <= (BOARD_SIZE * NUM_BOARDS) - ROW_SIZE; initialPosition += offset)
	{
		std::array<CheckerType, ROW_SIZE> arr;
		int index = 0;
		for (int i = initialPosition; i < ROW_SIZE + initialPosition && index < arr.size(); ++i)
		{
			arr.at(index) = m_pieces.at(i);
			index++;
		}
		GameOver state = checkForWinForPieces(arr);
		if (state != GameOver::None) return state;
	}

	//horizontals between boards
	for (int i = 0; i < BOARD_SIZE; i += ROW_SIZE)
	{
		std::array<CheckerType, ROW_SIZE> arr;
		for (int j = 0; j < ROW_SIZE; j++)
		{
			arr.at(j) = m_pieces.at(i + ((BOARD_SIZE + 1) * j));
		}
		GameOver state = checkForWinForPieces(arr);
		if (state != GameOver::None) return state;
	}
	return GameOver::None;
}

/// <summary>
/// Goes through all of the verticals for each of the boards and check if either of the players won there.
/// It also checks the verticals between each of the boards
/// </summary>
/// <returns>Returns if the Red player won, the Yellow player won or if there was no win </returns>
GameOver State::checkVerticals()
{
	int index = 0;
	//check for verticals on each column for a specific board and then go on to the next board and check all of the verticals there
	while (index < (BOARD_SIZE * NUM_BOARDS) - 1)
	{
		for (int i = index; i < (index + ROW_SIZE); ++i)
		{
			std::array<CheckerType, COL_SIZE> arr;
			for (int j = 0; j < COL_SIZE; ++j)
			{
				int currentIndex = i + (j * COL_SIZE);
				if (currentIndex >= m_pieces.size()) currentIndex = m_pieces.size() - 1;
				arr.at(j) = m_pieces.at(currentIndex);
			}
			GameOver state = checkForWinForPieces(arr);
			if (state != GameOver::None) return state;
		}
		index += BOARD_SIZE;//skip past 3 rows so this should be equal to 13 to get to the next board
	}
	for (int i = 0; i < ROW_SIZE; ++i)
	{
		std::array<CheckerType, ROW_SIZE> arr;
		for (int j = 0; j < ROW_SIZE; ++j)
		{
			int index = i + (j * (BOARD_SIZE + ROW_SIZE));
			arr.at(j) = m_pieces.at(index);
		}
		GameOver state = checkForWinForPieces(arr);
		if (state != GameOver::None) return state;
	}
	return GameOver::None;
}

/// <summary>
/// checks for wins for straight down between all of the boards
/// this just needs to go through the entire first board and then check the next 3 that are exactly one board after it to see if they are all of the same type or not
/// </summary>
/// <returns>Returns if the Red player won, the Yellow player won or if there was no win </returns>
GameOver State::checkStraightDown()
{
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		std::array<CheckerType, ROW_SIZE> arr;
		for (int j = 0; j < 4; ++j)
		{
			int index = i + (j * 16);
			arr.at(j) = m_pieces.at(index);
		}
		GameOver state = checkForWinForPieces(arr);
		if (state != GameOver::None) return state;
	}
	return GameOver::None;
}

/// <summary>
/// Checks for wins on each of the diagonals on each board individually. This results in two checks per board for the diagonal going to the left and another check for the diagonal going to the right
/// This will also check the other two diagonals that go between all 4 boards.
/// </summary>
/// <returns>Returns if the Red player won, the Yellow player won or if there was no win </returns>
GameOver State::checkDiagonals()
{
	for (int i = 0; i < (BOARD_SIZE * NUM_BOARDS) - 1; i += BOARD_SIZE)
	{
		std::array<CheckerType, ROW_SIZE> arr;
		for (int j = 0; j < ROW_SIZE; ++j)
		{
			int index = i + (j * (ROW_SIZE + 1));
			arr.at(j) = m_pieces.at(index);
		}
		GameOver state = checkForWinForPieces(arr);
		if (state != GameOver::None) return state;
	}
	for (int i = ROW_SIZE - 1; i < (BOARD_SIZE * NUM_BOARDS) - 1; i += BOARD_SIZE)
	{
		std::array<CheckerType, ROW_SIZE> arr;
		for (int j = 0; j < ROW_SIZE; ++j)
		{
			int index = i + (j * (ROW_SIZE - 1));
			arr.at(j) = m_pieces.at(index);
		}
		GameOver state = checkForWinForPieces(arr);
		if (state != GameOver::None) return state;
	}
	std::array<CheckerType, 4> arr;
	for (int i = 0; i < 4; ++i)
	{
		arr.at(i) = m_pieces.at(m_diagonalIndices.at(i));
	}
	GameOver state = checkForWinForPieces(arr);
	if (state != GameOver::None) return state;
	for (int i = 0; i < 4; ++i)
	{
		arr.at(i) = m_pieces.at(m_oppositeDiagonalIndices.at(i));
	}
	state = checkForWinForPieces(arr);
	if (state != GameOver::None) return state;
	return GameOver::None;
}

/// <summary>
/// goes through the entire board and if there is no free spaces then it assumes that there is a draw if a win was not able to be found earlier
/// </summary>
/// <returns>Returns if the Red player won, the Yellow player won or if there was no win </returns>
GameOver State::checkForDraw()const
{
	for (auto& piece : m_pieces)
	{
		if (piece == CheckerType::None)
		{
			return GameOver::None;
		}
	}
	return GameOver::Tie;
}

/// <summary>
/// checks 4 different pieces passed in and returns a win for whatever colour is passed in if they are all the same
/// the checkers that are passed in will be generated from the other functions in this class which check the different axiz on the board such as the horizontals and verticals
/// </summary>
/// <param name="checkers">array of 4 vectors that represent a possible connect 4 of either red or yellow pieces</param>
/// <returns></returns>
GameOver State::checkForWinForPieces(std::array<CheckerType, ROW_SIZE>& checkers)
{
	CheckerType type = checkers.at(0);
	if (type == CheckerType::None) return GameOver::None;

	for (int i = 1; i < checkers.size(); i++)
	{
		if (checkers.at(i) != type) return GameOver::None;
	}
	GameOver result = (type == CheckerType::Red) ? GameOver::Red : GameOver::Yellow;
	return result;
}

/// <summary>
/// The constructor sets up the board to be completely empty
/// </summary>
State::State()
{
	for (int z = 0; z < BOARD_SIZE * NUM_BOARDS; z++)
	{
		m_pieces.push_back(CheckerType::None);
	}
	std::cout << "\n";
}

/// <summary>
/// returns the piece at the position
/// </summary>
/// <param name="row">row between 0 and 3 inclusive that the piece is on</param>
/// <param name="col">col between 0 and 3 inclusive that the piece is on</param>
/// <param name="board">board between 0 and 3 inclusive that the piece is on</param>
/// <returns>returns the checker type of the piece at this position</returns>
CheckerType State::getPieceAtPosition(int row, int col, int board) const
{
	return m_pieces.at((row * ROW_SIZE + col) + (board * BOARD_SIZE));
}

/// <summary>
/// set the piece at the given position to a specific checker type
/// </summary>
/// <param name="row">row between 0 and 3 inclusive that the piece to be set is on</param>
/// <param name="col">col between 0 and 3 inclusive that the piece to be set is on</param>
/// <param name="board">board between 0 and 3 inclusive that the piece to be set is on</param>
/// <param name="type">Can be set to either red, yellow or none</param>
void State::setPieceAtPosition(int row, int col, int board, CheckerType type)
{
	m_pieces.at((row * ROW_SIZE + col) + (board * BOARD_SIZE)) = type;
}

/// <summary>
/// returns the piece at the index passed in
/// </summary>
/// <param name="index">index between 0 and 63 inclusive of the piece to be returned</param>
/// <returns>returns the type that this piece is at the position given</returns>
CheckerType State::getPieceAtPosition(int index) const
{
	return m_pieces.at(index);
}

/// <summary>
/// sets the piece at the the index given to the new checker type
/// </summary>
/// <param name="index">index between 0 and 63 inclusive of the piece to be set</param>
/// <param name="type">type that the piece should be set to.</param>
void State::setPieceAtPosition(int index, CheckerType type)
{
	if (index >= 0 && index < m_pieces.size())
	{
		m_pieces.at(index) = type;
	}

}

/// <summary>
/// Checks if the position given is empty so that a piece is able to be placed there
/// </summary>
/// <param name="row">Row for the piece to be placed on</param>
/// <param name="col">Col for the piece to be placed on</param>
/// <param name="board">Board for the piece to be placed on</param>
/// <returns>returns true if the move is legal, otherwise false</returns>
bool State::isMoveLegal(int row, int col, int board) const
{
	return m_pieces.at((row * ROW_SIZE + col) + (board * BOARD_SIZE)) == CheckerType::None;
}

/// <summary>
/// Checks if the position given is empty so that a piece is able to be placed there
/// </summary>
/// <param name="index">index of the position for the piece to be placed on</param>
/// <returns>returns true if the move is legal, otherwise false</returns>
bool State::isMoveLegal(int index) const
{
	return m_pieces.at(index) == CheckerType::None;
}

/// <summary>
/// Checks for a victory for both players.
/// Also checks for a draw if no win could be found for either player.
/// </summary>
/// <returns>returns the colour of the player who won if a player won or a tie if a tie was received. If the game is still on going then None will be returned</returns>
GameOver State::checkVictory()
{
	GameOver result = GameOver::None;
	result = checkDiagonals();
	if (result != GameOver::None) return result;
	result = checkHorizontals();
	if (result != GameOver::None) return result;
	result = checkVerticals();
	if (result != GameOver::None) return result;
	result = checkStraightDown();
	if (result != GameOver::None) return result;
	result = checkForDraw();
	return result;
}

/// <summary>
/// Gets all of the different legal spots to be able to place another piece on the board
/// </summary>
/// <returns>a vector of indices that represent the positions that are still legal to play on</returns>
std::vector<int> State::getLegalSpotsToPlay() const
{
	std::vector<int> availableSpots;
	for (int i = 0; i < m_pieces.size(); ++i)
	{
		if (m_pieces.at(i) == CheckerType::None)
		{
			availableSpots.push_back(i);
		}
	}
	return availableSpots;
}

/// <summary>
/// Gets all of the types of pieces that are on the same row as the index that was passed in
/// </summary>
/// <param name="index">index of the position that you want to get all of the other pieces on the same row</param>
/// <returns>A list of 3 pieces that are all on the same row as the piece passed in</returns>
std::array<CheckerType, 3> State::getAllOnSameRow(int index) const
{
	std::array<CheckerType, 3> arr{};
	int rowNumber = (index / 4);
	int positionInRow = (index % 4);
	int currentIndex = 0;
	for (int i = 0; i < 64; ++i)
	{
		if (rowNumber == i / 4 && positionInRow != i % 4)
		{
			arr.at(currentIndex) = m_pieces.at(i);
			currentIndex++;
			if (currentIndex >= 3)
			{
				return arr;
			}
		}
	}
	return arr;
}

/// <summary>
/// Gets all of the types of pieces that are on the same column as the index that was passed in
/// </summary>
/// <param name="index">index of the position that you want to get all of the other pieces on the same column</param>
/// <returns>A list of 3 pieces that are all on the same column as the piece passed in</returns>
std::array<CheckerType, 3> State::getAllOnSameColumn(int index) const
{
	std::array<CheckerType, 3> arr{};
	int boardNumber = (index / BOARD_SIZE);
	int columnNumber = (index % ROW_SIZE);
	int currentIndex = 0;
	int amountAdded = 0;
	for (int i = 0; i < BOARD_SIZE * NUM_BOARDS; ++i)
	{
		if (boardNumber == (i / BOARD_SIZE) && columnNumber == (i % ROW_SIZE) && index != i)
		{
			arr.at(currentIndex) = m_pieces.at(i);
			currentIndex++;
			amountAdded++;
			if (amountAdded >= 3) return arr;
		}
	}
	return arr;
}

/// <summary>
/// Gets all of the types of pieces that are on the same straight down as the index that was passed in
/// </summary>
/// <param name="index">index of the position that you want to get all of the other pieces on the same straight down</param>
/// <returns>A list of 3 pieces that are all on the same straight down as the piece passed in</returns>
std::array<CheckerType, 3> State::getAllStraightDown(int index) const
{
	std::array<CheckerType, 3> arr{};
	if (index == 16)
	{
		std::cout << "";
	}
	int boardNumber = (index / BOARD_SIZE);
	int currentIndex = 0;
	for (int i = 0; i < boardNumber; ++i)
	{
		int value = index - (BOARD_SIZE * (i + 1));
		arr.at(currentIndex) = m_pieces.at(value);
		currentIndex++;
	}

	for (int i = 0; i < 3 - boardNumber; ++i)
	{
		int value = index + (BOARD_SIZE * (i + 1));
		arr.at(currentIndex) = m_pieces.at(value);
		currentIndex++;
	}
	return arr;
}

/// <summary>
/// Gets all of the types of pieces that are on the same board diagonal as the index that was passed in
/// </summary>
/// <param name="index">index of the position that you want to get all of the other pieces on the same board diagonal</param>
/// <returns>A list of 3 pieces that are all on the same board diagonal as the piece passed in</returns>
std::array<CheckerType, 3> State::getAllOnSameBoardDiagonal(int index) const
{
	std::array<CheckerType, 3> arr{};
	int boardNumber = (index / BOARD_SIZE);
	int diagonalForBoard = (boardNumber > 0) ? index % 16 : index;
	bool isFirstDiagonal = (diagonalForBoard % 5 == 0) ? true : false;
	bool isSecondDiagonal = (diagonalForBoard % 3 == 0 && !isFirstDiagonal) ? true : false;
	int currentIndex = 0;
	for (int i = 0; i < BOARD_SIZE * NUM_BOARDS && currentIndex < 3; ++i)
	{
		if (boardNumber == (i / BOARD_SIZE) && index != i)
		{
			int diagonal = (boardNumber > 0) ? i % 16 : i;
			if (isFirstDiagonal)
			{
				if (diagonal % 5 == 0)
				{
					arr.at(currentIndex) = m_pieces.at(i);
					currentIndex++;
				}				
			}
			else if (isSecondDiagonal)
			{
				if (diagonal % 3 == 0)
				{
					arr.at(currentIndex) = m_pieces.at(i);
					currentIndex++;
				}
			}
		}
	}
	return arr;
}

/// <summary>
/// Gets all of the types of pieces that are on the same big diagonal as the index that was passed in
/// </summary>
/// <param name="index">index of the position that you want to get all of the other pieces on the same big diagonal</param>
/// <returns>A list of 3 pieces that are all on the same big diagonal as the piece passed in</returns>
std::array<CheckerType, 3> State::getAllOnSameDiagonal(int index) const
{
	bool onFirstDiagonal = std::find(m_diagonalIndices.begin(), m_diagonalIndices.end(), index) != m_diagonalIndices.end();
	bool onSecondDiagonal = std::find(m_oppositeDiagonalIndices.begin(), m_oppositeDiagonalIndices.end(), index) != m_oppositeDiagonalIndices.end();
	std::array<CheckerType, 3> arr{};
	int currentIndex = 0;
	if (onFirstDiagonal)
	{
		for (int num : m_diagonalIndices)
		{
			if (num != index)
			{
				arr.at(currentIndex) = m_pieces.at(num);
				currentIndex++;
			}
		}
	}
	else if (onSecondDiagonal)
	{
		for (int num : m_oppositeDiagonalIndices)
		{
			if (num != index)
			{
				arr.at(currentIndex) = m_pieces.at(num);
				currentIndex++;
			}
		}
	}
	return arr;
}

/// <summary>
/// Checks to see if a particular index is on a board diagonal
/// </summary>
/// <param name="index">index to be checked to see if it is on a board diagonal</param>
/// <returns>returns true if on board diagonal, otherwise false</returns>
bool State::isOnBoardDiagonal(int index) const
{
	int boardNumber = (index / BOARD_SIZE);
	int diagonalForBoard = (boardNumber > 0) ? index % 16 : index;
	bool isFirstDiagonal = (diagonalForBoard % 5 == 0) ? true : false;
	bool isSecondDiagonal = (diagonalForBoard % 3 == 0 && !isFirstDiagonal) ? true : false;
	return isFirstDiagonal || isSecondDiagonal;
}

/// <summary>
/// Checks to see if a particular index is on a big diagonal
/// </summary>
/// <param name="index">index to be checked to see if it is on a big diagonal</param>
/// <returns>returns true if on big diagonal, otherwise false</returns>
bool State::isOnDiagonal(int index) const
{
	bool onFirstDiagonal = std::find(m_diagonalIndices.begin(), m_diagonalIndices.end(), index) != m_diagonalIndices.end();
	bool onSecondDiagonal = std::find(m_oppositeDiagonalIndices.begin(), m_oppositeDiagonalIndices.end(), index) != m_oppositeDiagonalIndices.end();
	return onFirstDiagonal || onSecondDiagonal;
}

/// <summary>
/// Checks if a piece at a specific position is in a corner
/// </summary>
/// <param name="index">index to be checked</param>
/// <returns>returns true if it is a corner, otherwise false</returns>
bool State::isCorner(int index) const
{
	return std::find(m_corners.begin(), m_corners.end(), index) != m_corners.end();;
}

/// <summary>
/// returns all of the pieces on the board, including empty spaces
/// </summary>
/// <returns>vector of checker types representing the entire board</returns>
std::vector<CheckerType> State::getPieces() const
{
	return m_pieces;
}
