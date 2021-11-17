/*--------------------------------------------------------------
File Name: Options.h
Project: Slimy Doodly
Author: Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "../Engine/GameState.h"	//Base Class GameState
#include "../Engine/Input.h"
#include "GameObjectManager.h"		//GameObject
#include <vector>
#include <map>
#include <string>
class Options : public GameState
{

public:
	Options();
	void Load() override;
	void Update(double dt) override;
	void Draw() override;
	void Unload() override;

	std::string GetName() override { return "Options"; }

private:
	Input::InputKey keyReset;
	Input::InputKey keyShutDown;
	Input::InputKey keytonextlevel;
	doodle::Image* bg = nullptr;
	doodle::Image* optionsImage = nullptr;
};

