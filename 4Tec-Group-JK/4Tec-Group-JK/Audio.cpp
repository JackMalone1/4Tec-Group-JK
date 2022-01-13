#include "Audio.h"

Audio::Audio()
{
	setup();
	playBackgroundMusic();
}

Audio::~Audio()
{
}

void Audio::playCheckerSFX()
{
	m_checker.play();
}

void Audio::playSelectionSFX()
{
	m_selection.play();
}

void Audio::setMusicVolume(int t_vol)
{
	m_background.setVolume(t_vol);
}

void Audio::setSFXVolume(int t_vol)
{
	m_checker.setVolume(t_vol);
	m_selection.setVolume(t_vol);
}

void Audio::playBackgroundMusic()
{
	m_background.play();
}

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