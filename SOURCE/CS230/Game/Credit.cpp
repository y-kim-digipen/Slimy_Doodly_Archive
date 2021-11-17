/*--------------------------------------------------------------
File Name: Credit.cpp
Project: Slimy Doodly
Author: Haneul Lee
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "Credit.h"

#include "../Engine/Engine.h"
#include "World.h"
#include "Screens.h"	

Credit::Credit() : restartKey(Input::KeyboardButton::Space)
{
	
}

void Credit::Load()
{
	Engine::GetLogger().LogEvent("Load " + GetName());
	World::Instance().Load(World::Levels::Ending);
	images.push_back(new doodle::Image("assets/Credit/Credit_Screen.png"));
}

void Credit::Update([[maybe_unused]] const double dt)
{
	if (restartKey.IsKeyRelease())
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
		Engine::GetGameStateManager().SetNextState(MENU);
	}
}

void Credit::Draw()
{
	using namespace doodle;
	push_settings();
	clear_background(0x000000ff);
	set_image_mode(RectMode::Center);
	draw_image(*images[0], Engine::GetWindow().GetSize().x / 2, Engine::GetWindow().GetSize().y / 2, Engine::GetWindow().GetSize().x, Engine::GetWindow().GetSize().y);
	set_font_size(18);
	set_fill_color(HexColor(0xaaffaaff));
	draw_text("Press SpaceBar to get back to main menu.", Engine::GetWindow().GetSize().x / 2 - 230.0, 0);
	pop_settings();
}

void Credit::Unload()
{
	Engine::GetLogger().LogEvent("Unload " + GetName());
	for (doodle::Image* imaging : images)
	{
		delete imaging;
	}
	images.clear();
}