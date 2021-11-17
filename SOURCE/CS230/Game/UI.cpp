/*--------------------------------------------------------------
File Name: UI.cpp
Project: Slimy Doodly
Author: Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS // for MSVC, it doesn't like this function
#include <cstdlib>
#include "UI.h"
#include "../Engine/BasicDataTypes.h"
#include "../Engine/Engine.h"
#include <string>
#include <fstream>
#include "../Game/Screens.h"
#include "World.h"
#include <filesystem>

UI::UI()
{
	trasition =  new doodle::Image("Assets/UI/Clear.png");
	choose = new doodle::Image("Assets/UI/Circle.png");
	Timeui = new doodle::Image("Assets/UI/TimeUI.png");
	Attemptui = new doodle::Image("Assets/UI/AttemptUI.png");
	ReturnMenuUI = new doodle::Image("Assets/UI/MENUUI.png");
	ResumeUI = new doodle::Image("Assets/UI/ResumeUI.png");

	levelstatus = LEVELSELECTER::Tutorial;
	choosing = ClearScreen::Next;
	optionstatus = E_OPTIONS::BGM;
	resumestatus = RESUME::RESUME;
	WinSize = Engine::GetWindow().GetSize()();
	trasition_center = { WinSize.x / 2 - trasition_Width / 2 ,WinSize.y / 2 - trasition_Height / 2 };
	CurrentLevelPosition = { trasition_center.x + 300,trasition_center.y + 300 };
	AttemptPosition = { trasition_center.x + 400,trasition_center.y + 200 };
	TimePosition = { trasition_center.x + 250, trasition_center.y + 100 };
	LevelDrawPosition = { WinSize.x/5 , 2 *WinSize.y / 3 };
	OptionDrawPosition = { WinSize.x / 2 -100, WinSize.y / 2 };
	
}
void UI::Init()
{
	if (World::Instance().IsHardMode() == false)
	{
		D_times = 0.0;
	}
	D_PlayerStatus = false;
	D_IsLevelClear = false;
	D_ClickNextLevel = false;
	D_ClickMenu = false;
	D_ClickRetry = false;
}

void UI::m_AttemptAdd()
{
	D_attempttime += 1;
}


void UI::m_ResetTime()
{
	D_times = 0.0;
}

void UI::m_TimeAdd(double dt)
{
	if (D_PlayerStatus == false && D_IsLevelClear == false && D_IsResume == false)
	{
		D_times += dt;
	}
}

void UI::m_ResetAttempt()
{
	D_attempttime = 0;
}

void UI::Update(double dt)
{
	m_TimeAdd(dt);
}

void UI::Draw()
{
	double fontSizes = 100;
	double Correction_Values = 20;
	Vector2D WinSizes = Engine::GetWindow().GetSize()();
	Vector2D AttemptPositions = { 0.0,WinSizes.y - fontSizes- Correction_Values };
	Vector2D TimePositions = { 4*WinSizes.x/5,  WinSizes.y - fontSizes- Correction_Values };
	doodle::push_settings();
	doodle::set_font(fontID);
	doodle::set_font_size(fontSizes);
	doodle::set_fill_color(doodle::HexColor{ 0x0000FFFF });
	doodle::set_outline_color(doodle::HexColor{ 0x000000FF });
	doodle::draw_image(*Attemptui, AttemptPositions.x, AttemptPositions.y+30,240,80);
	doodle::draw_image(*Timeui, TimePositions.x, TimePositions.y+30, 160, 80);
	doodle::draw_text("            " + std::to_string(D_attempttime), AttemptPositions.x, AttemptPositions.y +15);
	doodle::draw_text("         "+ std::to_string(static_cast<int>(D_times)) , TimePositions.x, TimePositions.y+15);
	if(World::Instance().IsHardMode())
	{
		doodle::push_settings();
		doodle::no_outline();
		doodle::set_fill_color(doodle::HexColor{ 0xFF0000FF });
		doodle::set_font_size(fontSize / 2);
		doodle::draw_text("Hard Mode" , TimePositions.x, TimePositions.y - 50);
		doodle::pop_settings();
	}
	doodle::pop_settings();
}

void UI::m_SetPlayerisDead()
{
	D_PlayerStatus = true;
}

void UI::m_SavetheRecord()
{
	std::pair<int, double> recording;
	recording.first = D_attempttime;
	recording.second = D_times;
	Record.emplace_back(recording);
}

void UI::m_TrasitionDraw()
{
	WinSize = Engine::GetWindow().GetSize()();
	trasition_center = { WinSize.x / 2 - trasition_Width / 2 ,WinSize.y / 2 - trasition_Height / 2 };
	CurrentLevelPosition = { trasition_center.x + 300,trasition_center.y + 300 };
	AttemptPosition = { trasition_center.x + 400,trasition_center.y + 200 };
	TimePosition = { trasition_center.x + 250, trasition_center.y + 100 };
	LevelDrawPosition = { WinSize.x / 5 , 2 * WinSize.y / 3 };

    CirclePosition = { trasition_center.x + 90, trasition_center.y + 20 };
	choosing = choosing % 3;

	if (LeftKey.IsKeyRelease() == true)
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
		choosing = static_cast<ClearScreen>(static_cast<int>(choosing) - 1);
	}
	if (RightKey.IsKeyRelease() == true)
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
		choosing = static_cast<ClearScreen>(static_cast<int>(choosing) + 1);
	}

	switch (choosing)
	{
	case ClearScreen::Menu:
		CirclePosition = { trasition_center.x + 90, trasition_center.y + 20 };
		break;
	case ClearScreen::Next:
		CirclePosition = { trasition_center.x + 415, trasition_center.y + 20 };
		break;
	case ClearScreen::Retry:
		CirclePosition = { trasition_center.x + 270, trasition_center.y + 20 };
		break;
	}

	doodle::push_settings();
	doodle::set_font(fontID);
	doodle::set_font_size(fontSize);
	doodle::set_fill_color(doodle::HexColor{ 0x000000FF });
	doodle::draw_image(*trasition, WinSize.x / 2 - trasition_Width /2, WinSize.y /2 - trasition_Height/2, trasition_Width, trasition_Height);
	doodle::draw_text(  Engine::GetGameStateManager().GetCurrState()->GetName(), CurrentLevelPosition.x, CurrentLevelPosition.y);
	doodle::draw_text(  std::to_string((Record.end()-1)->first), AttemptPosition.x, AttemptPosition.y);
	doodle::draw_text( std::to_string((Record.end()-1)->second)+" Sec", TimePosition.x, TimePosition.y);
	if(World::Instance().IsHardMode())
	{
		doodle::push_settings();
		doodle::draw_text(std::to_string((Record.end() - 1)->first), AttemptPosition.x, AttemptPosition.y);
		doodle::pop_settings();
	}
	doodle::draw_image(*choose, CirclePosition.x, CirclePosition.y, 180,100);
	doodle::pop_settings();

	if (Nextlevelkey.IsKeyRelease())
	{
		D_ClickNextLevel = true;
	}

	if (ChooseKey.IsKeyRelease() == true && choosing == ClearScreen::Next)
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
		D_ClickNextLevel = true;
	}
	if (ChooseKey.IsKeyRelease() == true && choosing == ClearScreen::Retry)
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
		D_ClickRetry = true;
	}
	if (ChooseKey.IsKeyRelease() == true && choosing == ClearScreen::Menu)
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
		D_ClickMenu = true;
	}

	if (static_cast<int>(choosing) < 0)
	{
		choosing = ClearScreen::Next;
	}
}

void UI::m_SetLevelClear(bool set)
{
	D_IsLevelClear = set;
}

bool UI::m_GetClickNextLevel()
{
	return D_ClickNextLevel;
}

bool UI::m_IsLevelClear()
{
	return D_IsLevelClear;
}

bool UI::m_GetClickRetry()
{

	return D_ClickRetry;
}

bool UI::m_GetClickMenu()
{
	return D_ClickMenu;
}

std::vector<bool> UI::m_GetLevelIsClearStorage() const
{
	return LevelIsClearstorage;
}



void UI::m_setLevelIsClearStorage(int i)
{
	if (0 <= i && i < LevelIsClearstorage.size() - 1)
	{
		LevelIsClearstorage[i] = true;
		
	}
	else
	{
		Engine::GetLogger().LogEvent("Wrong range! : levelselect clear data");
	}
}

void UI::m_LevelSelectInit()
{
	pin = new doodle::Image("Assets/UI/Pin.png");
	Locked = new doodle::Image("Assets/UI/Lock.png");
	LevelIsClearstorage.clear();
	char* docdir = getenv("USERPROFILE");
	std::string Savingdir(docdir);
	if (docdir)
	{
		Savingdir += "\\Documents\\slimydoodly";
	}
	std::string Savingpath = Savingdir + "\\save.scv";
	std::string Originfilepath = "Assets/UI/save.scv";

	std::ifstream inFile(Savingpath);
	std::ifstream inFile1(Originfilepath);
	std::string text;
	bool Isclear;

 if (std::filesystem::exists(Savingpath) == true)
	{
	
	if (Savingpath.substr(Savingpath.find_last_of('.')) != ".scv") {
		throw std::runtime_error("Bad Filetype.  " + Savingpath + " not a savefile info file (.scv)");
	}

	if (inFile.is_open() == false) {
		throw std::runtime_error("Failed to load " + Savingpath);
	}
	while (inFile.eof() == false) {
		inFile >> text;
		if (text == "True") {
			inFile >> Isclear;
			LevelIsClearstorage.push_back(Isclear);
		}
		else if (text == "False") {
			inFile >> Isclear;
			LevelIsClearstorage.push_back(Isclear);
		}
		else {
			Engine::GetLogger().LogError("Unknown command " + text);
		}
	}
	}
 else
	{
		if (Originfilepath.substr(Originfilepath.find_last_of('.')) != ".scv") {
			throw std::runtime_error("Bad Filetype.  " + Originfilepath + " not a sprite info file (.scv)");
		}

		if (inFile1.is_open() == false) {
			throw std::runtime_error("Failed to load " + Originfilepath);
		}
		while (inFile1.eof() == false) {
			inFile1 >> text;
			if (text == "True") {
				inFile1 >> Isclear;
				LevelIsClearstorage.push_back(Isclear);
			}
			else if (text == "False") {
				inFile1 >> Isclear;
				LevelIsClearstorage.push_back(Isclear);
			}
			else {
				Engine::GetLogger().LogError("Unknown command " + text);
			}
		}



	}
	
	
	
	levelselect.push_back(new doodle::Image("Assets/UI/TutorialUI.png"));
	for (int i = 1; i < 6; i++)
	{
		levelselect.push_back(new doodle::Image("Assets/UI/Level" + std::to_string(i) + "UI.png"));
	}
	hardmodeimage.push_back(new doodle::Image("Assets/UI/HardMode.png"));
	hardmodeimage.push_back(new doodle::Image("Assets/UI/HardModecheck.png"));
}



void UI::m_LevelSelectUnload()
{
	delete pin;
	delete Locked;
	for (doodle::Image* image : levelselect)
	{
		delete image;
	}
	levelselect.clear();
	for (doodle::Image* image : hardmodeimage)
	{
		delete image;
	}
	hardmodeimage.clear();

}

void UI::m_LevelSelectUpdate()
{
	WinSize = Engine::GetWindow().GetSize()();
	LevelDrawPosition = { WinSize.x / 10,   WinSize.y / 2 };
	levelstatus = levelstatus % 9;
	if (LeftKey.IsKeyRelease() == true)
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
		levelstatus = static_cast<LEVELSELECTER>(static_cast<int>(levelstatus) - 1);
	}
	if (RightKey.IsKeyRelease() == true)
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
		levelstatus = static_cast<LEVELSELECTER>(static_cast<int>(levelstatus) + 1);
	}

	switch (levelstatus)
	{
	case LEVELSELECTER::Tutorial:
		CirclePosition = { LevelDrawPosition.x , LevelDrawPosition.y + 40 };
		break;
	case LEVELSELECTER::Level1:
		CirclePosition = { LevelDrawPosition.x + WinSize.x / 7 * 1, LevelDrawPosition.y + 40 };
		break;
	case LEVELSELECTER::Level2:
		CirclePosition = { LevelDrawPosition.x + WinSize.x / 7 * 2,LevelDrawPosition.y + 40 };
		break;
	case LEVELSELECTER::Level3:
		CirclePosition = { LevelDrawPosition.x + WinSize.x / 7 * 3, LevelDrawPosition.y + 40 };
		break;
	case LEVELSELECTER::Level4:
		CirclePosition = { LevelDrawPosition.x + WinSize.x / 7 * 4, LevelDrawPosition.y + 40 };
		break;
	case LEVELSELECTER::Level5:
		CirclePosition = { LevelDrawPosition.x + WinSize.x / 7 * 5, LevelDrawPosition.y + 40 };
		break;
	case LEVELSELECTER::Menu:
		CirclePosition = { WinSize.x / 2 - 80, 120 };
		break;
	case LEVELSELECTER::HardMode:
		CirclePosition = { WinSize.x / 2 - 80, 220 };
		break;

	}

	if (ChooseKey.IsKeyRelease() == true && levelstatus == LEVELSELECTER::Tutorial)
	{
		if (LevelIsClearstorage[0] == true)
		{
			Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
			Engine::GetGameStateManager().SetNextState(TUTORIAL);
		}
	}
	if (World::Instance().IsHardMode() == false)
	{
		if (ChooseKey.IsKeyRelease() == true && levelstatus == LEVELSELECTER::Level1)
		{
			if (LevelIsClearstorage[1] == true)
			{
				Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
				Engine::GetGameStateManager().SetNextState(LEVEL1);
			}
		}
		if (ChooseKey.IsKeyRelease() == true && levelstatus == LEVELSELECTER::Level2)
		{
			if (LevelIsClearstorage[2] == true)
			{
				Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
				Engine::GetGameStateManager().SetNextState(LEVEL2);
			}
		}
		if (ChooseKey.IsKeyRelease() == true && levelstatus == LEVELSELECTER::Level3)
		{
			if (LevelIsClearstorage[3] == true)
			{
				Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
				Engine::GetGameStateManager().SetNextState(LEVEL3);
			}
		}
		if (ChooseKey.IsKeyRelease() == true && levelstatus == LEVELSELECTER::Level4)
		{
			if (LevelIsClearstorage[4] == true)
			{
				Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
				Engine::GetGameStateManager().SetNextState(LEVEL4);
			}
		}
		if (ChooseKey.IsKeyRelease() == true && levelstatus == LEVELSELECTER::Level5)
		{
			if (LevelIsClearstorage[5] == true)
			{
				Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
				Engine::GetGameStateManager().SetNextState(LEVEL5);
			}
		}
	}
	if (ChooseKey.IsKeyRelease() == true && levelstatus == LEVELSELECTER::Menu)
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
		Engine::GetGameStateManager().SetNextState(MENU);
	}
	if (ChooseKey.IsKeyRelease() == true && levelstatus == LEVELSELECTER::HardMode)
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
		World::Instance().SetHardMode();
	}

	if (static_cast<int>(levelstatus) < 0)
	{
		levelstatus = LEVELSELECTER::Tutorial;
	}
	if (static_cast<int>(levelstatus) > 7)
	{
		levelstatus = LEVELSELECTER::Tutorial;
	}
}


void UI::m_LevelSelectDraw()
{
	WinSize = Engine::GetWindow().GetSize()();
	LevelDrawPosition = { WinSize.x / 10,   WinSize.y / 2 };
	if (levelselect.size() != 0)
	{
		if (World::Instance().IsHardMode() == false)
		{
			for (int i = 0; i < 6; i++)
			{

				if (LevelIsClearstorage[i] == true)
				{
					doodle::draw_image(*levelselect[i], LevelDrawPosition.x + WinSize.x / 7 * i, LevelDrawPosition.y, postitlevel_size, postitlevel_size);
				}
				else
				{
					if (Locked != nullptr)
					{
						doodle::draw_image(*Locked, LevelDrawPosition.x + WinSize.x / 7 * i, LevelDrawPosition.y, postitlevel_size, postitlevel_size);
					}
				}

				if (pin != nullptr)
				{
					doodle::draw_image(*pin, LevelDrawPosition.x + WinSize.x / 7 * i + 70, LevelDrawPosition.y + 125, 30, 30);
				}
			}
		}
		else
		{
			if (LevelIsClearstorage[0] == true)
			{
				doodle::draw_image(*levelselect[0], LevelDrawPosition.x , LevelDrawPosition.y, postitlevel_size, postitlevel_size);
			}
			if (pin != nullptr)
			{
				doodle::draw_image(*pin, LevelDrawPosition.x + 70, LevelDrawPosition.y + 125, 30, 30);
			}
			for (int i = 1; i < 6; i++)
			{
				if (Locked != nullptr)
				{
					doodle::draw_image(*Locked, LevelDrawPosition.x + WinSize.x / 7 * i, LevelDrawPosition.y, postitlevel_size, postitlevel_size);
				}
				if (pin != nullptr)
				{
					doodle::draw_image(*pin, LevelDrawPosition.x + WinSize.x / 7 * i + 70, LevelDrawPosition.y + 125, 30, 30);
				}
			}
		}
	}

	if (World::Instance().IsHardMode() == false)
	{
		doodle::draw_image(*hardmodeimage[0], WinSize.x / 2 - 175, 200, 350, 100);
	}
	else
	{
		doodle::draw_image(*hardmodeimage[1], WinSize.x / 2 - 175, 200, 350, 100);
	}
	doodle::draw_image(*ReturnMenuUI, WinSize.x / 2-150, 100,300, 100);
	doodle::draw_image(*choose, CirclePosition.x, CirclePosition.y, 140, 80);

}

void UI::m_OptionsDraw()
{
	WinSize = Engine::GetWindow().GetSize()();
	OptionDrawPosition = { WinSize.x / 2 - 100 , WinSize.y / 2 };
	if (Optionsimage.size() != 0)
	{
		if (Engine::GetSoundManager().GetBGM() == false)
		{
			doodle::draw_image(*Optionsimage[0], OptionDrawPosition.x, OptionDrawPosition.y + WinSize.y / 7 * 1, 200, 100);
		}
		else
		{
			doodle::draw_image(*Optionsimage[1], OptionDrawPosition.x, OptionDrawPosition.y + WinSize.y / 7 * 1, 200, 100);
		}
		if (Engine::GetSoundManager().GetSFX() == false)
		{
			doodle::draw_image(*Optionsimage[2], OptionDrawPosition.x, OptionDrawPosition.y, 200, 100);
		}
		else
		{
			doodle::draw_image(*Optionsimage[3], OptionDrawPosition.x, OptionDrawPosition.y, 200, 100);
		}
	}
	doodle::draw_image(*ReturnMenuUI, WinSize.x / 2 - 150, 100,  300, 100);

	doodle::draw_image(*choose, CirclePosition.x, CirclePosition.y, 140, 80);


}

void UI::m_OptionsUnload()
{
	for (auto image : Optionsimage)
	{
		delete image;
	}
	Optionsimage.clear();
}

void UI::m_OptionsUpdate()
{
	WinSize = Engine::GetWindow().GetSize()();
	OptionDrawPosition = { WinSize.x / 2-100 , WinSize.y / 2 };

	optionstatus = optionstatus % 3;

	if (UpKey.IsKeyRelease() == true)
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
		optionstatus = static_cast<E_OPTIONS>(static_cast<int>(optionstatus) - 1);
	}
	if (DownKey.IsKeyRelease() == true)
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
		optionstatus = static_cast<E_OPTIONS>(static_cast<int>(optionstatus) + 1);
	}

	switch (optionstatus)
	{
	case E_OPTIONS::BGM:
		CirclePosition = { OptionDrawPosition.x+50 , OptionDrawPosition.y + WinSize.y / 7 * 1 +10 };
		break;
	case E_OPTIONS::SFX:
		CirclePosition = { OptionDrawPosition.x + 50, OptionDrawPosition.y  };
		break;
	case E_OPTIONS::Menu:
		CirclePosition = { WinSize.x / 2 - 150 + 70, 115 };
		break;
	}


	if (ChooseKey.IsKeyRelease() == true && optionstatus == E_OPTIONS::BGM)
	{
		Engine::GetSoundManager().SetBGM();
		Engine::GetSoundManager().PlayBGM();
	}
	if (ChooseKey.IsKeyRelease() == true && optionstatus == E_OPTIONS::SFX)
	{
		Engine::GetSoundManager().SetSFX();
	}
	if (ChooseKey.IsKeyRelease() == true && optionstatus == E_OPTIONS::Menu)
	{
		Engine::GetGameStateManager().SetNextState(MENU);
	}

}

void UI::m_OptionsInit()
{
	Optionsimage.push_back(new doodle::Image("Assets/UI/BGM.png"));
	Optionsimage.push_back(new doodle::Image("Assets/UI/BGMcheck.png"));
	Optionsimage.push_back(new doodle::Image("Assets/UI/SFX.png"));
	Optionsimage.push_back(new doodle::Image("Assets/UI/SFXcheck.png"));
}



void UI::Savefile()
{	
	char* docdir = getenv("USERPROFILE");
	if (docdir)
	{
	std::string Savingdir(docdir);
		Savingdir += "\\Documents\\slimydoodly";

		if (std::filesystem::exists(Savingdir) == false)
		{
			std::filesystem::create_directory(Savingdir);
		}
		std::string Savingpath = Savingdir + "\\save.scv";
		std::ofstream savingfile(Savingpath, std::ios_base::out | std::ios_base::trunc);
		for (int i = 0; i < 6; i++)
		{
			if (LevelIsClearstorage[i] == true)
			{
				savingfile << "True ";
				savingfile << "1\n";
			}
			else if (LevelIsClearstorage[i] == false)
			{
				savingfile << "False ";
				savingfile << "0\n";
			}
		}
		savingfile.close();
		Engine::GetLogger().LogEvent(Engine::GetGameStateManager().GetCurrState()->GetName() + "is clear and save the storage!");
	}
}

void UI::m_ResumeDraw()
{
	WinSize = Engine::GetWindow().GetSize()();
	trasition_center = { WinSize.x / 2 - trasition_Width / 2 ,WinSize.y / 2 - trasition_Height / 2 };
	ResumeDrawPosition = { WinSize.x/2 -150 ,WinSize.y/2 -60};

	resumestatus = resumestatus % 2;

	doodle::draw_image(*ResumeUI, WinSize.x / 2 - trasition_Width / 2, WinSize.y / 2 - trasition_Height / 2, trasition_Width, trasition_Height);
	if (UpKey.IsKeyRelease() == true)
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
		if (static_cast<int>(resumestatus) > 0)
		{
			resumestatus = static_cast<RESUME>(static_cast<int>(resumestatus) - 1);
		}
	}
	if (DownKey.IsKeyRelease() == true)
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/68885__aboe__scribsht4.wav");
		resumestatus = static_cast<RESUME>(static_cast<int>(resumestatus) + 1);
	}
	
	
	switch (resumestatus)
	{
	case RESUME::RESUME:
		CirclePosition = { ResumeDrawPosition.x +30 , ResumeDrawPosition.y + 80 };
		break;
	case RESUME::Menu:
		CirclePosition = { ResumeDrawPosition.x + 30 , ResumeDrawPosition.y  -80 };
		break;
	}
	doodle::draw_image(*choose, CirclePosition.x, CirclePosition.y, 300, 120);

	if (ChooseKey.IsKeyRelease() == true && resumestatus == RESUME::RESUME)
	{
		m_setResume();
	}
	if (ChooseKey.IsKeyRelease() == true && resumestatus == RESUME::Menu)
	{
		Engine::GetGameStateManager().SetNextState(MENU);
		Savefile();
		m_setResume();
	}
}




