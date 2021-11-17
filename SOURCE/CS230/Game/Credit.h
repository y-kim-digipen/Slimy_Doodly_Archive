/*--------------------------------------------------------------
File Name: Credit.h
Project: Slimy Doodly
Author: Haneul Lee
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "../Engine/GameState.h"	//Base Class GameState
#include "../Engine/Input.h"
#include "../Engine/TextureManager.h"
#include "doodle/doodle.hpp"

class Credit : public GameState
{
public:
	Credit();
	void Load() override;
	void Update(double dt) override;
	void Draw() override;
	void Unload() override;

	std::string GetName() override { return "Credit"; }

private:
	std::vector<doodle::Image*> images;

	Input::InputKey restartKey;
};