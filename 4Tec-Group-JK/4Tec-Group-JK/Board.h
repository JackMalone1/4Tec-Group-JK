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
	void setCheckerPosition();
	void setCheckerRotation();

private:

	sf::Texture m_boardTexture;
	std::vector<Checker> m_checkers;
	std::vector<sf::Sprite> m_board;
	std::string m_directory;
	sf::RenderWindow& m_window;

	std::vector<sf::Vector2f> m_targetPos; // 300.0f, 200.0f
	sf::Vector2f m_defaultPos1 = { 150.0f, 250.0f };
	sf::Vector2f m_defaultPos2 = { 450.0f, 250.0f };
	sf::Vector2f m_defaultPos3 = { 150.0f, 550.0f };
	sf::Vector2f m_defaultPos4 = { 450.0f, 550.0f };
	sf::Vector2f m_viewSize;

	sf::View v;

	int row = 0;
	int col = 0;
	float m_boardMoveSpeed = 5.0f;
	float m_boardRotSpeed = 5.0f;
	bool m_viewOn = false;
	bool m_inPosition = false;

	sf::Vector2f m_boardOffset = sf::Vector2f(0, 0);
	sf::Vector2f m_checkerOffset;

	Minimax m_ai;
	State state;
};
#endif