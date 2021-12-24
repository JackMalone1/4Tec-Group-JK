#include "State.h"
#include <iostream>

GameOver State::checkHorizontals()
{
	//for (int board = 0; board < 4; board++)
	//{
	//	for(int piece = 0 + (board * 16);board < )
	//}
	return GameOver::None;
}

GameOver State::checkVerticals()
{
	return GameOver::None;
}

GameOver State::checkStraightDown()
{
	return GameOver::None;
}

GameOver State::checkDiagonals()
{
	return GameOver();
}

GameOver State::checkForDraw()
{
	return GameOver();
}

GameOver State::checkForWinForPieces(std::array<CheckerType, 4> checkers)
{
	return GameOver::None;
}

State::State()
{
	for (int z = 0; z < 64; z++)
	{
		m_pieces.push_back(CheckerType::None);
	}
	std::cout << "\n";
}

CheckerType State::getPieceAtPosition(int row, int col, int board)
{
	return m_pieces.at((row * 4 + col) + (board * 16));
}

void State::setPieceAtPosition(int row, int col, int board, CheckerType type)
{
	m_pieces.at((row * 4 + col) + (board * 16)) = type;
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
