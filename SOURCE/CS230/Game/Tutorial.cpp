/*--------------------------------------------------------------
File Name: Tutorial.cpp
Project: Slimy Doodly
Author: Haneul Lee, Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "Tutorial.h"
#include "../Engine/Engine.h"
#include "World.h"
#include "Screens.h"

#if _DEBUG
static const bool isDebug = true;
#else
static const bool isDebug = false;
#endif

Tutorial::Tutorial() : keyReset(Input::KeyboardButton::R), keyShutDown(Input::KeyboardButton::Escape), keytonextlevel(Input::KeyboardButton::Enter)
{}

void Tutorial::Load()
{
	Engine::GetLogger().LogEvent("Load " + GetName());
	World::Instance().Load(World::Levels::Tutorial);
}

void Tutorial::Update(double dt)
{
    if (keyShutDown.IsKeyRelease())
    {
        //Engine::GetGameStateManager().SetNextState(LEVELSELECT);
        World::GetUI().m_setResume();
    }

    if (keyReset.IsKeyRelease())
    {
        if (World::Instance().IsHardMode() == true)
        {
            World::GetUI().m_ResetTime();
            Engine::GetGameStateManager().SetNextState(LEVEL1);
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
            Engine::GetGameStateManager().SetNextState(LEVEL1);
        }

    }
    World::Instance().Update(dt);

}

void Tutorial::Draw()
{
    World::Instance().Draw();
}

void Tutorial::Unload()
{
   
}
