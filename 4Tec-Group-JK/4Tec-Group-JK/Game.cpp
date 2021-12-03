#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ G_WINDOW_WIDTH, G_WINDOW_HEIGHT, 32U }, "4TEC" },
	m_exitGame{false} //when true game will exit
{
	ImGui::SFML::Init(m_window);
	for (int i = 0; i < G_CHECKER_COUNT; i++)
	{
		int m_color = (rand() % 4);
		m_checker.push_back(new Checker(m_color));
	}
}

Game::~Game()
{
	ImGui::SFML::Shutdown();
}

void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		ImGui::SFML::ProcessEvent(m_window, newEvent);
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type || 
			sf::Event::MouseButtonReleased == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
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

	std::cout << "F" << std::endl;
}

void Game::render()
{
	updateGUI();
	m_window.clear(sf::Color::White);

	m_board.render(m_window);

	for (auto &checker : m_checker)
	{
		checker->render(m_window);
	}
		
	ImGui::SFML::Render(m_window);
	m_window.display();
}

void Game::updateGUI()
{
	ImGui::SFML::Update(m_window, m_deltaTime);
	ImGui::Begin("Hello, world!");
	ImGui::Button("Cool Button");
	ImGui::End();
	
}
