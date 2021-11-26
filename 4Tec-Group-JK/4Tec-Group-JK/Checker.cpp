#include "Checker.h"

Checker::Checker(int t_color) : 
	m_color(t_color)
{
	m_directory = "Assets//IMAGES/Checker.png";
	m_checkerTexture.loadFromFile(m_directory);
	m_checker.setTexture(m_checkerTexture);
	m_checker.setScale(3, 3);

	colorPicker();
}

Checker::~Checker()
{
}

void Checker::update()
{
}

void Checker::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_checker);
}

void Checker::colorPicker()
{
	if (m_color == 0)
	{
		m_checker.setTextureRect(sf::IntRect(0, 0, m_checkerTexture.getSize().x/2, m_checkerTexture.getSize().y / 2));
		std::cout << "Checker Created Successfully: Red" << std::endl;
	}
	else if (m_color == 1)
	{
		m_checker.setTextureRect(sf::IntRect(m_checkerTexture.getSize().x / 2, 0, m_checkerTexture.getSize().x / 2, m_checkerTexture.getSize().y / 2));
		std::cout << "Checker Created Successfully: Blue" << std::endl;
	}
	else if (m_color == 2)
	{
		m_checker.setTextureRect(sf::IntRect(0, m_checkerTexture.getSize().y / 2, m_checkerTexture.getSize().x / 2, m_checkerTexture.getSize().y / 2));
		std::cout << "Checker Created Successfully: Yellow" << std::endl;
	}
	else if (m_color == 3)
	{
		m_checker.setTextureRect(sf::IntRect(m_checkerTexture.getSize().x / 2, m_checkerTexture.getSize().y / 2, m_checkerTexture.getSize().x / 2, m_checkerTexture.getSize().y / 2));
		std::cout << "Checker Created Successfully: Green" << std::endl;
	}
}