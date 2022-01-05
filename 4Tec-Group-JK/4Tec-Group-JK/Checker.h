#ifndef CHECKER_HPP
#define CHECKER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Globals.h"

class Checker
{
public:

	Checker();
	~Checker();
	void update();
	void render(sf::RenderWindow& t_window);
	void setColour(CheckerType t_colour);
	void setPosition(sf::Vector2f t_pos);

private:
	
	void colorPicker();

	sf::Texture m_checkerTexture;
	sf::Sprite m_checker;
	std::string m_directory;

	CheckerType m_color;
};
#endif