#ifndef GAME_HPP
#define GAME_HPP
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Board.h"
#include "Checker.h"
#include "Globals.h"

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
	void updateGUI();
	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game
	Board m_board;	
	sf::Vector2i m_mousePos;
	sf::Time m_deltaTime;
};
#endif // !GAME_HPP