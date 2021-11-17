/*--------------------------------------------------------------
File Name: Splash.h
Project: Slimy Doodly
Author: Yoonki Kim
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "../Engine/Texture.h"		//Texture
#include "../Engine/GameState.h"	//GameState
#include "../Engine/Timer/Timer.h"	//Timer

class Splash : public GameState {
public:
	Splash();
	void Load() override;
	void Update(double) override;
	void Draw() override;
	void Unload() override;

	std::string GetName() override { return "Splash"; }

private:
	Texture* DigipenLogo;
	std::unique_ptr<Timer> endTimer;
	static const double splashScreenLifeTime;
};

