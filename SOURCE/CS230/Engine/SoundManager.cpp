/*--------------------------------------------------------------
File Name: SoundManager.cpp
Project: Slimy Doodly
Author: Haneul Lee
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "SoundManager.h"

void SoundManager::LoadSFX(std::string filePath)
{
	sf::SoundBuffer new_SFX;
	new_SFX.loadFromFile(filePath);
	SFXs.push_back(new_SFX);
}

void SoundManager::LoadBGM(std::string filePath)
{
	sf::SoundBuffer new_BGM;
	new_BGM.loadFromFile(filePath);
	BGMs.push_back(new_BGM);
}

void SoundManager::SetBGMBuffer(int index)
{
	BGM.setBuffer(BGMs[index]);
}

void SoundManager::SetSFXBuffer(int index)
{
	{
		SFX.setBuffer(SFXs[index]);
	}
}

void SoundManager::PlayBGM()
{
	if (BGM_on) {
		BGM.play();
		BGM.setLoop(true);
	}
	else
	{
		BGM.stop();
	}
}

void SoundManager::PlaySFX()
{
	if (SFX_on) {
		SFX.play();
	}
}

void SoundManager::PlayBGM(std::string filePath)
{
	if (BGM_on) {
		BGM_music.openFromFile(filePath);
		BGM_music.play();
	}
}

void SoundManager::PlaySFX(std::string filePath)
{
	if (SFX_on) {
		SFX_music.openFromFile(filePath);
		SFX_music.play();
	}
}

void SoundManager::PauseBGM()
{
	BGM.pause();
}

void SoundManager::PauseSFX()
{
	SFX.pause();
}

void SoundManager::StopBGM()
{
	BGM.stop();
}

void SoundManager::StopSFX()
{
	SFX.stop();
}

void SoundManager::Clear()
{
	if (BGMs.size() != 0)
	{
		if (BGM.getStatus() != sf::Sound::Stopped)
		{
			BGM.stop();
		}
		BGMs.clear();
	}
	if (SFXs.size() != 0)
	{
		if (SFX.getStatus() != sf::Sound::Stopped)
		{
			SFX.stop();
		}
		SFXs.clear();
	}
}

void SoundManager::SetSFX()
{
	SFX_on = !SFX_on;
}

void SoundManager::SetBGM()
{
	BGM_on = !BGM_on;
}

bool SoundManager::GetSFX()
{
	return SFX_on;
}

bool SoundManager::GetBGM()
{
	return BGM_on;
}
