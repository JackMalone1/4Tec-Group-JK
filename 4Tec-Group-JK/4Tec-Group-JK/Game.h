#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Board.h"
#include "Checker.h"

class Game
{
public:
	Game();
	~Game();
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();	

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

	Board m_board;
	std::vector<Checker*> m_checker;

	sf::Vector2i m_mousePos;
};
#endif // !GAME_HPP