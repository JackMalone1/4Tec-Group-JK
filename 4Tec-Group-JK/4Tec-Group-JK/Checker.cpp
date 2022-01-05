#include "Checker.h"

Checker::Checker()
{
	m_directory = "Assets//IMAGES/Checker.png";
	m_checkerTexture.loadFromFile(m_directory);
	m_checker.setTexture(m_checkerTexture);
	m_checker.setScale(.3, .3);
}

Checker::~Checker()
{
}

void Checker::update()
{
}

void Checker::render(sf::RenderWindow& t_window)
{
	if (m_color == CheckerType::None) return;
	m_checker.setTexture(m_checkerTexture);
	t_window.draw(m_checker);
}

void Checker::setColour(CheckerType t_colour)
{
	m_color = t_colour;
	colorPicker();
}

void Checker::setPosition(sf::Vector2f t_pos)
{
	m_checker.setPosition(t_pos);
}

void Checker::colorPicker()
{
	if (m_color == CheckerType::Red)
	{
		m_checker.setTextureRect(sf::IntRect(0, 0, m_checkerTexture.getSize().x/2, m_checkerTexture.getSize().y / 2));
	}
	else if (m_color == CheckerType::Yellow)
	{
		m_checker.setTextureRect(sf::IntRect(0, m_checkerTexture.getSize().y / 2, m_checkerTexture.getSize().x / 2, m_checkerTexture.getSize().y / 2));
	}
	else if (m_color == CheckerType::None)
	{
		m_checker.setTextureRect(sf::IntRect(0, 0, 0, 0));
	}
}