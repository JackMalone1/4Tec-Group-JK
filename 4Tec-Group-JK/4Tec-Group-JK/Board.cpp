#include "Board.h"

Board::Board(sf::RenderWindow& t_window) :
	m_window(t_window)
{
	m_directory = "Assets//IMAGES/Grid.png";
	m_boardTexture.loadFromFile(m_directory);
	m_board.setTexture(m_boardTexture);
	m_board.setOrigin(m_board.getGlobalBounds().width / 2, m_board.getGlobalBounds().height / 2);
	m_board.setScale(2, 2);
	m_board.setPosition(m_board.getGlobalBounds().width / 2 + m_boarder, m_board.getGlobalBounds().height / 2 + m_boarder);

	/*m_circ.setFillColor(sf::Color::Red);
	m_circ.setRadius(10);
	m_circ.setPosition(400.f, 350.f);*/

	v = t_window.getDefaultView();
	/*for (int i = 0; i < m_boards.size(); i++)
	{
		for (int j = 0; j < m_boards.at(i).size(); j++)
		{
			for (int k = 0; k < m_boards.at(i).at(j).size(); k++)
			{
				m_boards.at(i).at(j).at(k) = new Checker(Colour::None);
			}
		}
	}*/
}

Board::~Board()
{
}

void Board::update()
{
}

void Board::render(sf::RenderWindow& t_window)
{
	if (m_viewOn)
	{ 
		v.setCenter(v.getSize() * .5f);
		t_window.setView(v);

		if (!m_inPosition)
		{			
			if ((int)m_board.getPosition().x < m_targetPos.x)
			{
				m_board.setPosition(m_board.getPosition().x + m_boardMoveSpeed, m_board.getPosition().y);
			}
			else if ((int)m_board.getPosition().y < m_targetPos.y)
			{
				m_board.setPosition(m_board.getPosition().x, m_board.getPosition().y + m_boardMoveSpeed);
			}
			else if ((int)m_board.getPosition().x > m_targetPos.x)
			{
				m_board.setPosition(m_board.getPosition().x - m_boardMoveSpeed, m_board.getPosition().y);
			}
			else if ((int)m_board.getPosition().y > m_targetPos.y)
			{
				m_board.setPosition(m_board.getPosition().x, m_board.getPosition().y - m_boardMoveSpeed);
			}
			else if ((int)m_board.getRotation() < 45.0f)
			{
				m_board.setRotation(m_board.getRotation() + .035f);
				v.setSize(v.getSize().x, v.getSize().y + .8);
			}
			else
			{
				m_inPosition = true;
			}
		}
	}

	t_window.draw(m_board);
	t_window.draw(m_circ);

	if (m_viewOn)
	{
		t_window.setView(t_window.getDefaultView());
	}


}

void Board::placePiece(sf::Vector2i t_mousePosition)
{
	if (!m_viewOn)
	{
		if (m_board.getGlobalBounds().contains((float)t_mousePosition.x, (float)t_mousePosition.y))
		{
			std::cout << "clicked on board" << std::endl;
			sf::Vector2f size = sf::Vector2f(m_board.getGlobalBounds().width, m_board.getGlobalBounds().height);
		}
	}
}

void Board::switchView()
{
	m_viewOn = !m_viewOn;

	if (!m_viewOn)
	{
		m_inPosition = false;
		m_board.setPosition(m_board.getGlobalBounds().width / 2 + m_boarder, m_board.getGlobalBounds().height / 2 + m_boarder);
		m_board.setRotation(0.f);
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
	//system("cls");
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
			break;
		case CheckerType::Yellow:
			std::cout << "O|";
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
