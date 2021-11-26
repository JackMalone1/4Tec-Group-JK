#include "Board.h"

Board::Board()
{
	m_directory = "Assets//IMAGES/Grid.png";
	m_boardTexture.loadFromFile(m_directory);
	m_board.setTexture(m_boardTexture);
	m_board.setScale(2, 2);
	m_board.setPosition(sf::Vector2f(400.f, 200.f));
}

Board::~Board()
{
}

void Board::update()
{
}

void Board::render(sf::RenderWindow& t_window)
{
	//t_window.draw(m_board);
	sf::Vector2f position = m_board.getPosition();
	m_board.setRotation(45.f);
	//adjust the position for new screen coordinates (once)
	m_board.setPosition(m_board.getPosition().x, m_board.getPosition().y * 2);
	sf::View v = t_window.getDefaultView();
	v.setSize(v.getSize().x, v.getSize().y * 2);
	v.setCenter(v.getSize() * .5f);

	t_window.setView(v);
	t_window.draw(m_board);
	t_window.setView(t_window.getDefaultView());
	m_board.setPosition(position);
}