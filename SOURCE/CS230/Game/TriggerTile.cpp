/*--------------------------------------------------------------
File Name: TriggerTile.cpp
Project: Slimy Doodly
Author: Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "TriggerTile.h"

#include <doodle/drawing.hpp>

#include "Screens.h"
//#include "../World.h"
#include "World.h"
#include "../Engine/Engine.h"
#include "doodle/doodle.hpp"
#include <fstream>
#include "NormalSlime.h"
#include "WaterSlime.h"
#include "LavaSlime.h"
#include "MimicSlime.h"
#include "SlimeMovements.h"
#include "ObjectSize.h"

TriggerTile::TriggerTile(Rect rect, int row, int column, Trigger_style type) : Tile(rect, row, column), style(type), triggerscript(row, column, type) {}

void TriggerTile::Draw(TransformMatrix cameraMatrix)
{
	objectMatrix = TranslateMatrix{ {rect.bottomLeft} };
	sprite.Draw(cameraMatrix * objectMatrix * ScaleMatrix{ {0.3, 0.38986} });

}

void TriggerTile::Update([[maybe_unused]] double dt)
{
	sprite.Update(dt);
	Collisioncheck();
	CollisionInteract(dt);
	objecthitted = false;
}


void TriggerTile::CollisionInteract(double)
{
	
	if (style == Trigger_style::Construct)
	{
		if (objecthitted == true && objectIsinteract == false)
		{
			objectIsinteract = true;


			for (int i = 0; i < triggerscript.GetStorage().size(); i++)
			{
				World::GetTileManager().SetNewTile(triggerscript.GetStorage()[i].first, triggerscript.GetStorage()[i].second);
			}
			sprite.PlayAnimation(1);
		}

		if (objecthitted == false && objectIsinteract == true)
		{
			std::cout << "intreact out" << std::endl;
			objectIsinteract = false;
			for (int i = 0; i < triggerscript.GetStorage().size(); i++)
			{
				World::GetTileManager().DeleteTile(triggerscript.GetStorage()[i].first, triggerscript.GetStorage()[i].second);

			}
			sprite.PlayAnimation(0);
		}
	}


	if (style == Trigger_style::Door)
	{
		if (objecthitted == true && objectIsinteract == false)
		{
			objectIsinteract = true;


			for (int i = 0; i < triggerscript.GetStorage().size(); i++)
			{
				World::GetTileManager().DeleteTile(triggerscript.GetStorage()[i].first, triggerscript.GetStorage()[i].second);
			}
			sprite.PlayAnimation(1);
		}

		if (objecthitted == false && objectIsinteract == true)
		{
			objectIsinteract = false;
			for (int i = 0; i < triggerscript.GetStorage().size(); i++)
			{
				World::GetTileManager().SetNewTile(triggerscript.GetStorage()[i].first, triggerscript.GetStorage()[i].second);
			}
			sprite.PlayAnimation(0);
		}

	}


	if (style == Trigger_style::SlimeRepawn)
	{
		if (objecthitted == true && objectIsinteract == false)
		{
			objectIsinteract = true;
			sprite.PlayAnimation(1);
	
			for (int i = 0; i < triggerscript.GetStorage().size(); i++)
			{
				SlimeMovements movements;
				if (triggerscript.GetSlimeName(i) == "NormalSlime")
				{
					NormalSlime* pt = new NormalSlime({ static_cast<double>(triggerscript.GetStorage()[i].first), static_cast<double>(triggerscript.GetStorage()[i].second) }, { SlimeSize_X, SlimeSize_Y }, movements);
					World::GetObjects().Add(pt);
					trackofslime = dynamic_cast<SlimeObject*>(pt);
				}
				else if (triggerscript.GetSlimeName(i) == "WaterSlime")
				{
					WaterSlime* pt = new WaterSlime({ static_cast<double>(triggerscript.GetStorage()[i].first), static_cast<double>(triggerscript.GetStorage()[i].second) }, { SlimeSize_X, SlimeSize_Y }, movements);
					World::GetObjects().Add(pt);
					trackofslime = dynamic_cast<SlimeObject*>(pt);
				}
				else if (triggerscript.GetSlimeName(i) == "LavaSlime")
				{
					LavaSlime* pt = new LavaSlime({ static_cast<double>(triggerscript.GetStorage()[i].first), static_cast<double>(triggerscript.GetStorage()[i].second) }, { SlimeSize_X, SlimeSize_Y }, movements);
					World::GetObjects().Add(pt);
					trackofslime = dynamic_cast<SlimeObject*>(pt);
				}
				else if (triggerscript.GetSlimeName(i) == "MimicSlime")
				{
					MimicSlime* pt = new MimicSlime({ static_cast<double>(triggerscript.GetStorage()[i].first), static_cast<double>(triggerscript.GetStorage()[i].second) }, { SlimeSize_X, SlimeSize_Y }, movements);
					World::GetObjects().Add(pt);
					trackofslime = dynamic_cast<SlimeObject*>(pt);
				}
			}
		
		}
		if (trackofslime != nullptr)
		{
			if (trackofslime->GetIsDead() == true)
			{
				objectIsinteract = false;
				sprite.PlayAnimation(0);
				delete trackofslime;
				trackofslime = nullptr;
			}
		}
	}
}

void TriggerTile::Load()
{
	sprite.Load("Assets/ScriptSprites/TriggerTile.spt");
	triggerscript.Load();
	sprite.PlayAnimation(0);
}


void TriggerTile::Collisioncheck()
{
	for (int i = 0; i < World::GetObjects().GetGameObjectStorage().size(); i++)
	{

		GameObject* target = World::GetObjects().GetGameObjectStorage()[i];
		if (IsCollision(target->GetPosition()) == true)
		{
			objecthitted = true;
		}
	}

}

