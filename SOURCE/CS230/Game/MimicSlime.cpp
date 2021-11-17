/*--------------------------------------------------------------
File Name: MimicSlime.cpp
Project: Slimy Doodly
Author: Haneul Lee
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "MimicSlime.h"
#include "Slime_anm.h"

MimicSlime::MimicSlime(Vector2D startPos, Vector2D size, SlimeMovements& movement_class) : SlimeObject(startPos, size)
{
	sprite.Load("assets/ScriptSprites/MimicSlime.spt");
	timer = 0;
	isFlipped = false;
	velocity = { 0, 0 };
	currState = &stateIdle;
	currState->Enter(this);
	movements = movement_class;
}