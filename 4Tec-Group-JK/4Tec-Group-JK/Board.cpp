#include "Board.h"

/// <summary>
/// This is the constructor for the Board class:
/// Initializes values for needed variables
/// Creates 4 boards
/// Creates all checkers
/// </summary>
/// <param name="t_window"> We pass the window in to the constructor to help us manipulate the view that the board and pieces are being displayed at.</param>
Board::Board(sf::RenderWindow& t_window) :
	m_window(t_window)
{
	m_directory = "Assets//IMAGES/Grid.png";
	m_boardTexture.loadFromFile(m_directory);

	m_targetPos.push_back(sf::Vector2f(300.0f, 300.0f));
	m_targetPos.push_back(sf::Vector2f(300.0f, 600.0f));
	m_targetPos.push_back(sf::Vector2f(300.0f, 900.0f));
	m_targetPos.push_back(sf::Vector2f(300.0f, 1200.0f));

	for (int i = 0; i < 4; i++)
	{
		m_board.emplace_back(sf::Sprite());
		m_board.at(i).setTexture(m_boardTexture);
		m_board.at(i).setOrigin(m_board.at(i).getGlobalBounds().width / 2, m_board.at(i).getGlobalBounds().height / 2);
		m_board.at(i).setScale(1, 1);
	}

	m_board.at(0).setPosition(m_defaultPos1.x, m_defaultPos1.y);
	m_board.at(1).setPosition(m_defaultPos2.x, m_defaultPos2.y);
	m_board.at(2).setPosition(m_defaultPos3.x, m_defaultPos3.y);
	m_board.at(3).setPosition(m_defaultPos4.x, m_defaultPos4.y);

	for (int i = 0; i < 64; i++)
	{
		m_checkers.emplace_back(Checker());
		m_checkers.at(i).setColour(CheckerType::Red);

		if (i % 4 == 0)
		{
			row++;
		}

		if (i < 16 && i >= 0)
		{
			m_checkers.at(i).setPosition(sf::Vector2f(
				/*X*/ (m_board.at(0).getGlobalBounds().width / 4 * (i % 4) + m_defaultPos1.x - (m_board.at(0).getGlobalBounds().width / 2) + 2.5),
				/*Y*/ (m_board.at(0).getGlobalBounds().height / 4 * row) + m_defaultPos1.y - (m_board.at(0).getGlobalBounds().height / 2) - 47.5));
		}

		if (i < 32 && i >= 16)
		{
			m_checkers.at(i).setPosition(sf::Vector2f(
				/*X*/ (m_board.at(1).getGlobalBounds().width / 4 * (i % 4) + m_defaultPos2.x - (m_board.at(1).getGlobalBounds().width / 2) + 2.5),
				/*Y*/ (m_board.at(1).getGlobalBounds().height / 4 * (row - 4)) + m_defaultPos2.y - (m_board.at(1).getGlobalBounds().height / 2) - 47.5));
		}

		if (i < 48 && i >= 32)
		{
			m_checkers.at(i).setPosition(sf::Vector2f(
				/*X*/ (m_board.at(2).getGlobalBounds().width / 4 * (i % 4) + m_defaultPos3.x - (m_board.at(2).getGlobalBounds().width / 2) + 2.5),
				/*Y*/ (m_board.at(2).getGlobalBounds().height / 4 * (row - 8)) + m_defaultPos3.y - (m_board.at(2).getGlobalBounds().height / 2) - 47.5));
		}

		if (i < 64 && i >= 48)
		{
			m_checkers.at(i).setPosition(sf::Vector2f(
				/*X*/ (m_board.at(3).getGlobalBounds().width / 4 * (i % 4) + m_defaultPos4.x - (m_board.at(3).getGlobalBounds().width / 2) + 2.5),
				/*Y*/ (m_board.at(3).getGlobalBounds().height / 4 * (row - 12)) + m_defaultPos4.y - (m_board.at(3).getGlobalBounds().height / 2) - 47.5));
		}
	}

	v = t_window.getDefaultView();
}

