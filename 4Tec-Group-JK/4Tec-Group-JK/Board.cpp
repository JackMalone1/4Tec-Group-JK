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
		m_checkers.at(i).setColour(CheckerType::None);

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

	m_checkerGroup1.create(1500, 1500);
	m_checkerGroup2.create(1500, 1500);
	m_checkerGroup3.create(1500, 1500);
	m_checkerGroup4.create(1500, 1500);
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
				/*X*/ (m_board.at(0).getGlobalBounds().width / 4 * (i % 4) + m_board.at(0).getPosition().x - (m_board.at(0).getGlobalBounds().width / 2) + m_offset.x),
				/*Y*/ (m_board.at(0).getGlobalBounds().height / 4 * row) + m_board.at(0).getPosition().y - (m_board.at(0).getGlobalBounds().height / 2) - m_offset.y));
		}

		if (i < 32 && i >= 16)
		{
			m_checkers.at(i).setPosition(sf::Vector2f(
				/*X*/ (m_board.at(1).getGlobalBounds().width / 4 * (i % 4) + m_board.at(1).getPosition().x - (m_board.at(1).getGlobalBounds().width / 2) + m_offset.x),
				/*Y*/ (m_board.at(1).getGlobalBounds().height / 4 * (row - 4)) + m_board.at(1).getPosition().y - (m_board.at(1).getGlobalBounds().height / 2) - m_offset.y));
		}

		if (i < 48 && i >= 32)
		{
			m_checkers.at(i).setPosition(sf::Vector2f(
				/*X*/ (m_board.at(2).getGlobalBounds().width / 4 * (i % 4) + m_board.at(2).getPosition().x - (m_board.at(2).getGlobalBounds().width / 2) + m_offset.x),
				/*Y*/ (m_board.at(2).getGlobalBounds().height / 4 * (row - 8)) + m_board.at(2).getPosition().y - (m_board.at(2).getGlobalBounds().height / 2) - m_offset.y));
		}

		if (i < 64 && i >= 48)
		{
			m_checkers.at(i).setPosition(sf::Vector2f(
				/*X*/ (m_board.at(3).getGlobalBounds().width / 4 * (i % 4) + m_board.at(3).getPosition().x - (m_board.at(3).getGlobalBounds().width / 2) + m_offset.x),
				/*Y*/ (m_board.at(3).getGlobalBounds().height / 4 * (row - 12)) + m_board.at(3).getPosition().y - (m_board.at(3).getGlobalBounds().height / 2) - m_offset.y));
		}

		m_checkers.at(i).setOrigin(sf::Vector2f(0, 0));
	}
}

void Board::setCheckerOrigin()
{
	if ((int)m_checks.getRotation() == 315.0f)
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
				m_checkers.at(i).setOrigin(sf::Vector2f(m_checkers.at(i).getPosition().x - m_targetPos.at(0).x - m_offset.x, 
					m_checkers.at(i).getPosition().y - m_targetPos.at(0).y + m_offset.y));
			}

			if (i < 32 && i >= 16)
			{
				m_checkers.at(i).setOrigin(sf::Vector2f(m_checkers.at(i).getPosition().x - m_targetPos.at(1).x - m_offset.x, 
					m_checkers.at(i).getPosition().y - m_targetPos.at(1).y + m_offset.y));
			}

			if (i < 48 && i >= 32)
			{
				m_checkers.at(i).setOrigin(sf::Vector2f(m_checkers.at(i).getPosition().x - m_targetPos.at(2).x - m_offset.x, 
					m_checkers.at(i).getPosition().y - m_targetPos.at(2).y + m_offset.y));
			}

			if (i < 64 && i >= 48)
			{
				m_checkers.at(i).setOrigin(sf::Vector2f(m_checkers.at(i).getPosition().x - m_targetPos.at(3).x - m_offset.x, 
					m_checkers.at(i).getPosition().y - m_targetPos.at(3).y + m_offset.y));
			}
		}
	}
	else
	{
		for (int i = 0; i < 64; i++)
		{
			m_checkers.at(i).setOrigin(sf::Vector2f(0, 0));
		}
	}
}

void Board::resetCheckers()
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

				(int)m_board.at(i).getRotation() != 315.0f)
			{
				m_board.at(i).setRotation(m_board.at(i).getRotation() - m_boardMoveSpeed);
				setCheckerPosition();
				v.setSize(v.getSize().x, v.getSize().y + (m_boardMoveSpeed * m_boardRotSpeed));
			}
		}
	}
	
	setCheckerOrigin();

	for (int i = 0; i < 4; i++)
	{
		t_window.draw(m_board.at(i));
	}

	m_checkerGroup1.clear(sf::Color::Transparent);
	m_checkerGroup2.clear(sf::Color::Transparent);
	m_checkerGroup3.clear(sf::Color::Transparent);
	m_checkerGroup4.clear(sf::Color::Transparent);

	for (auto& checker : m_checkers)
	{
		checker.resetTexture();
	}

	for (int i = 0; i < 64; i++)
	{
		if (i < 16 && i >= 0)
		{
			m_checkerGroup1.draw(m_checkers.at(i).m_checker);
		}

		if (i < 32 && i >= 16)
		{
			m_checkerGroup2.draw(m_checkers.at(i).m_checker);
		}

		if (i < 48 && i >= 32)
		{
			m_checkerGroup3.draw(m_checkers.at(i).m_checker);
		}

		if (i < 64 && i >= 48)
		{
			m_checkerGroup4.draw(m_checkers.at(i).m_checker);
		}
	}
	
	m_checkerGroup1.display();
	m_checks.setTexture(m_checkerGroup1.getTexture());
	m_checks.setOrigin(m_board.at(0).getPosition());
	m_checks.setPosition(m_board.at(0).getPosition() );
	m_checks.setRotation(m_board.at(0).getRotation());
	m_window.draw(m_checks);

	m_checkerGroup2.display();
	m_checks.setTexture(m_checkerGroup2.getTexture());
	m_checks.setOrigin(m_board.at(1).getPosition());
	m_checks.setPosition(m_board.at(1).getPosition());
	m_checks.setRotation(m_board.at(1).getRotation());
	m_window.draw(m_checks);

	m_checkerGroup3.display();
	m_checks.setTexture(m_checkerGroup3.getTexture());
	m_checks.setOrigin(m_board.at(2).getPosition());
	m_checks.setPosition(m_board.at(2).getPosition());
	m_checks.setRotation(m_board.at(2).getRotation());
	m_window.draw(m_checks);

	m_checkerGroup4.display();
	m_checks.setTexture(m_checkerGroup4.getTexture());
	m_checks.setOrigin(m_board.at(3).getPosition());
	m_checks.setPosition(m_board.at(3).getPosition());
	m_checks.setRotation(m_board.at(3).getRotation());
	m_window.draw(m_checks);

	if (m_viewOn)
	{
		t_window.setView(t_window.getDefaultView());
	}
}

/// <summary>
/// This checks to see if we need to be changing the view from 2D to (fake) 3D
/// </summary>
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
			resetCheckers();
		}
		else
		{
			v.reset(sf::FloatRect(m_board.at(i).getPosition().x, m_board.at(i).getPosition().y, G_WINDOW_WIDTH, G_WINDOW_HEIGHT));
		}
	}
}

/// <summary>
/// This checks if there is a piece already in the position on the board
/// you are trying to place a piece on, if there is no piece in the position
/// then you will place a red piece in that position
/// </summary>
/// <param name="row"></param>
/// <param name="col"></param>
/// <param name="board"></param>
/// <returns></returns>
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
	Move move = m_ai.doMove(state);
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
