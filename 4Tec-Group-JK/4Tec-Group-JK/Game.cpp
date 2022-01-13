#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ G_WINDOW_WIDTH, G_WINDOW_HEIGHT, 32U }, "4TEC", sf::Style::None },
	m_exitGame{ false } //when true game will exit
{
	m_window.setFramerateLimit(fps);
	ImGui::SFML::Init(m_window);
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	m_board = new Board(m_window);
	m_board->updateDisplayOfBoard();
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
		// Turn on/off isometric view
		if (event.KeyReleased == event.type && event.key.code == sf::Keyboard::A)
		{
			m_board->switchView();
		}
	}
}

void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_window.close();
	}
}

void Game::update(sf::Time t_deltaTime)
{
	m_deltaTime = t_deltaTime;
	m_board->update();
}

void Game::render()
{
	m_window.clear(sf::Color::White);
	ImGui::SFML::Render(m_window);
	if (playingGame)	m_board->render(m_window);
	m_window.display();
}

void Game::updateGUI()
{
	static ImGuiID dockspaceID = 0;
	static bool winOpenWish = true;

	ImGui::SetNextWindowPos(sf::Vector2f(0, 0));
	ImGui::SetNextWindowSize(sf::Vector2f(G_WINDOW_WIDTH, G_WINDOW_HEIGHT));

	if (playingGame)
	{
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
			if (ImGui::SliderInt("Row", &row, 1, 4))
			{
				m_audio.playSelectionSFX();
			}

			if (ImGui::SliderInt("Col", &col, 1, 4))
			{
				m_audio.playSelectionSFX();
			}

			if(ImGui::SliderInt("Board", &board, 1, 4))
			{
				m_audio.playSelectionSFX();
			}

			if (ImGui::Button("Select Square", sf::Vector2f(100.0f, 100.0f)))
			{
				if (m_board->placePiece(row - 1, col - 1, board - 1))
				{
					m_audio.playCheckerSFX();
					if (m_board->gameOver()) playingGame = false;
					m_board->aiTurn();
					if (m_board->gameOver()) playingGame = false;
				}
			}
		}
		ImGui::End();

		if (ImGui::Begin("Exit"))
		{
			if (ImGui::Button("Quit Game"))
			{
				m_audio.playSelectionSFX();
				m_window.close();
			}
		}
		ImGui::End();

		ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
		if (ImGui::Begin("Settings"))
		{
			if (ImGui::SliderInt("Music Volume", &musicVol, 0, 100))
			{
				m_audio.playSelectionSFX();
				m_audio.setMusicVolume(musicVol);
			}

			if (ImGui::SliderInt("SFX Volume", &sfxVol, 0, 100))
			{
				m_audio.playSelectionSFX();
				m_audio.setSFXVolume(sfxVol);
			}
		}
		ImGui::End();		
	}

	if (!playingGame)
    {
        ImGui::Begin("Difficulty level");

        if (ImGui::Button("Easy", sf::Vector2f(100.0f, 100.0f)))
        {
            delete m_board;

            m_board = new Board(m_window);
            m_board->updateDisplayOfBoard();

            m_board->m_ai.SetMaxDepth(2);
            playingGame = true;

			m_audio.playSelectionSFX();
        }
        else if (ImGui::Button("Medium", sf::Vector2f(100.0f, 100.0f)))
        {
            delete m_board;

            m_board = new Board(m_window);
            m_board->updateDisplayOfBoard();

            m_board->m_ai.SetMaxDepth(1);
            playingGame = true;

			m_audio.playSelectionSFX();
        }
        else if (ImGui::Button("Hard", sf::Vector2f(100.0f, 100.0f)))
        {
            delete m_board;

            m_board = new Board(m_window);
            m_board->updateDisplayOfBoard();

            m_board->m_ai.SetMaxDepth(3);
            playingGame = true;

			m_audio.playSelectionSFX();
        }

        ImGui::End();
    }
 }