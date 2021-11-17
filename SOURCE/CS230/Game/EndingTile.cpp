/*--------------------------------------------------------------
File Name: EndingTile.cpp
Project: Slimy Doodly
Author: Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "EndingTile.h"

#include <doodle/drawing.hpp>

#include "Screens.h"
#include "World.h"
#include "../Engine/Engine.h"
#include "doodle/doodle.hpp"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Tutorial.h"
#include "Level5.h"

EndingTile::EndingTile(Rect rect, int row, int column) : Tile(rect, row, column) {}

void EndingTile::Draw(TransformMatrix cameraMatrix)
{
		objectMatrix = TranslateMatrix{ {rect.bottomLeft} };
		sprite.Draw(cameraMatrix * objectMatrix * ScaleMatrix{ {0.3, 0.24986} });
	
}





void EndingTile::Update([[maybe_unused]] double dt)
{
	collisioncheck();
	if (playerhitted == true && Isinteract == false)
	{
		Isinteract = true;
		levelclear = true;
		World::GetUI().m_SavetheRecord();
	}
	if (playerhitted == true)
	{
		CollisionInteract(dt);
	}
	sprite.Update(dt);
}

void EndingTile::CollisionInteract(double)
{

	if (dynamic_cast<Tutorial*>(Engine::GetGameStateManager().GetCurrState()))
	{
		
		World::GetUI().m_SetLevelClear(true);
		if (World::Instance().IsHardMode() == false)
		{
			World::GetUI().m_setLevelIsClearStorage(1);
		}
		if (World::GetUI().m_GetClickNextLevel() == true)
		{
			Engine::GetGameStateManager().SetNextState(LEVEL1);
		}
		if (World::GetUI().m_GetClickRetry() == true)
		{
			Engine::GetGameStateManager().ReloadState();
		}
		if (World::GetUI().m_GetClickMenu() == true)
		{
			Engine::GetGameStateManager().SetNextState(MENU);
		}
	}
	if (dynamic_cast<Level1*>(Engine::GetGameStateManager().GetCurrState()))
	{
		World::GetUI().m_SetLevelClear(true);
		if (World::Instance().IsHardMode() == false)
		{
			World::GetUI().m_setLevelIsClearStorage(2);
		}
		if (World::GetUI().m_GetClickNextLevel() == true)
		{
			Engine::GetGameStateManager().SetNextState(LEVEL2);
		}
		if (World::GetUI().m_GetClickRetry() == true)
		{
			Engine::GetGameStateManager().ReloadState();
		}
		if (World::GetUI().m_GetClickMenu() == true)
		{
			Engine::GetGameStateManager().SetNextState(MENU);
		}
	}
	if (dynamic_cast<Level2*>(Engine::GetGameStateManager().GetCurrState()))
	{
		World::GetUI().m_SetLevelClear(true);
		if (World::Instance().IsHardMode() == false)
		{
			World::GetUI().m_setLevelIsClearStorage(3);
		}
		if (World::GetUI().m_GetClickNextLevel() == true)
		{
			Engine::GetGameStateManager().SetNextState(LEVEL3);
		}
		if (World::GetUI().m_GetClickRetry() == true)
		{
			Engine::GetGameStateManager().ReloadState();
		}
		if (World::GetUI().m_GetClickMenu() == true)
		{
			Engine::GetGameStateManager().SetNextState(MENU);
		}
	}
	if (dynamic_cast<Level3*>(Engine::GetGameStateManager().GetCurrState()))
	{
		World::GetUI().m_SetLevelClear(true);
		if (World::Instance().IsHardMode() == false)
		{
			World::GetUI().m_setLevelIsClearStorage(4);
		}
		if (World::GetUI().m_GetClickNextLevel() == true) 
		{
			Engine::GetGameStateManager().SetNextState(LEVEL4);
		}
		if (World::GetUI().m_GetClickRetry() == true)
		{
			Engine::GetGameStateManager().ReloadState();
		}
		if (World::GetUI().m_GetClickMenu() == true)
		{
			Engine::GetGameStateManager().SetNextState(MENU);
		}
	}
	if (dynamic_cast<Level4*>(Engine::GetGameStateManager().GetCurrState()))
	{
		World::GetUI().m_SetLevelClear(true);
		if (World::Instance().IsHardMode() == false)
		{
			World::GetUI().m_setLevelIsClearStorage(5);
		}
		if (World::GetUI().m_GetClickNextLevel() == true)
		{
			Engine::GetGameStateManager().SetNextState(LEVEL5);
		}
		if (World::GetUI().m_GetClickRetry() == true)
		{
			Engine::GetGameStateManager().ReloadState();
		}
		if (World::GetUI().m_GetClickMenu() == true)
		{
			Engine::GetGameStateManager().SetNextState(MENU);
		}


	}
	if (dynamic_cast<Level5*>(Engine::GetGameStateManager().GetCurrState()))
	{
		World::GetUI().m_SetLevelClear(true);


		if (World::GetUI().m_GetClickNextLevel() == true)
		{
			Engine::GetGameStateManager().SetNextState(CREDIT);
		}
		if (World::GetUI().m_GetClickRetry() == true)
		{
			Engine::GetGameStateManager().ReloadState();
		}
		if (World::GetUI().m_GetClickMenu() == true)
		{
			Engine::GetGameStateManager().SetNextState(MENU);
		}


	}
	if (levelclear == true)
	{
		levelclear = false;
		World::GetUI().Savefile();
	}
}

void EndingTile::Load()
{
	sprite.Load("Assets/ScriptSprites/EndingTile.spt");
}

void EndingTile::collisioncheck()
{
	for (int i = 0; i < World::GetObjects().GetGameObjectStorage().size(); i++)
	{

		GameObject* target = World::GetObjects().GetGameObjectStorage()[i];
		if (dynamic_cast<Player*>(target))
		{
			if (IsCollision(target->GetPosition()) == true)
			{
				playerhitted = true;
			}
			else
			{
				playerhitted = false;
			}
		}
	}


}

