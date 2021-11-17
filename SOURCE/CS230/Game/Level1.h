/*--------------------------------------------------------------
File Name: Level1.h
Project: Slimy Doodly
Author: Yoonki Kim, Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "../Engine/GameState.h"	//Base Class GameState
#include "../Engine/Input.h"
#include "BackGround.h"
#include "GameObjectManager.h"		//GameObject
#include "ScriptTexture.h"

class Level1 : public GameState
{

public:
	Level1();
	void Load() override;
	void Update(double dt) override;
	void Draw() override;
	void Unload() override;

	std::string GetName() override { return "Level1"; }

private:
	Input::InputKey keyReset;
	Input::InputKey keyShutDown;
	Input::InputKey keytonextlevel;
};

