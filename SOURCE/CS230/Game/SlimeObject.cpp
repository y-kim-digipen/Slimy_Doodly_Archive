/*--------------------------------------------------------------
File Name: SlimeObject.cpp
Project: Slimy Doodly
Author: Haneul Lee
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "SlimeObject.h"
#include "Slime_anm.h"

const double SlimeObject::jumpVelocity = 400;
const double SlimeObject::xAccel = 30;
const double SlimeObject::xDrag = SlimeObject::xAccel * 1.3;
const double SlimeObject::maxXvelocity = 140;

void SlimeObject::State_Idle::Enter([[maybe_unused]] GameObject* object)
{
	SlimeObject* slime = static_cast<SlimeObject*>(object);
	slime->sprite.PlayAnimation(static_cast<int>(Slime_Anm::None_Anim));

}
void SlimeObject::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
	SlimeObject* slime = static_cast<SlimeObject*>(object);
	if (slime->IsOnGround())
	{
		slime->movements.Update(dt);
	}
	slime->timer += dt;
}
void SlimeObject::State_Idle::TestForExit([[maybe_unused]] GameObject* object)
{
	SlimeObject* slime = static_cast<SlimeObject*>(object);

	if (slime->timer > 0.5)
	{
		slime->timer = 0;
		slime->ChangeState(&slime->stateMoving);
		if (slime->movements.getPrevLeftRightStatus() == MoveStatus::Left)
		{
			slime->movements.setCurrMoveStatus(MoveStatus::Left);
		}
		if (slime->movements.getPrevLeftRightStatus() == MoveStatus::Right)
		{
			slime->movements.setCurrMoveStatus(MoveStatus::Right);
		}
	}
}

void SlimeObject::State_Moving::Enter([[maybe_unused]] GameObject* object)
{
	SlimeObject* slime = static_cast<SlimeObject*>(object);
	slime->sprite.PlayAnimation(static_cast<int>(Slime_Anm::Move_Anim));
	if (slime->movements.getCurrMoveStatus() == MoveStatus::Left)
	{
		slime->isFlipped = false;
	}
	if (slime->movements.getCurrMoveStatus() == MoveStatus::Left)
	{
		slime->isFlipped = true;
	}
}
void SlimeObject::State_Moving::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
	SlimeObject* slime = static_cast<SlimeObject*>(object);
	if (slime->IsOnGround())
	{
		slime->movements.Update(dt);
	}

	if (slime->movements.getCurrMoveStatus() == MoveStatus::Left && slime->IsOnGround())
	{
		slime->isFlipped = false;
		slime->velocity.x -= xAccel * dt;
		if (slime->velocity.x < -maxXvelocity)
		{
			slime->velocity.x = -maxXvelocity;
		}
		if (slime->velocity.x > 0)
		{
			slime->velocity.x = 0;
		}
		slime->movements.setPrevMoveStatus(MoveStatus::Right);
		slime->movements.setPrevLeftRightStatus(MoveStatus::Left);
	}
	if (slime->movements.getCurrMoveStatus() == MoveStatus::Right && slime->IsOnGround())
	{
		slime->isFlipped = true;
		slime->velocity.x += xAccel * dt;
		if (slime->velocity.x > maxXvelocity)
		{
			slime->velocity.x = maxXvelocity;
		}
		if (slime->velocity.x < 0)
		{
			slime->velocity.x = 0;
		}
		slime->movements.setPrevMoveStatus(MoveStatus::Left);
		slime->movements.setPrevLeftRightStatus(MoveStatus::Right);
	}
}
void SlimeObject::State_Moving::TestForExit([[maybe_unused]] GameObject* object)
{
	SlimeObject* slime = static_cast<SlimeObject*>(object);
	if (slime->velocity.x == 0 && slime->movements.getPrevMoveStatus() != MoveStatus::Jump && slime->movements.getJump())
	{
		slime->movements.setCurrMoveStatus(MoveStatus::Jump);
	}
	if (slime->velocity.x == 0 && slime->movements.getPrevMoveStatus() != MoveStatus::Jump && slime->movements.getJump() == false)
	{
		slime->movements.setCurrMoveStatus(MoveStatus::Idle);
	}
	if (slime->movements.getCurrMoveStatus() == MoveStatus::Jump)
	{
		slime->ChangeState(&slime->stateJumping);
	}
	if (slime->movements.getCurrMoveStatus() == MoveStatus::Idle)
	{
		slime->ChangeState(&slime->stateIdle);
	}
	if (slime->velocity.y != 0)
	{
		slime->movements.setCurrMoveStatus(MoveStatus::Jump);
		slime->ChangeState(&slime->stateIdle);
	}
}
void SlimeObject::State_Jumping::Enter([[maybe_unused]] GameObject* object)
{
	SlimeObject* slime = static_cast<SlimeObject*>(object);
	slime->sprite.PlayAnimation(static_cast<int>(Slime_Anm::None_Anim));
	slime->velocity.y = SlimeObject::jumpVelocity;
	slime->isOnGround = false;
}
void SlimeObject::State_Jumping::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
	SlimeObject* slime = static_cast<SlimeObject*>(object);
	slime->movements.Update(dt);
	if (slime->velocity.y < 0)
	{
		slime->velocity.y = 0;
	}
}
void SlimeObject::State_Jumping::TestForExit([[maybe_unused]] GameObject* object)
{
	SlimeObject* slime = static_cast<SlimeObject*>(object);
	if (slime->velocity.y == 0)
	{
		slime->ChangeState(&slime->stateFalling);
	}
}
void SlimeObject::State_Falling::Enter([[maybe_unused]] GameObject* object)
{
	SlimeObject* slime = static_cast<SlimeObject*>(object);
	slime->isOnGround = false;
}
void SlimeObject::State_Falling::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
	SlimeObject* slime = static_cast<SlimeObject*>(object);
	slime->movements.Update(dt);
}
void SlimeObject::State_Falling::TestForExit([[maybe_unused]] GameObject* object)
{
	SlimeObject* slime = static_cast<SlimeObject*>(object);
	if (slime->velocity.y == 0 && slime->IsOnGround())
	{
		if (slime->movements.getPrevLeftRightStatus() == MoveStatus::Left) {
			slime->movements.setCurrMoveStatus(MoveStatus::Left);
			slime->ChangeState(&slime->stateMoving);
		}
		if (slime->movements.getPrevLeftRightStatus() == MoveStatus::Right) {
			slime->movements.setCurrMoveStatus(MoveStatus::Right);
			slime->ChangeState(&slime->stateMoving);
		}
		slime->movements.setPrevMoveStatus(MoveStatus::Jump);
	}
}