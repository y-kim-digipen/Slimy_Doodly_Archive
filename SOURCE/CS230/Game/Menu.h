/*--------------------------------------------------------------
File Name: Menu.h
Project: Slimy Doodly
Author: Haneul Lee, Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "../Engine/GameState.h"	//Base Class GameState
#include "../Engine/Input.h"
#include "../Engine/TextureManager.h"
#include "doodle/doodle.hpp"

class Menu : public GameState
{
public:
	Menu();
	void Load() override;
	void Update(double dt) override;
	void Draw() override;
	void Unload() override;

	std::string GetName() override { return "Menu"; }

private:
	Input::InputKey downKey;
	Input::InputKey upKey;
	Input::InputKey chooseKey;

	enum class Selections {
		Start, Option, Credit, Exit,
	};

	std::vector<doodle::Image*> images; 

	Selections this_menu;
};