/// <summary>
/// setCheckerPosition is used to set each checker in their correct place on the correct board by using just an index.
/// We will use this for easier complete manipulation when changing the views from 2d to 3d.
/// </summary>
void Board::setCheckerPosition()
{
	row = 0;

	for (int i = 0; i < 64; i++)
	{
		if (i % 4 == 0)
		{
			row++;
		}

		if (i < 16 && i >= 0)
		{
			m_checkers.at(i).setPosition(sf::Vector2f(
				/*X*/ (m_board.at(0).getGlobalBounds().width / 4 * (i % 4) + m_board.at(0).getPosition().x - (m_board.at(0).getGlobalBounds().width / 2) + 2.5),
				/*Y*/ (m_board.at(0).getGlobalBounds().height / 4 * row) + m_board.at(0).getPosition().y - (m_board.at(0).getGlobalBounds().height / 2) - 47.5));
		}

		if (i < 32 && i >= 16)
		{
			m_checkers.at(i).setPosition(sf::Vector2f(
				/*X*/ (m_board.at(1).getGlobalBounds().width / 4 * (i % 4) + m_board.at(1).getPosition().x - (m_board.at(1).getGlobalBounds().width / 2) + 2.5),
				/*Y*/ (m_board.at(1).getGlobalBounds().height / 4 * (row - 4)) + m_board.at(1).getPosition().y - (m_board.at(1).getGlobalBounds().height / 2) - 47.5));
		}

		if (i < 48 && i >= 32)
		{
			m_checkers.at(i).setPosition(sf::Vector2f(
				/*X*/ (m_board.at(2).getGlobalBounds().width / 4 * (i % 4) + m_board.at(2).getPosition().x - (m_board.at(2).getGlobalBounds().width / 2) + 2.5),
				/*Y*/ (m_board.at(2).getGlobalBounds().height / 4 * (row - 8)) + m_board.at(2).getPosition().y - (m_board.at(2).getGlobalBounds().height / 2) - 47.5));
		}

		if (i < 64 && i >= 48)
		{
			m_checkers.at(i).setPosition(sf::Vector2f(
				/*X*/ (m_board.at(3).getGlobalBounds().width / 4 * (i % 4) + m_board.at(3).getPosition().x - (m_board.at(3).getGlobalBounds().width / 2) + 2.5),
				/*Y*/ (m_board.at(3).getGlobalBounds().height / 4 * (row - 12)) + m_board.at(3).getPosition().y - (m_board.at(3).getGlobalBounds().height / 2) - 47.5));
		}

		m_checkers.at(i).setOrigin(m_checkers.at(i).getPosition());
	}
}

void Board::setCheckerRotation()
{
	for (int i = 0; i < 64; i++)
	{		
		if(m_checkers.at(i).getRotation() < -45.0f)
		{
			continue;
		}

		if (i < 16 && i >= 0)
		{
			m_checkers.at(i).setOrigin(m_targetPos.at(0));
			m_checkers.at(i).setRotation(m_board.at(0).getRotation() - m_boardMoveSpeed);
		}

		if (i < 32 && i >= 16)
		{
			m_checkers.at(i).setOrigin(m_targetPos.at(1));
			m_checkers.at(i).setRotation(m_board.at(1).getRotation() - m_boardMoveSpeed);
		}

		if (i < 48 && i >= 32)
		{
			m_checkers.at(i).setOrigin(m_targetPos.at(2));
			m_checkers.at(i).setRotation(m_board.at(2).getRotation() - m_boardMoveSpeed);
		}

		if (i < 64 && i >= 48)
		{
			m_checkers.at(i).setOrigin(m_targetPos.at(3));
			m_checkers.at(i).setRotation(m_board.at(3).getRotation() - m_boardMoveSpeed);
		}
	}
}

Board::~Board()
{
}

void Board::update()
{
}

