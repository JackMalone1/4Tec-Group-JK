#include "Board.h"

Board::Board(sf::RenderWindow& t_window) :
	m_window(t_window)
{
	m_directory = "Assets//IMAGES/Grid.png";
	m_boardTexture.loadFromFile(m_directory);
	m_board.setTexture(m_boardTexture);
	m_board.setOrigin(m_board.getGlobalBounds().width / 2, m_board.getGlobalBounds().height / 2);
	m_board.setScale(2, 2);
	m_board.setPosition(m_board.getGlobalBounds().width / 2 + m_boarder, m_board.getGlobalBounds().height / 2 + m_boarder);

	m_circ.setFillColor(sf::Color::Red);
	m_circ.setRadius(10);
	m_circ.setPosition(400.f, 350.f);

	v = t_window.getDefaultView();

	for (int i = 0; i < G_CHECKER_COUNT; i++)
	{
		int m_color = (rand() % 4);
		m_checker.push_back(new Checker(m_color));
	}
}

Board::~Board()
{
}

void Board::update()
{
}

void Board::render(sf::RenderWindow& t_window)
{
	if (m_viewOn)
	{ 
		v.setCenter(v.getSize() * .5f);
		t_window.setView(v);

		if (!m_inPosition)
		{			
			if ((int)m_board.getPosition().x < m_targetPos.x)
			{
				m_board.setPosition(m_board.getPosition().x + m_boardMoveSpeed, m_board.getPosition().y);
			}
			else if ((int)m_board.getPosition().y < m_targetPos.y)
			{
				m_board.setPosition(m_board.getPosition().x, m_board.getPosition().y + m_boardMoveSpeed);
			}
			else if ((int)m_board.getPosition().x > m_targetPos.x)
			{
				m_board.setPosition(m_board.getPosition().x - m_boardMoveSpeed, m_board.getPosition().y);
			}
			else if ((int)m_board.getPosition().y > m_targetPos.y)
			{
				m_board.setPosition(m_board.getPosition().x, m_board.getPosition().y - m_boardMoveSpeed);
			}
			else if ((int)m_board.getRotation() < 45.0f)
			{
				m_board.setRotation(m_board.getRotation() + .035f);
				v.setSize(v.getSize().x, v.getSize().y + .8);
			}
			else
			{
				//v.setSize(v.getSize().x, v.getSize().y * 2);
				m_inPosition = true;
			}
		}
	}

	t_window.draw(m_board);
	t_window.draw(m_circ);

	if (m_viewOn)
	{
		t_window.setView(t_window.getDefaultView());
	}

	for (auto& checker : m_checker)
	{
		checker->render(t_window, m_viewOn);
	}
}

void Board::placePiece(sf::Vector2i t_mousePosition)
{
	if (m_board.getGlobalBounds().contains((float)t_mousePosition.x, (float)t_mousePosition.y))
	{
		std::cout << "clicked on board" << std::endl;
	}
}

void Board::switchView()
{
	m_viewOn = !m_viewOn;

	if (!m_viewOn)
	{
		m_inPosition = false;
		m_board.setPosition(m_board.getGlobalBounds().width / 2 + m_boarder, m_board.getGlobalBounds().height / 2 + m_boarder);
		m_board.setRotation(0.f);
	}
}
