/*--------------------------------------------------------------
File Name: Level2.cpp
Project: Slimy Doodly
Author: Hoseob Jeong, Yoonki Kim
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "Level2.h"

#include "../Engine/Engine.h"
#include "World.h"
#include "Screens.h"
#if _DEBUG
static const bool isDebug = true;
#else
static const bool isDebug = false;
#endif

Level2::Level2() : keyReset(Input::KeyboardButton::R), keyShutDown(Input::KeyboardButton::Escape),  keytonextlevel(Input::KeyboardButton::Enter)
{}

void Level2::Load()
{
    Engine::GetLogger().LogEvent("Load " + GetName());
    World::Instance().Load(World::Levels::Level2);
}

void Level2::Update(const double dt)
{
    if (keyShutDown.IsKeyRelease())
    {
        World::GetUI().m_setResume();
    }

    if (keyReset.IsKeyRelease())
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
    if constexpr (isDebug == true)
    {
        if (keytonextlevel.IsKeyRelease())
        {
            Engine::GetGameStateManager().SetNextState(LEVEL3);
        }

    }
    World::Instance().Update(dt);
}

void Level2::Draw()
{
    World::Instance().Draw();
}

void Level2::Unload()
{

}
