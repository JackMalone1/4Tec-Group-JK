#include "Audio.h"

/// <summary>
/// This constructor creates the Audio object and calls the Setup() function and the playBackgroundMusic() 
/// function because these need to be called before anything else happens
/// </summary>
Audio::Audio()
{
	setup();
	playBackgroundMusic();
}

/// <summary>
/// When called, this simply plays the Checker placing sound effect
/// </summary>
void Audio::playCheckerSFX()
{
	m_checker.play();
}

/// <summary>
/// When called, this simply plays the selection placing sound effect
/// </summary>
void Audio::playSelectionSFX()
{
	m_selection.play();
}

/// <summary>
/// We use this to easily set the volume of the Music in game by passing in the % of voloume from 0 - 100%
/// </summary>
/// <param name="t_vol">Volume</param>
void Audio::setMusicVolume(int t_vol)
{
	m_background.setVolume(t_vol);
}

/// <summary>
/// We use this to easily set the volume of the Sound Effect in the game by passing in the % of voloume from 0 - 100%
/// </summary>
/// <param name="t_vol">Volume</param>
void Audio::setSFXVolume(int t_vol)
{
	m_checker.setVolume(t_vol);
	m_selection.setVolume(t_vol);
}

/// <summary>
/// When called, this simply plays the background music used in the game
/// </summary>
void Audio::playBackgroundMusic()
{
	m_background.play();
}

/// <summary>
/// This function is used to load the buffer for the checker and 
/// selection sound effects and opening the background music from the file
/// 
/// We also use this to set the volume of the music to 25 by default 
/// and to put the music on a loop 
/// </summary>
void Audio::setup()
{
	if (!m_checkerBuffer.loadFromFile("ASSETS//AUDIO//BoopBoop.wav"))
	{
		std::cout << "|| The checker placing sound effect doesn't work \n|| Check Audio.cpp to see if the file directory is correct" << std::endl;
	}
	else
	{
		m_checker.setBuffer(m_checkerBuffer);
	}

	if (!m_selectionBuffer.loadFromFile("ASSETS//AUDIO//SelectBoopBoop.wav"))
	{
		std::cout << "|| The selection sound effect doesn't work \n|| Check Audio.cpp to see if the file directory is correct" << std::endl;
	}
	else
	{
		m_selection.setBuffer(m_selectionBuffer);
	}

	if (!m_background.openFromFile("ASSETS//AUDIO//BackgroundMusic.wav"))
	{
		std::cout << "|| The background music doesn't work \n|| Check Audio.cpp to see if the file directory is correct" << std::endl;
	}
	else
	{
		m_background.setVolume(25);
		m_background.setLoop(1);
	}
}