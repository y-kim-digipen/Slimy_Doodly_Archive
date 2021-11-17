/*--------------------------------------------------------------
File Name: Menu.cpp
Project: Slimy Doodly
Author: Haneul Lee, Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "Menu.h"

#include "../Engine/Engine.h"
#include "World.h"
#include "Screens.h"

#if _DEBUG
static const bool isDebug = true;
#else
static const bool isDebug = false;
#endif
Menu::Menu() : downKey(Input::KeyboardButton::S), upKey(Input::KeyboardButton::W), chooseKey(Input::KeyboardButton::Space), this_menu(Menu::Selections::Start)
{

}

void Menu::Load()
{
    Engine::GetLogger().LogEvent("Load " + GetName());
    World::Instance().Load(World::Levels::Menu);
    images.push_back(new doodle::Image("assets/Sprites/bg.png"));
    images.push_back(new doodle::Image("assets/Menu/post_it.png"));
    images.push_back(new doodle::Image("assets/Menu/Title.png"));
    images.push_back(new doodle::Image("assets/Menu/ButtonPlay.png"));
    images.push_back(new doodle::Image("assets/Menu/ButtonCredits.png"));
    images.push_back(new doodle::Image("assets/Menu/ButtonQuit.png"));
    images.push_back(new doodle::Image("assets/Menu/ButtonPlaySelect.png"));
    images.push_back(new doodle::Image("assets/Menu/ButtonCreditsSelect.png"));
    images.push_back(new doodle::Image("assets/Menu/ButtonQuitSelect.png"));
    images.push_back(new doodle::Image("assets/Menu/Pencil.png"));
    images.push_back(new doodle::Image("assets/Menu/Instructions.png"));
    images.push_back(new doodle::Image("assets/Menu/ButtonOption.png"));
    images.push_back(new doodle::Image("assets/Menu/ButtonOptionSelect.png"));
}

void Menu::Update([[maybe_unused]] const double dt)
{
    if (downKey.IsKeyRelease())
    {
        Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
        switch (this_menu)
        {
        case Selections::Start:
            this_menu = Selections::Option;
            break;
        case Selections::Option:
            this_menu = Selections::Credit;
            break;
        case Selections::Credit:
            this_menu = Selections::Exit;
            break;
        case Selections::Exit:
            this_menu = Selections::Start;
            break;
        }
    }
    else if (upKey.IsKeyRelease())
    {
        Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
        switch (this_menu)
        {
        case Selections::Start:
            this_menu = Selections::Exit;
            break;
        case Selections::Option:
            this_menu = Selections::Start;
            break;
        case Selections::Credit:
            this_menu = Selections::Option;
            break;
        case Selections::Exit:
            this_menu = Selections::Credit;
            break;\
        }
    }  
    else if (chooseKey.IsKeyRelease())
    {
        Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
        switch (this_menu)
        {
        case Selections::Start:
            Engine::GetGameStateManager().SetNextState(LEVELSELECT);
            break;
        case Selections::Option:
            Engine::GetGameStateManager().SetNextState(OPTIONS);
            break;
        case Selections::Credit:
            Engine::GetGameStateManager().SetNextState(CREDIT);
            break;
        case Selections::Exit:
            Engine::GetGameStateManager().Shutdown();
            break;

        }
    }
}

void Menu::Draw()
{
    using namespace doodle;
    if (images.size() != 0)
    {
        push_settings();
        clear_background(0x000000ff);
        set_image_mode(RectMode::Center);
        draw_image(*images[0], static_cast<double>(Engine::GetWindow().GetSize().x / 2), static_cast<double>(Engine::GetWindow().GetSize().y / 2));
        draw_image(*images[1], static_cast<double>(Engine::GetWindow().GetSize().x / 2), static_cast<double>(Engine::GetWindow().GetSize().y / 2) - 120, static_cast<double>(Engine::GetWindow().GetSize().x), static_cast<double>(Engine::GetWindow().GetSize().y));
        draw_image(*images[2], static_cast<double>(Engine::GetWindow().GetSize().x / 2), static_cast<double>(Engine::GetWindow().GetSize().y) / 6 * 5, 450, 180);
        draw_image(*images[10], static_cast<double>(Engine::GetWindow().GetSize().x / 2) - 500, static_cast<double>(Engine::GetWindow().GetSize().y) / 3 * 2, 500, 450);

        switch (this_menu)
        {
        case Selections::Start:
            draw_image(*images[6], Engine::GetWindow().GetSize().x / 2, static_cast<double>(Engine::GetWindow().GetSize().y) / 6 * 4 - 20, 308, 91);
            draw_image(*images[11], Engine::GetWindow().GetSize().x / 2, static_cast<double>(Engine::GetWindow().GetSize().y) / 6 * 3 - 20, 308, 91);
            draw_image(*images[4], Engine::GetWindow().GetSize().x / 2, static_cast<double>(Engine::GetWindow().GetSize().y) / 6 * 2 - 20, 308, 91);
            draw_image(*images[5], Engine::GetWindow().GetSize().x / 2, static_cast<double>(Engine::GetWindow().GetSize().y) / 6 * 1 - 20, 308, 91);
            push_settings();
            apply_translate(Engine::GetWindow().GetSize().x / 2 + 200.0, static_cast<double>(Engine::GetWindow().GetSize().y) / 6 * 4 + 70);
            apply_rotate(PI / 6);
            draw_image(*images[9], 0, 0, 388, 72);
            pop_settings();
            break;
        case Selections::Option://11, 12
            draw_image(*images[3], Engine::GetWindow().GetSize().x / 2, static_cast<double>(Engine::GetWindow().GetSize().y) / 6 * 4 - 20, 308, 91);
            draw_image(*images[12], Engine::GetWindow().GetSize().x / 2, static_cast<double>(Engine::GetWindow().GetSize().y) / 6 * 3 - 20, 308, 91);
            draw_image(*images[4], Engine::GetWindow().GetSize().x / 2, static_cast<double>(Engine::GetWindow().GetSize().y) / 6 * 2 - 20, 308, 91);
            draw_image(*images[5], Engine::GetWindow().GetSize().x / 2, static_cast<double>(Engine::GetWindow().GetSize().y) / 6 * 1 - 20, 308, 91);
            push_settings();
            apply_translate(Engine::GetWindow().GetSize().x / 2 + 200.0, static_cast<double>(Engine::GetWindow().GetSize().y) / 6 * 3 + 70);
            apply_rotate(PI / 6);
            draw_image(*images[9], 0, 0, 388, 72);
            pop_settings();
            break;
        case Selections::Credit:
            draw_image(*images[3], Engine::GetWindow().GetSize().x / 2, static_cast<double>(Engine::GetWindow().GetSize().y) / 6 * 4 - 20, 308, 91);
            draw_image(*images[11], Engine::GetWindow().GetSize().x / 2, static_cast<double>(Engine::GetWindow().GetSize().y) / 6 * 3 - 20, 308, 91);
            draw_image(*images[7], Engine::GetWindow().GetSize().x / 2, static_cast<double>(Engine::GetWindow().GetSize().y) / 6 * 2 - 20, 308, 91);
            draw_image(*images[5], Engine::GetWindow().GetSize().x / 2, static_cast<double>(Engine::GetWindow().GetSize().y) / 6 * 1 - 20, 308, 91);
            push_settings();
            apply_translate(Engine::GetWindow().GetSize().x / 2 + 200.0, static_cast<double>(Engine::GetWindow().GetSize().y) / 6 * 2 + 70);
            apply_rotate(PI / 6);
            draw_image(*images[9], 0, 0, 388, 72);
            pop_settings();
            break;
        case Selections::Exit:
            draw_image(*images[3], Engine::GetWindow().GetSize().x / 2, static_cast<double>(Engine::GetWindow().GetSize().y) / 6 * 4 - 20, 308, 91);
            draw_image(*images[11], Engine::GetWindow().GetSize().x / 2, static_cast<double>(Engine::GetWindow().GetSize().y) / 6 * 3 - 20, 308, 91);
            draw_image(*images[4], Engine::GetWindow().GetSize().x / 2, static_cast<double>(Engine::GetWindow().GetSize().y) / 6 * 2 - 20, 308, 91);
            draw_image(*images[8], Engine::GetWindow().GetSize().x / 2, static_cast<double>(Engine::GetWindow().GetSize().y) / 6 * 1 - 20, 308, 91);
            push_settings();
            apply_translate(Engine::GetWindow().GetSize().x / 2 + 200.0, static_cast<double>(Engine::GetWindow().GetSize().y) / 6 * 1 + 70);
            apply_rotate(PI / 6);
            draw_image(*images[9], 0, 0, 388, 72);
            pop_settings();
            break;
        }
        pop_settings();
    }
}

void Menu::Unload()
{
    for (doodle::Image* imaging : images)
    {
        delete imaging;
    }
    images.clear();
    Engine::GetLogger().LogEvent("Unload " + GetName());

}
