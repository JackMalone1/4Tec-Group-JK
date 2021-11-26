#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

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
};
#endif // !GAME_HPP