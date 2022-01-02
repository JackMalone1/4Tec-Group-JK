#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include "Checker.h"
#include "Globals.h"
#include "State.h"
#include "Minimax.h"

class Board
{
public:

	Board(sf::RenderWindow& t_window);
	~Board();
	void update();
	void render(sf::RenderWindow& t_window);
	void placePiece(sf::Vector2i t_mousePosition);
	void switchView();
	bool placePiece(int row, int col, int board);
	void aiTurn();
	bool gameOver();
	void updateDisplayOfBoard();
private:

	//std::array<std::array<std::array<Checker*, 4>, 4>, 4> m_boards;
	sf::Texture m_boardTexture;
	sf::Sprite m_board;
	std::string m_directory;
	sf::RenderWindow& m_window;

	sf::Vector2f m_targetPos = { 400.f, 350.f };
	sf::Vector2f m_viewSize;

	sf::View v;

	int m_boarder = 15;
	float m_boardMoveSpeed = 0.2f;
	bool m_viewOn = false;
	bool m_inPosition = false;

	/// Testing
	sf::CircleShape m_circ;
	Minimax m_ai;
	State state;
};
#endif