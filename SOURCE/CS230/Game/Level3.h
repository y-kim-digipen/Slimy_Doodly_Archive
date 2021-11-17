/*--------------------------------------------------------------
File Name: Level3.h
Project: Slimy Doodly
Author: Hoseob Jeong, Yoonki Kim
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "../Engine/GameState.h"	//Base Class GameState
#include "../Engine/Input.h"
#include "BackGround.h"
#include "GameObjectManager.h"		//GameObject

class Level3 : public GameState
{

public:
	Level3();
	void Load() override;
	void Update(double dt) override;
	void Draw() override;
	void Unload() override;

	std::string GetName() override { return "Level3"; }

private:
	Input::InputKey keyReset;
	Input::InputKey keyShutDown;
	Input::InputKey keytonextlevel;
};