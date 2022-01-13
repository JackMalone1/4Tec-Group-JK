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

/// <summary>
/// If the piece is Red or Yellow then display it to the screen, otherwise dont
/// </summary>
/// <param name="t_window">Render window</param>
void Checker::render(sf::RenderWindow& t_window)
{
	if (m_color == CheckerType::None) return;
	m_checker.setTexture(m_checkerTexture);
	t_window.draw(m_checker);
}

/// <summary>
/// Pass in the colour you want the piece to be and it will change the colour of the piece
/// </summary>
/// <param name="t_colour"></param>
void Checker::setColour(CheckerType t_colour)
{
	m_color = t_colour;

	if (t_colour == CheckerType::Red)
	{
		m_checker.setTextureRect(sf::IntRect(0, 0, m_checkerTexture.getSize().x / 2, m_checkerTexture.getSize().y / 2));
	}
	else if (t_colour == CheckerType::Yellow)
	{
		m_checker.setTextureRect(sf::IntRect(0, m_checkerTexture.getSize().y / 2, m_checkerTexture.getSize().x / 2, m_checkerTexture.getSize().y / 2));
	}
	else if (t_colour == CheckerType::None)
	{
		m_checker.setTextureRect(sf::IntRect(0, 0, 0, 0));
	}
}

/// <summary>
/// Function for setting the position of the checker through another class
/// </summary>
/// <param name="t_pos">position you want the checker to be in</param>
void Checker::setPosition(sf::Vector2f t_pos)
{
	m_checker.setPosition(t_pos);
}

/// <summary>
/// Function for setting the rotation of the checker through another class
/// </summary>
/// <param name="t_rot">rotation you want the checker to have</param>
void Checker::setRotation(float t_rot)
{
	m_checker.setRotation(t_rot);
}

/// <summary>
/// Returns the current checker position
/// </summary>
/// <returns>Checker Position</returns>
sf::Vector2f Checker::getPosition()
{
	return m_checker.getPosition();
}

/// <summary>
/// Returns the current checker rotation
/// </summary>
/// <returns>Checker Rotation</returns>
float Checker::getRotation()
{
	return m_checker.getRotation();
}

/// <summary>
/// Returns the origin of the current checker
/// </summary>
/// <returns>Checker Origin</returns>
sf::Vector2f Checker::getOrigin()
{
	return m_checker.getOrigin();
}

/// <summary>
/// Sets the otigin of the checker to be at a specific position
/// </summary>
/// <param name="t_pos"></param>
void Checker::setOrigin(sf::Vector2f t_pos)
{
	m_checker.setOrigin(t_pos);
}

void Checker::resetTexture()
{
	m_checker.setTexture(m_checkerTexture);
}
