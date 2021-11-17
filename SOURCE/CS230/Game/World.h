/*--------------------------------------------------------------
File Name: World.h
Project: Slimy Doodly
Author: Yoonki Kim, Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "GameObjectManager.h"  //GameObjectManager
#include "Particle.h"
#include "ScriptTexture.h"
#include "Tilemanager.h"
#include "UI.h"
class World
{
public:
    typedef Vector2D Camera;
    enum class Levels
    {
        None, Menu, Tutorial ,Level1, Level2, Level3, Level4, Level5 , Ending,
    };
    World();
    ~World() {};
    void Load(Levels lvl);
    void Update(double dt);
    void Draw();
    static World& Instance() { static World instance; return instance; }
    static GameObjectManager& GetObjects() { return Instance().objects; }
    static Tilemanager& GetTileManager() { return Instance().tileManager; }
    static ParticleEmitter& GetParticleEmitter(int particleType) { return Instance().particleEmitters[particleType]; }
    static UI& GetUI() { return Instance().UI; }
    double GetGravityConstant() const { return gravityConstant; }
    double GetCameraZoomRatio() const { return  cameraZoomRatio; }
    [[nodiscard]] Vector2D GetCamera() const { return camera; }
    double GetZoom() const { return cameraZoomRatio; };
    void AddScripts(ScriptTexture* script) { scripts.emplace_back(script); }
    void SetHardMode() { hardmodeOn = !hardmodeOn; GetUI().m_ResetAttempt(); }
    bool IsHardMode() { return hardmodeOn; }
    void SetCheatCode() { cheatcodeOn = !cheatcodeOn; }
    bool IsCheatMode() { return cheatcodeOn; }

private:
    Mouse::InputKey zoomOutKey;
    GameObjectManager objects;
    Tilemanager tileManager;
    Camera camera;
    Texture* backGround = nullptr;
    bool hardmodeOn;
    bool cheatcodeOn;
    double gameZoom;
    double cameraZoomRatio;
    void UpdateCameraMove(const GameObject* followingObject);
    double gravityConstant;
    UI UI;
    const int fontID = doodle::create_distance_field_bitmap_font("Assets/Fonts/fonts.fnt");
    std::vector<ScriptTexture*> scripts;
    std::vector<ParticleEmitter> particleEmitters;
    Input::InputKey CheatModeKey;
};

