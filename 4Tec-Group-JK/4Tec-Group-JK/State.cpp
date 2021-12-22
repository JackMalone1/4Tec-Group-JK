#include "State.h"
#include <iostream>

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
	return m_pieces.at((col * 4 + row) * (board + 1));
}

void State::setPieceAtPosition(int row, int col, int board, CheckerType type)
{
	m_pieces.at((col * 4 + row) * (board + 1)) = type;
}

GameOver State::checkVictory()
{
	return GameOver::None;
}
