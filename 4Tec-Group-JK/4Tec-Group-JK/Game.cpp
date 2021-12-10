#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ G_WINDOW_WIDTH, G_WINDOW_HEIGHT, 32U }, "4TEC" },
	m_exitGame{false}, //when true game will exit,
	m_board{ m_window }
{
	ImGui::SFML::Init(m_window);
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
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(m_window, event);
		if ( sf::Event::Closed == event.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == event.type ||
			sf::Event::MouseButtonReleased == event.type) //user pressed a key
		{
			processKeys(event);
		}

		if(event.mouseButton.button == sf::Mouse::Left && 
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
}

void Game::render()
{
	updateGUI();
	m_window.clear(sf::Color::White);

	m_board.render(m_window);
		
	ImGui::SFML::Render(m_window);
	m_window.display();
}

void Game::updateGUI()
{
	if (m_deltaTime.asMicroseconds() <= 0) m_deltaTime = sf::seconds(0.1f);
	ImGui::SFML::Update(m_window, m_deltaTime);
	ImGui::Begin("Hello, world!");
	ImGui::InputInt("Row", &input, 1, 1);
	if (input != 0)
	{
		std::cout << input << std::endl;
	}
	ImGui::End();	
}