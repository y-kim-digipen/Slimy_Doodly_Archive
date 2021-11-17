/*--------------------------------------------------------------
File Name: main.cpp
Project: Slimy Doodly
Author: Yoonki Kim, Hoseob Jeong, Haneul Lee
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include <exception>	// std::exception

#include "Engine/Engine.h"		//Engine
#include "Game/Splash.h"		//Splash
#include "Game/Menu.h"			//Menu
#include "Game/Level1.h"		//Level1
#include "Game/Level2.h"		//Level2
#include "Game/Level3.h"		//Level3
#include "Game/Level4.h"		//Level4
#include "Game/Level5.h"		//Level5
#include "Game/Credit.h"		//Ending
#include "Game/Tutorial.h"
#include "Game/LevelSelect.h"
#include "Game/Options.h"
int main(void) {
	Engine& engine = Engine::Instance();

	doodle::show_cursor(false);
	try {
		engine.Init("Slimy_Doodly");
		Splash splash;
		Menu menu;
		LevelSelect levelselect;
		Options options;
		Level1 level1;
		Level2 level2;
		Level3 level3;
		Level4 level4;
		Level5 level5;
		Tutorial tutorial;
		Credit credit;

		engine.GetGameStateManager().AddGameState(splash);
		engine.GetGameStateManager().AddGameState(menu);
		engine.GetGameStateManager().AddGameState(options);
		engine.GetGameStateManager().AddGameState(levelselect);
		engine.GetGameStateManager().AddGameState(tutorial);
		engine.GetGameStateManager().AddGameState(level1);
		engine.GetGameStateManager().AddGameState(level2);
		engine.GetGameStateManager().AddGameState(level3);
		engine.GetGameStateManager().AddGameState(level4);
		engine.GetGameStateManager().AddGameState(level5);
		engine.GetGameStateManager().AddGameState(credit);

		Engine::GetSoundManager().LoadBGM("Assets/SFX/slimy_doodly_bgm.wav");
		Engine::GetSoundManager().SetBGMBuffer(0);
		Engine::GetSoundManager().PlayBGM();

		while (engine.HasGameEnded() == false) 
		{
			engine.Update();
		}

		engine.Shutdown();
		return 0;
	} catch (std::exception & e) {
		Engine::GetLogger().LogError(e.what());
		return -1;
	}
}