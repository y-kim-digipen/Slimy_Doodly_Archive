/*--------------------------------------------------------------
File Name: Splash.cpp
Project: Slimy Doodly
Author: Yoonki Kim
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "Splash.h"
#include "Screens.h"				//LEVEL1
#include "../Engine/Engine.h"		//Engine

const double Splash::splashScreenLifeTime = 3.0;

Splash::Splash() : DigipenLogo(nullptr)
{}

void Splash::Load()
{
	Engine::GetLogger().LogEvent("Load " + GetName());

	DigipenLogo = Engine::GetTextureManager().Load("Assets/Sprites/DigiPen_BLACK_1024px.png");
	endTimer = std::make_unique<Timer>(splashScreenLifeTime);
	endTimer->Init();
}

void Splash::Update(const double dt)
{
	endTimer->Update(dt);
	
	if(endTimer->IsSettedTime() == true)
	{
		Engine::GetGameStateManager().SetNextState(MENU);
	}
}

void Splash::Draw()
{
	Engine::GetWindow().Clear(White);

	DigipenLogo->Draw(TranslateMatrix{ (Engine::GetWindow().GetSize() - DigipenLogo->GetSize()) / 2.0 },
		{0, 0}, DigipenLogo->GetSize());
}

void Splash::Unload()
{
	Engine::GetLogger().LogEvent("Unload " + GetName());
}