/// <summary>
/// This is called in the games render function, 
/// it renders the board and all the checkers to the screen, 
/// alongside the ui that allows you to play the game. 
/// </summary>
/// <param name="t_window">We need to pass in the game window to display all necessary objects to the player</param>
void Board::render(sf::RenderWindow& t_window)
{
	if (m_viewOn)
	{
		if (!m_inPosition)
		{
			v.setCenter(v.getSize() * .5f);
			t_window.setView(v);
			for (int i = 0; i < 4; i++)
			{
				// If the boards X position is less than the Target X position
				if ((int)m_board.at(i).getPosition().x < m_targetPos.at(i).x)
				{
					m_board.at(i).setPosition(m_board.at(i).getPosition().x + m_boardMoveSpeed, m_board.at(i).getPosition().y);
					setCheckerPosition();
				}
				// If the boards Y position is less than the Target Y position
				else if ((int)m_board.at(i).getPosition().y < m_targetPos.at(i).y)
				{
					m_board.at(i).setPosition(m_board.at(i).getPosition().x, m_board.at(i).getPosition().y + m_boardMoveSpeed);
					setCheckerPosition();
				}
				// If the boards X position is greater than the Target X position
				else if ((int)m_board.at(i).getPosition().x > m_targetPos.at(i).x)
				{
					m_board.at(i).setPosition(m_board.at(i).getPosition().x - m_boardMoveSpeed, m_board.at(i).getPosition().y);
					setCheckerPosition();
				}
				// If the boards Y position is greater than the Target Y position
				else if ((int)m_board.at(i).getPosition().y > m_targetPos.at(i).y)
				{
					m_board.at(i).setPosition(m_board.at(i).getPosition().x, m_board.at(i).getPosition().y - m_boardMoveSpeed);
					setCheckerPosition();
				}


				// If the boards rotation is less than 45 degrees
				if ((int)m_board.at(0).getPosition().x == m_targetPos.at(0).x &&
					(int)m_board.at(0).getPosition().y == m_targetPos.at(0).y &&

					(int)m_board.at(1).getPosition().x == m_targetPos.at(1).x &&
					(int)m_board.at(1).getPosition().y == m_targetPos.at(1).y &&

					(int)m_board.at(2).getPosition().x == m_targetPos.at(2).x &&
					(int)m_board.at(2).getPosition().y == m_targetPos.at(2).y &&

					(int)m_board.at(3).getPosition().x == m_targetPos.at(3).x &&
					(int)m_board.at(3).getPosition().y == m_targetPos.at(3).y &&

					(int)m_board.at(i).getRotation() < 45.0f /*&&
					(int)m_checkers.at(63).getRotation() < 45.0f*/)
				{
					m_board.at(i).setRotation(m_board.at(i).getRotation() + m_boardMoveSpeed);
					setCheckerRotation();
					v.setSize(v.getSize().x, v.getSize().y + (m_boardMoveSpeed * m_boardRotSpeed));
				}
				else
				{
					//m_inPosition = true;
				}
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		t_window.draw(m_board.at(i));
	}

	for (int i = 0; i < 64; i++)
	{
		m_checkers.at(i).render(t_window);
	}

	if (m_viewOn)
	{
		t_window.setView(t_window.getDefaultView());
	}
}

void Board::placePiece(sf::Vector2i t_mousePosition)
{
	if (!m_viewOn)
	{
		for (int i = 0; i < 4; i++)
		{
			if (m_board.at(i).getGlobalBounds().contains((float)t_mousePosition.x, (float)t_mousePosition.y))
			{
				std::cout << "clicked on board" << std::endl;
			}
		}
	}
}

void Board::switchView()
{
	m_viewOn = !m_viewOn;

	for (int i = 0; i < 4; i++)
	{
		if (!m_viewOn)
		{
			m_board.at(0).setPosition(m_defaultPos1.x, m_defaultPos1.y);
			m_board.at(1).setPosition(m_defaultPos2.x, m_defaultPos2.y);
			m_board.at(2).setPosition(m_defaultPos3.x, m_defaultPos3.y);
			m_board.at(3).setPosition(m_defaultPos4.x, m_defaultPos4.y);
			m_board.at(i).setRotation(0.f);
			//setCheckerRotation();
			//setCheckerPosition();
		}
		else
		{
			v.reset(sf::FloatRect(m_board.at(i).getPosition().x, m_board.at(i).getPosition().y, G_WINDOW_WIDTH, G_WINDOW_HEIGHT));
		}
	}
}

bool Board::placePiece(int row, int col, int board)
{
	if (state.getPieceAtPosition(row, col, board) == CheckerType::None)
	{
		state.setPieceAtPosition(row, col, board, CheckerType::Red);
		return true;
	}

	return false;
}

void Board::aiTurn()
{
	Move move = m_ai.doMove(state, 0);
	state.setPieceAtPosition(move.index, CheckerType::Yellow);
	updateDisplayOfBoard();
}

bool Board::gameOver()
{
	return state.checkVictory() != GameOver::None;
}

void Board::updateDisplayOfBoard()
{
	std::vector<CheckerType> pieces = state.getPieces();
	system("cls");
	int numberPlaced = 0;
	for (int i = 0; i < pieces.size(); ++i)
	{
		if (i % 16 == 0)
		{
			std::cout << std::endl << "-----------------------" << std::endl;
			std::cout << "|";
		}
		else if (numberPlaced == 0)
		{
			std::cout << std::endl << "|";
		}
		switch (pieces.at(i))
		{
		case CheckerType::None:
			std::cout << "-|";
			break;
		case CheckerType::Red:
			std::cout << "X|";
			m_checkers.at(i).setColour(CheckerType::Red);
			break;
		case CheckerType::Yellow:
			std::cout << "O|";
			m_checkers.at(i).setColour(CheckerType::Yellow);
			break;
		default:
			break;
		}
		numberPlaced++;
		if (numberPlaced == 4)
		{
			numberPlaced = 0;
		}
	}

}
