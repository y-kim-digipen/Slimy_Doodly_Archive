/*--------------------------------------------------------------
File Name: LavaSlime.h
Project: Slimy Doodly
Author: Haneul Lee
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "GameObject.h"
#include "SlimeMovements.h"
#include "SlimeObject.h"

class LavaSlime : public SlimeObject {
public:
	LavaSlime(Vector2D startPos, Vector2D size, SlimeMovements& movement_class);
};