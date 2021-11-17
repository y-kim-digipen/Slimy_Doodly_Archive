/*--------------------------------------------------------------
File Name: SoundManager.h
Project: Slimy Doodly
Author: Haneul Lee
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "SFML/Audio.hpp"
#include "SFML/Config.hpp"
#include "SFML/System.hpp"

class SoundManager {
public:
	void LoadSFX(std::string filePath);
	void LoadBGM(std::string filePath);
	void SetBGMBuffer(int index);
	void SetSFXBuffer(int index);
	void PlayBGM();
	void PlaySFX();
	void PlayBGM(std::string filePath);
	void PlaySFX(std::string filePath);
	void PauseBGM();
	void PauseSFX();
	void StopBGM();
	void StopSFX();
	void Clear();

	void SetSFX();
	void SetBGM();
	bool GetSFX();
	bool GetBGM();

private:
	std::vector<sf::SoundBuffer> SFXs;
	sf::Sound SFX;
	sf::Music SFX_music;
	std::vector<sf::SoundBuffer> BGMs;
	sf::Sound BGM;
	sf::Music BGM_music;

	bool SFX_on = true;
	bool BGM_on = true;
};