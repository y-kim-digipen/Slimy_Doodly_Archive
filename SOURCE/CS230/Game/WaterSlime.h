/*--------------------------------------------------------------
File Name: WaterSlime.h
Project: Slimy Doodly
Author: Haneul Lee
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "SlimeObject.h"
#include "GameObject.h"
#include "SlimeMovements.h"

class WaterSlime : public SlimeObject {
public:
	WaterSlime(Vector2D startPos, Vector2D size, SlimeMovements& movement_class);
};