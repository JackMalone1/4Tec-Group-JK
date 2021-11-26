#include "Board.h"

Board::Board()
{
	m_directory = "Assets//IMAGES/Grid.png";
	m_boardTexture.loadFromFile(m_directory);
	m_board.setTexture(m_boardTexture);
	m_board.setScale(3, 3);
}

Board::~Board()
{
}

void Board::update()
{
}

void Board::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_board);
}