/*--------------------------------------------------------------
File Name: SlimeMovements.cpp
Project: Slimy Doodly
Author: Haneul Lee
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "SlimeMovements.h"

void SlimeMovements::Update(double dt)
{
	timer += dt;
	if (currMoveStatus == MoveStatus::Idle)
	{
		if (MoveLeft == true)
		{
			currMoveStatus = MoveStatus::Left;
		}
		else if (MoveRight == true)
		{
			currMoveStatus = MoveStatus::Right;
		}
		else if (Jump_after_moving == true)
		{
			currMoveStatus = MoveStatus::Jump;
		}
	}

	if (MoveLeft == true && currMoveStatus == MoveStatus::Left)
	{
		if (timer > MoveLeftTime)
		{
			currMoveStatus = MoveStatus::Right;
			timer = 0;
		}
	}

	if (MoveRight == true && currMoveStatus == MoveStatus::Right)
	{
		if (timer > MoveLeftTime)
		{
			currMoveStatus = MoveStatus::Left;
			timer = 0;
		}
	}

	if (Jump_after_moving == true && is_jumping_now == false)
	{
		if (timer > (MoveLeftTime + MoveRightTime)/2) {
			is_jumping_now = false;
		}
	}

	if (Jump_after_moving == true)
	{
		if (timer == 0 && is_jumping_now == false) {
			is_jumping_now = true;
			currMoveStatus = MoveStatus::Jump;
		}
	}
}