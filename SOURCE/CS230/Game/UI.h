/*--------------------------------------------------------------
File Name: UI.h
Project: Slimy Doodly
Author: Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include <doodle/doodle.hpp>
#include <vector>
#include "../Engine/Input.h"
#include "../Engine/Sprite.h"


enum class ClearScreen : int
{
    Menu = 0, Retry, Next,

};

enum class LEVELSELECTER : int
{
    Tutorial =0, Level1, Level2, Level3, Level4, Level5, HardMode, Menu,
};
enum class E_OPTIONS : int
{
    BGM = 0, SFX, Menu,
};
enum class RESUME : int
{
    RESUME = 0, Menu,
};

class UI
{
public:
    UI();
    ~UI()
    {
        delete trasition;
        delete choose;
        delete Timeui;
        delete Attemptui;
        delete ResumeUI;

    }
    void Init();
    void m_AttemptAdd();
    void m_ResetTime();
    void m_TimeAdd(double dt);
    void m_ResetAttempt();
    void Update(double dt);
    void Draw();
    void m_SetPlayerisDead();
    void m_SavetheRecord();
    void m_TrasitionDraw();
    void m_SetLevelClear(bool set);
    bool m_GetClickNextLevel();
    bool m_IsLevelClear();
    bool m_GetClickRetry();
    bool m_GetClickMenu();

    std::vector<bool> m_GetLevelIsClearStorage() const;

    void m_setLevelIsClearStorage(int i);

    void m_LevelSelectInit();
    void m_LevelSelectUpdate();
    void m_LevelSelectUnload();
    void m_LevelSelectDraw();

    void m_OptionsDraw();
    void m_OptionsUnload();
    void m_OptionsUpdate();
    void m_OptionsInit();

    void Savefile();

    void m_ResumeDraw();
    bool m_IsResume() const { return D_IsResume; }
    void m_setResume() { D_IsResume = !D_IsResume; }
private:
    const int fontID = doodle::create_distance_field_bitmap_font("Assets/Fonts/fonts.fnt");
    double D_times = 0;
    int D_attempttime = 1;
    bool D_PlayerStatus = false;
    bool D_IsLevelClear = false;
    bool D_ClickNextLevel = false;
    bool D_ClickMenu = false;
    bool D_ClickRetry = false;
    bool D_IsResume = false;

    std::vector<std::pair<int, double>> Record;
    std::vector<bool>LevelIsClearstorage;
    std::vector<doodle::Image*>levelselect;
    std::vector<doodle::Image*>hardmodeimage;
    std::vector<doodle::Image*>Optionsimage;

    Input::InputKey Nextlevelkey = Input::KeyboardButton::N;

    doodle::Image* trasition = nullptr;
    doodle::Image* choose = nullptr;
    doodle::Image* Attemptui = nullptr;
    doodle::Image* Timeui = nullptr;
    doodle::Image* pin = nullptr;
    doodle::Image* Locked = nullptr;
    doodle::Image* ReturnMenuUI = nullptr;
    doodle::Image* ResumeUI = nullptr;

private:
    Input::InputKey LeftKey = Input::KeyboardButton::A;
    Input::InputKey RightKey = Input::KeyboardButton::D;
    Input::InputKey UpKey = Input::KeyboardButton::W;
    Input::InputKey DownKey = Input::KeyboardButton::S;
    Input::InputKey ChooseKey = Input::KeyboardButton::Space;

    ClearScreen choosing;
    LEVELSELECTER levelstatus;
    E_OPTIONS optionstatus;
    RESUME resumestatus;
    Vector2D CirclePosition;
    const double fontSize = 70;
    const double trasition_Height = 500;
    const double trasition_Width = 600;

    const double postitlevel_size = 150;

    Vector2D WinSize;
    Vector2D trasition_center;
    Vector2D CurrentLevelPosition;
    Vector2D AttemptPosition;
    Vector2D TimePosition;
    Vector2D LevelDrawPosition;
    Vector2D OptionDrawPosition;
    Vector2D ResumeDrawPosition;

};
constexpr ClearScreen operator%(ClearScreen& a, int b)
{
    return static_cast<ClearScreen> (static_cast<int>(a) % b);
}

constexpr LEVELSELECTER operator%(LEVELSELECTER& a, int b)
{
    return static_cast<LEVELSELECTER> (static_cast<int>(a) % b);
}

constexpr E_OPTIONS operator%(E_OPTIONS& a, int b)
{
    return static_cast<E_OPTIONS> (static_cast<int>(a) % b);
}

constexpr RESUME operator%(RESUME& a, int b)
{
    return static_cast<RESUME> (static_cast<int>(a) % b);
}