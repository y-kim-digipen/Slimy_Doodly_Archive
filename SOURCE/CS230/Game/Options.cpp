/*--------------------------------------------------------------
File Name: Options.cpp
Project: Slimy Doodly
Author: Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "Options.h"
#include "../Engine/Engine.h"
#include "World.h"
#include "Screens.h"

#if _DEBUG
static const bool isDebug = true;
#else
static const bool isDebug = false;
#endif

Options::Options() : keyReset(Input::KeyboardButton::R), keyShutDown(Input::KeyboardButton::Escape), keytonextlevel(Input::KeyboardButton::Enter)
{

}

void Options::Load()
{
    Engine::GetLogger().LogEvent("Load " + GetName());
    //World::Instance().Load(World::Levels::Tutorial);
    World::GetUI().m_OptionsInit();
    bg = new doodle::Image("assets/Sprites/bg.png");
    optionsImage = new doodle::Image("assets/UI/OptionsUI.png");
}

void Options::Update([[maybe_unused]] double dt)
{
    if (keyShutDown.IsKeyRelease())
    {
        Engine::GetGameStateManager().SetNextState(MENU);
    }


    if constexpr (isDebug == true)
    {
        if (keytonextlevel.IsKeyRelease())
        {
            Engine::GetGameStateManager().SetNextState(TUTORIAL);
        }

    }

    World::GetUI().m_OptionsUpdate();

}

void Options::Draw()
{
    doodle::clear_background(0x000000ff);
    doodle::draw_image(*bg, 0, 0);
    doodle::draw_image(*optionsImage, Engine::GetWindow().GetSize().x / 2 - 350.0, Engine::GetWindow().GetSize().y - 150.0, 700, 150);

    World::GetUI().m_OptionsDraw();
    //World::Instance().Draw();
}

void Options::Unload()
{
    World::GetUI().m_OptionsUnload();
    delete bg;
    delete optionsImage;
}
