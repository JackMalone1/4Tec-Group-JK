#ifndef CHECKER_HPP
#define CHECKER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Globals.h"

class Checker
{
public:

	Checker(int t_color);
	~Checker();
	void update();
	void render(sf::RenderWindow& t_window, bool t_viewOn);

private:
	
	void colorPicker();

	sf::Texture m_checkerTexture;
	sf::Sprite m_checker;
	std::string m_directory;

	int m_color;
};
#endif