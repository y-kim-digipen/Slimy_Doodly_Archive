/*--------------------------------------------------------------
File Name: LavaTile.cpp
Project: Slimy Doodly
Author: Hoseob Jeong, Haneul Lee
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "LavaTile.h"

#include <doodle/drawing.hpp>

#include "Screens.h"
#include "World.h"
#include "WaterSlime.h"
#include "NormalSlime.h"
#include "MimicSlime.h"
#include "../Engine/Engine.h"
#include "LavaTileAnim.h"

LavaTile::LavaTile(Rect rect, int row, int column) : Tile(rect, row, column), timer(0.3) {}



void LavaTile::Draw(TransformMatrix cameraMatrix)
{

	objectMatrix = TranslateMatrix{ {rect.bottomLeft} };
	sprite.Draw(cameraMatrix * objectMatrix * ScaleMatrix{ {0.3, 0.30986} });
	

}


void LavaTile::Update([[maybe_unused]] double dt)
{

	sprite.Update(dt);
	CollisionInteract(dt);
	timer.Update(dt);
}

void LavaTile::CollisionInteract([[maybe_unused]] double dt)
{
	slimeinteract = false;
		for (int i = 0; i < World::GetObjects().GetGameObjectStorage().size(); i++)
	{
			
			GameObject* target = World::GetObjects().GetGameObjectStorage()[i];
			
				if (dynamic_cast<WaterSlime*>(target))
				{

					if (IsCollision(target->GetPosition()) == true)
					{
						slimehitted = true;
						if (slimehitted == true && slimeinteract == false)
						{
							Engine::GetSoundManager().PlaySFX("Assets/SFX/melt.wav");
							slimeinteract = true;
							sprite.PlayAnimation(static_cast<int>(LavaTile_Anm::Change_Anim));
							timer.Init();
							World::GetObjects().Erase(i);
							slimedead = true;		
							World::GetParticleEmitter(1).Emit(1,GetCenter()+Vector2D(0, GetHeight()/2), Vector2D(), Vector2D(0,1), 0);
						}
					}
					else
					{
						slimehitted = false;
					}
				}
				if (dynamic_cast<NormalSlime*>(target))
				{
					if (IsCollision(target->GetPosition()) == true)
					{
						Engine::GetSoundManager().PlaySFX("Assets/SFX/melt.wav");
						slimehitted = true;
						if (slimehitted == true && slimeinteract == false)
						{
							slimeinteract = true;
							World::GetObjects().Erase(i);
							World::GetParticleEmitter(1).Emit(1, GetCenter() + Vector2D(0, GetHeight() / 2), Vector2D(), Vector2D(0, 1), 0);
						}
					}
					else
					{
						slimehitted = false;
					}
				}
				if (dynamic_cast<MimicSlime*>(target))
				{
					if (IsCollision(target->GetPosition()) == true)
					{
						Engine::GetSoundManager().PlaySFX("Assets/SFX/melt.wav");
						slimehitted = true;
						if (slimehitted == true && slimeinteract == false)
						{
							slimeinteract = true;
							World::GetObjects().Erase(i);
							World::GetParticleEmitter(1).Emit(1, GetCenter() + Vector2D(0, GetHeight() / 2), Vector2D(), Vector2D(0, 1), 0);
						}
					}
					else
					{
						slimehitted = false;
					}
				}
				if (dynamic_cast<Player*>(target))
				{
					if (IsCollision(target->GetPosition() + Vector2D(0, target->GetSize().y / 3)) == true)
					{
						slimehitted = true;
						if (slimehitted == true && slimeinteract == false)
						{
							slimeinteract = true;
							if (World::Instance().IsCheatMode() == false)
							{
						Engine::GetSoundManager().PlaySFX("Assets/SFX/melt.wav");
								target->MakeDead();
								World::GetObjects().Erase(i);
								World::GetParticleEmitter(1).Emit(1, GetCenter() + Vector2D(0, GetHeight() / 2), Vector2D(), Vector2D(0, 1), 0);
							}
						}
					}
					else
					{
						slimehitted = false;
					}
				}
				if ( slimedead == true && timer.IsSettedTime() == true)
				{
					World::GetTileManager().ChangeTile(GetRow(), GetColumn());
				}
	}
		
}

void LavaTile::Load()
{
	sprite.Load("Assets/ScriptSprites/LavaTile.spt");
    sprite.PlayAnimation(static_cast<int>(LavaTile_Anm::Move_Anim));
}
