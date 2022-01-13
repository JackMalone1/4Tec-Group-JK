#ifndef GAME_HPP
#define GAME_HPP
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Audio.h"
#include "Board.h"
#include "Checker.h"
#include "Globals.h"

/// <summary>
/// This class Controls the main game loop of the game.
/// </summary>
class Game
{
public:
    Game();
    ~Game();
    void run();

private:

    sf::Time m_deltaTime;
    sf::Vector2i m_mousePos;
    sf::RenderWindow m_window; // main SFML window

    Board* m_board;
    Audio m_audio;

    void processEvents();
    void processKeys(sf::Event t_event);
    void update(sf::Time t_deltaTime);
    void render();
    void updateGUI();

    int row = 1;
    int col = 1;
    int board = 1;
    int musicVol = 25;
    int sfxVol = 100;

    bool m_exitGame; // control exiting game
    bool playingGame = false;

    const float fps{ 60.0f };
};
#endif // !GAME_HPP