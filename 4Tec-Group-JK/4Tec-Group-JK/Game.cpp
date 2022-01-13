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

/// <summary>
/// This function creates all the IMGUI UI elements and adds their functionality
/// </summary>
void Game::updateGUI()
{
	static ImGuiID dockspaceID = 0;
	static bool winOpenWish = true;

	ImGui::SetNextWindowPos(sf::Vector2f(0, 0)); // Sets the position of the next window that will be created
	ImGui::SetNextWindowSize(sf::Vector2f(G_WINDOW_WIDTH, G_WINDOW_HEIGHT)); // Sets the size of the next window that will be created

	if (playingGame)
	{
		if (ImGui::Begin("Master Window", &winOpenWish)) // Creates a master window in IMGUI
		{
			ImGui::TextUnformatted("Boards"); // Creates text that reads "Boards"
		}

		dockspaceID = ImGui::GetID("HUB_DockSpace"); // Declare Central dockspace
		ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode);

		ImGui::End(); // Ends the creation of the window and its functionality

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

			if (ImGui::Button("Select Square", sf::Vector2f(100.0f, 100.0f))) // Creates a button called "Select Square"
			{
				if (m_board->placePiece(row - 1, col - 1, board - 1)) // Places a piece on the board
				{
					m_audio.playCheckerSFX(); // Play a sound effect for placing a piece on the board
					if (m_board->gameOver()) playingGame = false; // Needs to check if the game is over after each players turn
					m_board->aiTurn(); // The AI takes its turn 
					if (m_board->gameOver()) playingGame = false; // Needs to check if the game is over after each players turn
				}
			}
		}
		ImGui::End(); // Ends the creation of the window and its functionality

		if (ImGui::Begin("Exit")) // Creates an Exit window that we have docked in the UI
		{
			if (ImGui::Button("Quit Game")) // Creates a button called "Quit Game"
			{
				m_audio.playSelectionSFX(); // Plays a selection sound effect 
				m_window.close(); // Closes the window
			}
		}
		ImGui::End(); // Ends the creation of the window and its functionality

		ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
		if (ImGui::Begin("Settings")) // Creates a settings window which we have docked in the UI
		{
			if (ImGui::SliderInt("Music Volume", &musicVol, 0, 100)) // Set the volume of the Music using a slider
			{
				m_audio.playSelectionSFX(); // Plays a selection sound effect 
				m_audio.setMusicVolume(musicVol); // Changes the volume of the music
			}

			if (ImGui::SliderInt("SFX Volume", &sfxVol, 0, 100)) // Set the volume of the Sound Effects using a slider
			{
				m_audio.playSelectionSFX(); // Plays a selection sound effect 
				m_audio.setSFXVolume(sfxVol); // Changes the volume of the sound effects
			}
		}
		ImGui::End(); // Ends the creation of the window and its functionality
	}

	if (!playingGame)
    {
        ImGui::Begin("Difficulty level"); // Creates a window called "Difficulty Level"

        if (ImGui::Button("Easy", sf::Vector2f(100.0f, 100.0f))) // Creates a button called "Easy"
        {
            delete m_board; //Removes the previous board game

            m_board = new Board(m_window); // Create a new board
            m_board->updateDisplayOfBoard();

            m_board->m_ai.SetMaxDepth(2); 
            playingGame = true;

			m_audio.playSelectionSFX(); // Plays a selection sound effect 
        }
        else if (ImGui::Button("Medium", sf::Vector2f(100.0f, 100.0f)))
        {
            delete m_board; //Removes the previous board game

            m_board = new Board(m_window); // Create a new board
            m_board->updateDisplayOfBoard();

            m_board->m_ai.SetMaxDepth(1);
            playingGame = true;

			m_audio.playSelectionSFX(); // Plays a selection sound effect 
        }
        else if (ImGui::Button("Hard", sf::Vector2f(100.0f, 100.0f)))
        {
            delete m_board; //Removes the previous board game

            m_board = new Board(m_window); // Create a new board
            m_board->updateDisplayOfBoard();

            m_board->m_ai.SetMaxDepth(3);
            playingGame = true;

			m_audio.playSelectionSFX(); // Plays a selection sound effect 
        }

        ImGui::End(); // Ends the creation of the window and its functionality
    }
 }