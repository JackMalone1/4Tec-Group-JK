#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <SFML/Audio.hpp>
#include <iostream>

class Audio
{
public:

	Audio();
	~Audio();

	void playCheckerSFX();
	void playSelectionSFX();
	void setMusicVolume(int t_vol);
	void setSFXVolume(int t_vol);

private:

	void playBackgroundMusic();
	void setup();

	sf::SoundBuffer m_checkerBuffer;
	sf::SoundBuffer m_selectionBuffer;
	sf::Sound m_checker;
	sf::Sound m_selection;
	sf::Music m_background;
};
#endif