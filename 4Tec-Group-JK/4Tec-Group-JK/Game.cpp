#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ G_WINDOW_WIDTH, G_WINDOW_HEIGHT, 32U }, "4TEC" },
	m_exitGame{ false }, //when true game will exit,
	m_board{ m_window }
{
	m_window.setFramerateLimit(fps);
	ImGui::SFML::Init(m_window);

	//updateGUI();
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
			m_exitGame = true;
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
		m_exitGame = true;
	}

	if (sf::Mouse::Left == t_event.key.code)
	{
		m_mousePos = sf::Mouse::getPosition(m_window);

		std::cout << "X: " << m_mousePos.x << ", Y: " << m_mousePos.y << std::endl;
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	m_deltaTime = t_deltaTime;
	//ImGui::SFML::Update(m_window, m_deltaTime);
}

void Game::render()
{
	//updateGUI();
	m_window.clear(sf::Color::White);

	m_board.render(m_window);

	ImGui::SFML::Render(m_window);
	m_window.display();
}

void Game::updateGUI()
{
	ImGui::Begin("Hello, world!");
	if (ImGui::SliderInt("Row", &input, 1, 4))
	{
		std::cout << input << std::endl;
	}

	if (ImGui::SliderInt("Col", &col, 1, 4))
	{
		std::cout << col << std::endl;
	}
	if (ImGui::Button("Select Square", sf::Vector2f(100.0f, 100.0f)))
	{
		std::cout << "Button Pressed";
	}
	ImGui::End();
}