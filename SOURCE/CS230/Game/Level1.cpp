/*--------------------------------------------------------------
File Name: Level1.cpp
Project: Slimy Doodly
Author: Yoonki Kim, Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "Level1.h"

#include "../Engine/Engine.h"
#include "World.h"
#include "Screens.h"
#if _DEBUG
static const bool isDebug = true;
#else
static const bool isDebug = false;
#endif

Level1::Level1() : keyReset(Input::KeyboardButton::R), keyShutDown(Input::KeyboardButton::Escape), keytonextlevel(Input::KeyboardButton::Enter)
{}

void Level1::Load()
{
    Engine::GetLogger().LogEvent("Load " + GetName());
    World::Instance().Load(World::Levels::Level1);
}

void Level1::Update(const double dt)
{
    if (keyShutDown.IsKeyRelease())
    {
        World::GetUI().m_setResume();
    }

    if(keyReset.IsKeyRelease())
    {
        if (World::Instance().IsHardMode() == true)
        {
            World::GetUI().m_ResetTime();
            Engine::GetGameStateManager().SetNextState(TUTORIAL);
        }
        else
        {
            Engine::GetGameStateManager().ReloadState();
        }
        World::GetUI().m_AttemptAdd();
    }
    if constexpr (isDebug == true )
    {
        if (keytonextlevel.IsKeyRelease())
        {
            Engine::GetGameStateManager().SetNextState(LEVEL2);
        }

    }
    World::Instance().Update(dt);
}

void Level1::Draw()
{
    World::Instance().Draw();
}

void Level1::Unload()
{

}
