#include "Checker.h"

Checker::Checker(Colour t_color) :
	m_color{t_color}
{
	m_directory = "Assets//IMAGES/Checker.png";
	m_checkerTexture.loadFromFile(m_directory);
	m_checker.setTexture(m_checkerTexture);
	m_checker.setScale(1.0, 1.0);

	colorPicker();
}

Checker::~Checker()
{
}

void Checker::update()
{
}

void Checker::render(sf::RenderWindow& t_window, bool t_viewOn)
{
	if (m_color == Colour::None) return;
	sf::Vector2f position = m_checker.getPosition();

	if (t_viewOn)
	{		
		m_checker.setRotation(45.f);
		//adjust the position for new screen coordinates (once)
		m_checker.setPosition(m_checker.getPosition().x, m_checker.getPosition().y * 2);
		sf::View v = t_window.getDefaultView();
		v.setSize(v.getSize().x, v.getSize().y * 2);
		v.setCenter(v.getSize() * .5f);
		t_window.setView(v);		
	}

	t_window.draw(m_checker);

	if(t_viewOn)
	{
		m_checker.setPosition(position);
		t_window.setView(t_window.getDefaultView());
	}
	
}

void Checker::colorPicker()
{
	if (m_color == Colour::Red)
	{
		m_checker.setTextureRect(sf::IntRect(0, 0, m_checkerTexture.getSize().x/2, m_checkerTexture.getSize().y / 2));
		std::cout << "Checker Created Successfully: Red" << std::endl;
	}
	else if (m_color == Colour::Yellow)
	{
		m_checker.setTextureRect(sf::IntRect(0, m_checkerTexture.getSize().y / 2, m_checkerTexture.getSize().x / 2, m_checkerTexture.getSize().y / 2));
		std::cout << "Checker Created Successfully: Yellow" << std::endl;
	}
}