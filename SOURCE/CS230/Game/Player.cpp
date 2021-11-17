/*--------------------------------------------------------------
File Name: Player.cpp
Project: Slimy Doodly
Author: Yoonki Kim
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "Player.h"
#include "../Engine/Engine.h"   //Engine::GetLogger()
#include "../Game/Player_Anims.h"
#include "Level1.h"
#include "World.h"
#include "string"

const double Player::jumpVelocity = 400;
const double Player::xAccel = 480;
const double Player::xDrag = Player::xAccel * 1.3;
const double Player::maxXvelocity = 300;

Player::Player(Vector2D startPos, Vector2D size) : GameObject(startPos, size),
shootKey(Mouse::MouseButton::Left), moveLeftKey(Input::KeyboardButton::A), moveRightKey(Input::KeyboardButton::D), jumpKey(Input::KeyboardButton::W)
{
	if(World::Instance().IsHardMode())
	{
		sprite.Load("Assets/ScriptSprites/Player_Rage.spt");
	}
	else
	{
		sprite.Load("Assets/ScriptSprites/Player.spt");
	}
    velocity = { 0, 0 };
    currState = &stateIdle;
    currState->Enter(this);
}

void Player::Update(double dt)
{
	if (World::GetUI().m_IsLevelClear() == true)
	{
		return;
	}
	if(GetIsDead() == false)
	{
		GameObject::Update(dt);
		waveGun.Update(dt);
		if (isOnGround)
		{
			if (velocity.x < 0)
			{
				isFlipped = true;
			}
			else if (velocity.x > 0)
			{
				isFlipped = false;
			}
		}

		if (isFlipped == true) {
			SetScale({ -1, 1 });
		}
		else {
			SetScale({ 1, 1 });
		}
	}

}

void Player::Draw(TransformMatrix displayMatrix)
{
	if (GetIsDead() == false)
	{
		GameObject::Draw(displayMatrix);
		waveGun.Draw(displayMatrix);
	}
}

Vector2D Player::GetWaveGunEnergy() const
{
	return waveGun.GetWaveEnergy();
}

void Player::State_Idle::Enter([[maybe_unused]] GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->sprite.PlayAnimation(static_cast<int>(PlayerAnim::Idle));
}

void Player::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
}

void Player::State_Idle::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->moveLeftKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateRunning);
	}
	else if (player->moveRightKey.IsKeyDown() == true) {
		player->ChangeState(&player->stateRunning);
	}
	if (player->shootKey.IsKeyRelease() == true && player->waveGun.HasAmmo() == true)
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/wave_gun.wav");
		player->ChangeState(&player->stateFlying);
	}
	if (player->jumpKey.IsKeyDown() == true && player->IsOnGround())
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/jump.wav");
		player->ChangeState(&player->stateJumping);
	}
}

void Player::State_Running::Enter(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->sprite.PlayAnimation(static_cast<int>(PlayerAnim::Run));
	if (player->velocity.x < 0)
	{
		player->isFlipped = true;
	}
	else if (player->velocity.x > 0)
	{
		player->isFlipped = false;
	}
}

void Player::State_Running::Update(GameObject* object, double dt)
{
	Player* player = static_cast<Player*>(object);

	if ((player->moveLeftKey.IsKeyDown() == false) && (player->moveRightKey.IsKeyDown() == false))
	{
		if (player->velocity.x <= Player::xDrag / 2 && player->velocity.x >= -Player::xDrag / 2)
		{
			player->velocity.x = 0;
		}
		else if (player->velocity.x < 0)
		{
			player->velocity.x += Player::xDrag * dt;
		}
		else if (player->velocity.x > 0)
		{
			player->velocity.x -= Player::xDrag * dt;
		}
	}
	else if (player->moveLeftKey.IsKeyDown() == true)
	{
		player->velocity.x -= Player::xAccel * dt;
		if (player->velocity.x < -Player::maxXvelocity) {
			player->velocity.x = -Player::maxXvelocity;
		}
	}
	else if (player->moveRightKey.IsKeyDown() == true)
	{
		player->velocity.x += Player::xAccel * dt;
		if (player->velocity.x > Player::maxXvelocity) {
			player->velocity.x = Player::maxXvelocity;
		}
	}
	if (player->shootKey.IsKeyRelease() == true && player->waveGun.HasAmmo() == true)
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/wave_gun.wav");
		player->ChangeState(&player->stateFlying);
	}
}

void Player::State_Running::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->velocity.x > 0) {
		if (player->moveLeftKey.IsKeyDown() == true) {
			player->ChangeState(&player->stateSkidding);
		}
	}
	else if (player->velocity.x < 0) {
		if (player->moveRightKey.IsKeyDown() == true) {
			player->ChangeState(&player->stateSkidding);
		}
	}
	if (player->velocity.x == 0 && ((player->moveRightKey.IsKeyDown() == true) || (player->moveLeftKey.IsKeyDown() == true))) {
		player->ChangeState(&player->stateIdle);
	}
	if (player->jumpKey.IsKeyDown() == true && player->IsOnGround())
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/jump.wav");
		player->ChangeState(&player->stateJumping);
	}
}

void Player::State_Jumping::Enter(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->sprite.PlayAnimation(static_cast<int>(PlayerAnim::Jump));
	player->velocity.y = Player::jumpVelocity;
	//player->isOnGround = false;
}

void Player::State_Jumping::Update(GameObject* object, double dt)
{
	Player* player = static_cast<Player*>(object);
	if (player->jumpKey.IsKeyRelease() == true && player->velocity.y > 0)
	{
		player->velocity.y = 0;
	}
	if (player->velocity.y < 0)
	{
		player->velocity.y = 0;
	}
	if (player->moveLeftKey.IsKeyDown() == true)
	{
		player->velocity.x -= Player::xAccel * dt;
		if (player->velocity.x < -Player::maxXvelocity) {
			player->velocity.x = -Player::maxXvelocity;
		}
	}
	if (player->moveRightKey.IsKeyDown() == true)
	{
		player->velocity.x += Player::xAccel * dt;
		if (player->velocity.x > Player::maxXvelocity) {
			player->velocity.x = Player::maxXvelocity;
		}
	}
	if (player->shootKey.IsKeyRelease() == true && player->waveGun.HasAmmo() == true)
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/wave_gun.wav");
		player->ChangeState(&player->stateFlying);
	}
}

void Player::State_Jumping::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->velocity.y == 0 && player->IsOnGround())
	{
		if (player->velocity.x == 0)
		{
			player->ChangeState(&player->stateIdle);
		}
		else
		{
			player->ChangeState(&player->stateRunning);
		}
	}
	if (player->velocity.y == 0)
	{
		player->ChangeState(&player->stateFalling);
	}

}

void Player::State_Falling::Enter([[maybe_unused]]GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->sprite.PlayAnimation(static_cast<int>(PlayerAnim::Fall));
}

void Player::State_Falling::Update(GameObject* object, double dt)
{
	Player* player = static_cast<Player*>(object);
	if (player->moveLeftKey.IsKeyDown() == true)
	{
		player->velocity.x -= Player::xAccel * dt;
		if (player->velocity.x < -Player::maxXvelocity) {
			player->velocity.x = -Player::maxXvelocity;
		}
	}
	if (player->moveRightKey.IsKeyDown() == true)
	{
		player->velocity.x += Player::xAccel * dt;
		if (player->velocity.x > Player::maxXvelocity) {
			player->velocity.x = Player::maxXvelocity;
		}
	}
	if (player->shootKey.IsKeyRelease() == true && player->waveGun.HasAmmo() == true)
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/wave_gun.wav");
		player->ChangeState(&player->stateFlying);
	}
}

void Player::State_Falling::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->velocity.y == 0 && player->IsOnGround())
	{
		if (player->velocity.x == 0)
		{
			player->ChangeState(&player->stateIdle);
		}
		else
		{
			player->ChangeState(&player->stateRunning);
		}
	}
}

void Player::State_Skidding::Enter([[maybe_unused]] GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->sprite.PlayAnimation(static_cast<int>(PlayerAnim::Run));
}

void Player::State_Skidding::Update(GameObject* object, double dt)
{
	Player* player = static_cast<Player*>(object);
	if (player->velocity.x > 0)
	{
		player->velocity.x -= (Player::xDrag + Player::xAccel) * dt;
	}
	else if (player->velocity.x < 0)
	{
		player->velocity.x += (Player::xDrag + Player::xAccel) * dt;
	}
	if (player->shootKey.IsKeyRelease() == true && player->waveGun.HasAmmo() == true)
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/wave_gun.wav");
		player->ChangeState(&player->stateFlying);
	}
}

void Player::State_Skidding::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->moveLeftKey.IsKeyDown() == true) {
		if (player->velocity.x <= 0) {
			player->ChangeState(&player->stateRunning);
		}
	}
	else if (player->moveRightKey.IsKeyDown() == true) {
		if (player->velocity.x >= 0) {
			player->ChangeState(&player->stateRunning);
		}
	}
	else {
		player->ChangeState(&player->stateRunning);
	}
	if (player->jumpKey.IsKeyDown() == true && player->IsOnGround()) {
		player->ChangeState(&player->stateJumping);
	}
}

void Player::State_Flying::Enter(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	Vector2D waveEnergy = player->GetWaveGunEnergy();
	player->AddVelocity(-waveEnergy);
	player->waveGun.Shoot();
}

void Player::State_Flying::Update(GameObject* object, double dt)
{
	Player* player = static_cast<Player*>(object);
	if (player->moveLeftKey.IsKeyDown() == true)
	{
		player->velocity.x -= Player::xAccel * dt;
		if (player->velocity.x < -Player::maxXvelocity) {
			player->velocity.x = -Player::maxXvelocity;
		}
	}
	if (player->moveRightKey.IsKeyDown() == true)
	{
		player->velocity.x += Player::xAccel * dt;
		if (player->velocity.x > Player::maxXvelocity) {
			player->velocity.x = Player::maxXvelocity;
		}
	}
	if (player->shootKey.IsKeyRelease() == true && player->waveGun.HasAmmo() == true)
	{
		Engine::GetSoundManager().PlaySFX("Assets/SFX/wave_gun.wav");
		player->ChangeState(&player->stateFlying);
	}
}

void Player::State_Flying::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->velocity.y <= 0)
	{
		player->ChangeState(&player->stateFalling);
	}
	if (player->velocity.y == 0 && player->IsOnGround())
	{
		if (player->velocity.x == 0)
		{
			player->ChangeState(&player->stateIdle);
		}
		else
		{
			player->ChangeState(&player->stateRunning);
		}
	}
}
