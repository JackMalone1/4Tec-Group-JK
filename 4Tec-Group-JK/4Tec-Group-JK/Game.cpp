#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ G_WINDOW_WIDTH, G_WINDOW_HEIGHT, 32U }, "4TEC" },
	m_board{ m_window }
{
	m_window.setFramerateLimit(fps);
	ImGui::SFML::Init(m_window);
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	m_board.updateDisplayOfBoard();
}

Game::~Game()
{
	ImGui::SFML::Shutdown();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen())
	{
		timeSinceLastUpdate += clock.restart();

		processEvents();
		ImGui::SFML::Update(m_window, sf::seconds(1.0f / fps));
		updateGUI();
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(m_window, event);
		if (sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type ||
			sf::Event::MouseButtonReleased == event.type) //user pressed a key
		{
			processKeys(event);
		}

		if (event.mouseButton.button == sf::Mouse::Left &&
			event.type == sf::Event::MouseButtonReleased)
		{
			m_board.placePiece(sf::Mouse::getPosition(m_window));
		}

		// Turn on/off isometric view
		if (event.KeyReleased == event.type && event.key.code == sf::Keyboard::A)
		{
			m_board.switchView();
		}
	}
}

void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_window.close();
	}

	if (sf::Mouse::Left == t_event.key.code)
	{
		m_mousePos = sf::Mouse::getPosition(m_window);

		std::cout << "X: " << m_mousePos.x << ", Y: " << m_mousePos.y << std::endl;
	}
}

void Game::update(sf::Time t_deltaTime)
{
	m_deltaTime = t_deltaTime;
	m_board.update();
}

void Game::render()
{
	m_window.clear(sf::Color::White);
	ImGui::SFML::Render(m_window);
	m_board.render(m_window);
	m_window.display();
}

void Game::updateGUI()
{
	static ImGuiID dockspaceID = 0;
	static bool winOpenWish = true;

	ImGui::SetNextWindowPos(sf::Vector2f(0, 0));
	ImGui::SetNextWindowSize(sf::Vector2f(G_WINDOW_WIDTH, G_WINDOW_HEIGHT));
	if (ImGui::Begin("Master Window", &winOpenWish))
	{
		ImGui::TextUnformatted("Boards");
	}

	// Declare Central dockspace
	dockspaceID = ImGui::GetID("HUB_DockSpace");
	ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode);

	ImGui::End();

	if (!winOpenWish)
	{
		ImGui::OpenPopup("Popup");
	}

	//ImGui::SetNextWindowFocus();
	if (ImGui::BeginPopupModal("Popup"))
	{
		ImGui::TextUnformatted("a popup");
		ImGui::EndPopup();
	}

	ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Place a piece"))
	{
		if (ImGui::SliderInt("Row", &input, 1, 4))
		{
			std::cout << input << std::endl;
		}

		if (ImGui::SliderInt("Col", &col, 1, 4))
		{
			std::cout << col << std::endl;
		}

		if (ImGui::SliderInt("Board", &board, 1, 4))
		{
			std::cout << board << std::endl;
		}

		if (ImGui::Button("Select Square", sf::Vector2f(100.0f, 100.0f)))
		{
			m_board.placePiece(input - 1, col - 1, board - 1);
			if (m_board.gameOver()) m_window.close();
			std::cout << "Placed piece at row: " << input << " at col: " << col << " on board: " << board << std::endl;
			m_board.aiTurn();
			if (m_board.gameOver()) m_window.close();
		}
	}
	ImGui::End();

	ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Settings"))
	{
		if (ImGui::Button("Quit Game"))
		{
			m_window.close();
		}
	}
	ImGui::End();
 }