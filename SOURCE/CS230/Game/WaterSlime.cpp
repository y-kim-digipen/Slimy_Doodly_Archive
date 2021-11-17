/*--------------------------------------------------------------
File Name: WaterSlime.cpp
Project: Slimy Doodly
Author: Haneul Lee
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "WaterSlime.h"
#include "Slime_anm.h"

WaterSlime::WaterSlime(Vector2D startPos, Vector2D size, SlimeMovements& movement_class) : SlimeObject(startPos, size)
{
	sprite.Load("assets/ScriptSprites/WaterSlime.spt");
	timer = 0;
	isFlipped = false;
	velocity = { 0, 0 };
	currState = &stateIdle;
	currState->Enter(this);
	movements = movement_class;
}