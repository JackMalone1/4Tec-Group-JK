#include "State.h"
#include <iostream>

GameOver State::checkHorizontals()
{
	int offset = ROW_SIZE;
	for (int initialPosition = 0; initialPosition <= (BOARD_SIZE * NUM_BOARDS) - ROW_SIZE; initialPosition += offset)
	{
		std::array<CheckerType, ROW_SIZE> arr;
		std::copy(m_pieces.begin() + initialPosition, m_pieces.begin() + initialPosition + offset - 1, arr);
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
	return result;
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
