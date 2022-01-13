#ifndef CHECKER_HPP
#define CHECKER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Globals.h"

/// <summary>
/// This class is for 1 single checker, instantiated elsewhere in the program
/// </summary>
class Checker
{
public:

	Checker();
	~Checker();
	void update();
	void render(sf::RenderWindow& t_window);
	void setColour(CheckerType t_colour);
	void setPosition(sf::Vector2f t_pos);
	void setRotation(float t_rot);
	void setOrigin(sf::Vector2f t_pos);
	float getRotation();
	sf::Vector2f getPosition();
	sf::Vector2f getOrigin();
	sf::Sprite m_checker;
	void resetTexture();
private:

	sf::Texture m_checkerTexture;
	std::string m_directory;

	CheckerType m_color;
};
#endif