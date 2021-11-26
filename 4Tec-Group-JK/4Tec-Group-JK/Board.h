#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Globals.h"

class Board
{
public:

	Board();
	~Board();
	void update();
	void render(sf::RenderWindow& t_window);

private:

	sf::Texture m_boardTexture;
	sf::Sprite m_board;
	std::string m_directory;
};
#endif