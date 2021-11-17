/*--------------------------------------------------------------
File Name: World.cpp
Project: Slimy Doodly
Author: Yoonki Kim, Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"   //Engine::GetWindow()
#include "World.h"
#include "Player.h"             //to static cast player to base class
#include "../Engine/Texture.h"

World::World() : gravityConstant(1270), gameZoom(2.0), cameraZoomRatio(gameZoom), zoomOutKey(Mouse::MouseButton::Right), hardmodeOn(false), cheatcodeOn(false), CheatModeKey(Input::KeyboardButton::I)
{}

void World::Load(Levels lvl)
{
    for (ParticleEmitter& particleEmitter : particleEmitters)
    {
        particleEmitter.Clear();
    }
    particleEmitters.clear();

    for(auto& script : scripts)
    {
        delete script;
    }
    scripts.clear();

    GetObjects().Unload();
    //reset tileManager
    GetTileManager().Unload();
    camera = { 0, 0 };
    backGround = Engine::GetTextureManager().Load("assets/Sprites/bg.png");
    particleEmitters.push_back(ParticleEmitter("assets/ScriptSprites/Wave.spt", 3, 0.49));
    particleEmitters.push_back(ParticleEmitter("assets/ScriptSprites/Shutterstock.spt", 3, 0.49));
    switch(lvl)
    {
    case Levels::Menu:
        UI.Init();
        break;
    case Levels::Tutorial:
         {
        GetTileManager().Load("Assets/Tutorial/Tutorial.Map");
        GetObjects().Load("Assets/Tutorial/Tutorial.lvl");
        AddScripts(new ScriptTexture("Basic", { 50, 200 }, 0.3));
        AddScripts(new ScriptTexture("script1", { 200, 300 }, 0.3));
        AddScripts(new ScriptTexture("script2", { 400, 200 }, 0.3));
        AddScripts(new ScriptTexture("script3", { 620, 230 }, 0.3));
        AddScripts(new ScriptTexture("script4", { 900, 260 }, 0.3));
        UI.Init();
        return;
         }
    case Levels::Level1:
        {
        GetTileManager().Load("Assets/Level1/Level1.Map");
        GetObjects().Load("Assets/Level1/Level1.lvl");
        AddScripts(new ScriptTexture("script5", { 150, 300 }, 0.3));
        UI.Init();
        return;
        }
    case Levels::Level2:
    {
        GetTileManager().Load("Assets/Level2/Level2.Map");
        GetObjects().Load("Assets/Level2/Level2.lvl");
        AddScripts(new ScriptTexture("script7", { 150, 300 }, 0.3));
        AddScripts(new ScriptTexture("script6", { 620, 230 }, 0.3));
        UI.Init();
        return;
    }
    case Levels::Level3:
    {
        GetTileManager().Load("Assets/Level3/Level3.Map");
        GetObjects().Load("Assets/Level3/Level3.lvl");
        UI.Init();
        return;
    }
    case Levels::Level4:
    {
        GetTileManager().Load("Assets/Level4/Level4.Map");
        GetObjects().Load("Assets/Level4/Level4.lvl");
        UI.Init();
        return;
    }
    case Levels::Level5:
    {
        GetTileManager().Load("Assets/Level5/Level5.Map");
        GetObjects().Load("Assets/Level5/Level5.lvl");
        UI.Init();
        return;
    }
    }
}

void World::Update(double dt)
{
   
    if (UI.m_IsResume() == false)
    {
        if (GetObjects().GetPlayer()->GetIsDead() == false)
        {
            if (zoomOutKey.IsKeyDown())
            {
                if (cameraZoomRatio > 1)
                {
                    cameraZoomRatio -= 0.1;
                }
            }
            else
            {
                if (cameraZoomRatio <= gameZoom)
                {
                    cameraZoomRatio += 0.1;
                }
            }
        }
        GetTileManager().Update(dt);
        GetObjects().UpdateAll(dt);
        UpdateCameraMove(static_cast<GameObject*>(GetObjects().GetPlayer()));
    }
    UI.Update(dt);

    if (CheatModeKey.IsKeyRelease() == true)
    {
        SetCheatCode();
    }
}

void World::Draw()
{
    Engine::GetWindow().Clear(doodle::HexColor{ 0xFFFFFFFF });

    TransformMatrix cameraMatrix = TranslateMatrix(-camera) * ScaleMatrix { Vector2D(cameraZoomRatio, cameraZoomRatio) };
    backGround->Draw(cameraMatrix * TranslateMatrix{Vector2D{-150, -150}});
    GetTileManager().Draw(cameraMatrix );
    for(auto script : scripts)
    {
        script->Draw(cameraMatrix);
    }
    GetObjects().DrawAll(cameraMatrix);
    if (GetObjects().GetPlayer()->GetIsDead() == true)
    {
        Vector2D winSize = Engine::GetWindow().GetSize()();
        std::string deadUIString = "You're Dead, Press 'R' to restart";
        doodle::push_settings();
        double fontSize = 80;
        doodle::set_font(fontID);
        doodle::set_font_size(fontSize);
        doodle::set_fill_color(doodle::HexColor{ 0x000000FF });
        doodle::draw_text(deadUIString, winSize.x / 2 - fontSize* deadUIString.size()/10- 60, winSize.y / 2);
        doodle::pop_settings();    

        UI.m_SetPlayerisDead();
    }
    if (IsCheatMode() == true)
    {
        Vector2D winSize = Engine::GetWindow().GetSize()();
        std::string CHEATMODE = "cheat Mode!!";
        doodle::push_settings();
        double fontSize = 60;
        doodle::set_font(fontID);
        doodle::set_font_size(fontSize);
        doodle::set_fill_color(doodle::HexColor{ 0xFF0000FF });
        doodle::draw_text(CHEATMODE, winSize.x / 2 - fontSize * CHEATMODE.size() / 10 - 60, winSize.y - 90);
        doodle::pop_settings();

    }
    if(UI.m_IsLevelClear() == true)
    {
        UI.m_TrasitionDraw();
    }
    if (UI.m_IsResume() == true)
    {
        UI.m_ResumeDraw();
    }
    UI.Draw();
}

void World::UpdateCameraMove(const GameObject* followingObject)
{
        const Vector2D objectPosition = followingObject->GetPosition();
        const Vector2D windowSize = Engine::GetWindow().GetSize()();
        const Vector2D cameraTargetPos = (objectPosition * cameraZoomRatio - (windowSize * 0.5 + Vector2D(0, -windowSize.y * 0.2)));

        auto lerp = [cameraTargetPos](Vector2D curCamPos, double ratio)
        {
            return curCamPos + (cameraTargetPos - curCamPos) * ratio;
        };
        camera = lerp(camera, 0.7);
}
