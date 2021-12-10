#ifndef CHECKER_HPP
#define CHECKER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Globals.h"

enum class Colour
{
	Red = 0,
	Yellow = 1,
	None = 2
};

class Checker
{
public:

	Checker(Colour t_color);
	~Checker();
	void update();
	void render(sf::RenderWindow& t_window, bool t_viewOn);

private:
	
	void colorPicker();

	sf::Texture m_checkerTexture;
	sf::Sprite m_checker;
	std::string m_directory;

	Colour m_color;
};
#endif