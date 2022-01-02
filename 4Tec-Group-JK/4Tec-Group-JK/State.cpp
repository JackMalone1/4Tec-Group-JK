#include "State.h"
#include <iostream>

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
				int index = i + (j * COL_SIZE);
				if (index >= m_pieces.size()) index = m_pieces.size() - 1;
				arr.at(j) = m_pieces.at(index);
			}
			GameOver state = checkForWinForPieces(arr);
			if (state != GameOver::None) return state;
		}
		index += (ROW_SIZE * 3) + 1;//skip past 3 rows so this should be equal to 13 to get to the next board
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
	/*std::array<CheckerType, ROW_SIZE> arr;
	for (int i = 0; i < ROW_SIZE; ++i)
	{
		int index = i + (i * (BOARD_SIZE + ROW_SIZE + 1));
		arr.at(i) = m_pieces.at(index);
	}
	GameOver state = checkForWinForPieces(arr);
	if (state != GameOver::None) return state;
	for (int i = 0; i < ROW_SIZE; ++i)
	{
		int index = ROW_SIZE - 1 + (i * (BOARD_SIZE + ROW_SIZE - 1));
		arr.at(i) = m_pieces.at(index);
	}
	state = checkForWinForPieces(arr);
	if (state != GameOver::None) return state;*/
	return GameOver::None;
}

GameOver State::checkForDraw()
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

GameOver State::checkForWinForPieces(std::array<CheckerType, ROW_SIZE> checkers)
{
	CheckerType type = checkers.at(0);
	if (type == CheckerType::None) return GameOver::None;

	for (int i = 1; i < checkers.size(); i++)
	{
		if (checkers.at(i) != type) return GameOver::None;
	}
	GameOver result = (type == CheckerType::Red) ? GameOver::Red : GameOver::Yellow;
	return GameOver();
}

State::State()
{
	for (int z = 0; z < BOARD_SIZE * NUM_BOARDS; z++)
	{
		m_pieces.push_back(CheckerType::None);
	}
	std::cout << "\n";
}

CheckerType State::getPieceAtPosition(int row, int col, int board)
{
	return m_pieces.at((row * ROW_SIZE + col) + (board * BOARD_SIZE));
}

void State::setPieceAtPosition(int row, int col, int board, CheckerType type)
{
	m_pieces.at((row * ROW_SIZE + col) + (board * BOARD_SIZE)) = type;
}

CheckerType State::getPieceAtPosition(int index)
{
	return m_pieces.at(index);
}

void State::setPieceAtPosition(int index, CheckerType type)
{
	m_pieces.at(index) = type;
}

bool State::isMoveLegal(int row, int col, int board)
{
	return m_pieces.at((row * ROW_SIZE + col) + (board * BOARD_SIZE)) == CheckerType::None;
}

bool State::isMoveLegal(int index)
{
	return m_pieces.at(index) == CheckerType::None;
}

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

std::vector<int> State::getLegalSpotsToPlay()
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

std::array<CheckerType, 3> State::getAllOnSameRow(int index)
{
	std::array<CheckerType, 3> arr{};
	int amountAdded = 0;
	int amountToLeft = (index >= ROW_SIZE) ? index % ROW_SIZE : index;
	int amountToRight = (ROW_SIZE - 1) - amountToLeft;
	for (int i = 0; i < amountToLeft; i++)
	{
		arr.at(amountAdded) = m_pieces.at(i);
		amountAdded++;
	}
	for (int i = 0; i < amountToRight; i++)
	{
		arr.at(amountAdded) = m_pieces.at(i + 1);
		amountAdded++;
	}
	return arr;
}

std::array<CheckerType, 3> State::getAllOnSameColumn(int index)
{
	std::array<CheckerType, 3> arr{};
	int boardNumber = (index / BOARD_SIZE);
	int columnNumber = (index % ROW_SIZE);
	int currentIndex = 0;
	for (int i = 0; i < BOARD_SIZE * NUM_BOARDS; ++i)
	{
		if (boardNumber == (i / BOARD_SIZE) && columnNumber == (i % ROW_SIZE) && index != i)
		{
			arr.at(currentIndex) = m_pieces.at(i);
			currentIndex++;
		}
	}
	return std::array<CheckerType, COL_SIZE - 1>();
}

std::array<CheckerType, 3> State::getAllStraightDown(int index)
{
	std::array<CheckerType, 3> arr{};
	int boardNumber = (index / BOARD_SIZE);
	int currentIndex = 0;
	for (int i = 0; i < boardNumber; ++i)
	{
		arr.at(currentIndex) = m_pieces.at(index - (BOARD_SIZE * (i + 1)));
	}

	for (int i = 0; i < 3 - boardNumber; ++i)
	{
		arr.at(currentIndex) = m_pieces.at(index + (BOARD_SIZE * (i + 1)));
	}
	return arr;
}

std::array<CheckerType, 3> State::getAllOnSameBoardDiagonal(int index)
{
	std::array<CheckerType, 3> arr{};
	int boardNumber = (index / BOARD_SIZE);
	int diagonalForBoard = (boardNumber > 0) ? index % 16 : index;
	bool isFirstDiagonal = (diagonalForBoard % 5 == 0) ? true : false;
	bool isSecondDiagonal = (diagonalForBoard % 3 == 0 && !isFirstDiagonal) ? true : false;
	int currentIndex = 0;
	for (int i = 0; i < BOARD_SIZE * NUM_BOARDS; ++i)
	{
		if (boardNumber == (i / BOARD_SIZE) && index != i)
		{
			int diagonal = (boardNumber > 0) ? i % 16 : i;
			if (isFirstDiagonal)
			{
				if (diagonal % 5 == 0)
				{
					arr.at(currentIndex) = m_pieces.at(i);
				}				
			}
			else if (isSecondDiagonal)
			{
				if (diagonal % 3 == 0)
				{
					arr.at(currentIndex) = m_pieces.at(i);
				}
			}
		}
	}
	return arr;
}

std::array<CheckerType, 3> State::getAllOnSameDiagonal(int index)
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

bool State::isOnBoardDiagonal(int index)
{
	int boardNumber = (index / BOARD_SIZE);
	int diagonalForBoard = (boardNumber > 0) ? index % 16 : index;
	bool isFirstDiagonal = (diagonalForBoard % 5 == 0) ? true : false;
	bool isSecondDiagonal = (diagonalForBoard % 3 == 0 && !isFirstDiagonal) ? true : false;
	return isFirstDiagonal || isSecondDiagonal;
}

bool State::isOnDiagonal(int index)
{
	bool onFirstDiagonal = std::find(m_diagonalIndices.begin(), m_diagonalIndices.end(), index) != m_diagonalIndices.end();
	bool onSecondDiagonal = std::find(m_oppositeDiagonalIndices.begin(), m_oppositeDiagonalIndices.end(), index) != m_oppositeDiagonalIndices.end();
	return onFirstDiagonal || onSecondDiagonal;
}

bool State::isCorner(int index)
{
	return std::find(m_corners.begin(), m_corners.end(), index) != m_corners.end();;
}

std::vector<CheckerType> State::getPieces()
{
	return m_pieces;
}
