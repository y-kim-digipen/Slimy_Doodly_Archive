/*--------------------------------------------------------------
File Name: WaveGun.cpp
Project: Slimy Doodly
Author: Yoonki Kim, Haneul Lee
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "WaveGun.h"

#include "../Engine/Engine.h"
#include "World.h"				//World::GetObjects().GetPlayer();
#include "Player.h"				//To cast player to gameObject
#include "SlimeObject.h"

const double WaveGun::EnergyRatio = 600;

WaveGun::WaveGun() : reloadTimer(2.)
{
	reloadTimer.Init();
	crosshair.Load("Assets/ScriptSprites/Crosshair.spt");

}

void WaveGun::Update(double dt)
{
    UpdateMousePos();
	UpdateAmmo(dt);
}

void WaveGun::Draw(TransformMatrix displayMatrix) 
{
	DrawAim(displayMatrix);
	DrawAmmoStatus(displayMatrix);
}

bool WaveGun::HasAmmo() const
{
    return ammo > 0;
}

Vector2D WaveGun::GetWaveEnergy() const
{
	auto playerCenterPos = World::GetObjects().GetPlayer()->GetPosition() + Vector2D{0, World::GetObjects().GetPlayer()->GetSize().y / 2};
    const Vector2D directionVec = (mousePosition - playerCenterPos).UnitVec();
    return { directionVec.x * EnergyRatio , directionVec.y * EnergyRatio };
}

void WaveGun::DrawAim(TransformMatrix displayMatrix) 
{
	Player& playerRef = *(World::GetObjects().GetPlayer());
	double playerWidth = playerRef.GetCollisionBox().topRight.x - playerRef.GetCollisionBox().bottomLeft.x;
	Vector2D playerCenterPos = playerRef.GetPosition() + Vector2D{ 0, playerRef.GetSize().y / 2 };

	Vector2D vectorBetween = mousePosition - playerCenterPos;
	double angleBetween = atan2(vectorBetween.y, vectorBetween.x) - doodle::HALF_PI;

	doodle::push_settings();
	doodle::set_outline_color(doodle::HexColor{ 0xFF0000B0 });
	doodle::set_fill_color(doodle::HexColor{ 0x703088A0 });
    doodle::draw_ellipse(Engine::GetMouseInput().GetMousePos()().x, Engine::GetMouseInput().GetMousePos()().y, 15);
	doodle::pop_settings();
    //for Debug

	doodle::push_settings();
	TransformMatrix posMatrix = displayMatrix * TranslateMatrix(playerCenterPos) * RotateMatrix(angleBetween);
	doodle::set_outline_width(3);
	doodle::set_outline_color(doodle::HexColor{ 0xFF0000B0 });
	doodle::set_fill_color(doodle::HexColor{ 0x703088A0 });
	doodle::apply_matrix(posMatrix[0][0], posMatrix[1][0], posMatrix[0][1], posMatrix[1][1], posMatrix[0][2], posMatrix[1][2]);
	doodle::draw_triangle(0, playerWidth / 3 + playerWidth, -playerWidth / 6, playerWidth, playerWidth / 6, playerWidth);
	doodle::pop_settings();
	TransformMatrix mouseMatrix = TranslateMatrix(Vector2D{ Engine::GetMouseInput().GetMousePos()().x, Engine::GetMouseInput().GetMousePos()().y }) * ScaleMatrix( {0.4,0.4});
	crosshair.Draw(mouseMatrix);
}

void WaveGun::UpdateMousePos()
{
	mousePosition = (Engine::GetMouseInput().GetMousePos()() + World::Instance().GetCamera()) / World::Instance().GetCameraZoomRatio();
}

void WaveGun::UpdateAmmo(double dt)
{
	if (ammo < 3)
	{
		reloadTimer.Update(dt);
		if (reloadTimer.IsSettedTime() == true) {
			++ammo;
		}
	}
}

void WaveGun::Shoot()
{
	if (HasAmmo()) {


		const Vector2DInt mousePos = Engine::GetMouseInput().GetMousePos();
		const Vector2D toOriginVector = mousePos() - World::GetObjects().GetPlayer()->GetPosition();

		const Vector2D playerPos = World::GetObjects().GetPlayer()->GetPosition() + Vector2D{ 0, World::GetObjects().GetPlayer()->GetSize().y / 2 };
		const Vector2D wavegunEndPos = playerPos + GetWaveEnergy();

		World::GetParticleEmitter(0).Emit(1, playerPos, Vector2D(), toOriginVector.UnitVec(), 0, atan2(GetWaveEnergy().y, GetWaveEnergy().x));

		--ammo;

		auto gameObjects = World::GetObjects().GetGameObjectStorage();
		for (auto obj : gameObjects)
		{
			if (!dynamic_cast<Player*>(obj))
			{

				bool hasIntersectingLine = false;
				auto lineInterSect = [&playerPos, &wavegunEndPos, &hasIntersectingLine](Vector2D l_start, Vector2D l_end) mutable
				{
					double den = (l_end.y - l_start.y) * (wavegunEndPos.x - playerPos.x) - (l_end.x - l_start.x) * (wavegunEndPos.y - l_start.y);

					if (den == 0)
						return;

					double ua = ((l_end.x - l_start.x) * (playerPos.y - l_start.y) - (l_end.y - l_start.y) * (playerPos.x - l_start.x)) / den;
					double ub = ((wavegunEndPos.x - l_start.x) * (playerPos.y - l_start.y) - (wavegunEndPos.y - l_start.y) * (playerPos.x - l_start.x)) / den;

					hasIntersectingLine |= (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1);
				};

				if (obj != nullptr && dynamic_cast<SlimeObject*>(obj))
				{
					Rect objCollisionBox = obj->GetCollisionBox();
					double width = objCollisionBox.topRight.x - objCollisionBox.bottomLeft.x;
					//double height = objCollisionBox.topRight.y - objCollisionBox.bottomLeft.x;

					std::pair<Vector2D, Vector2D> top = { objCollisionBox.topRight, objCollisionBox.topRight - Vector2D{width, 0} };
					std::pair<Vector2D, Vector2D> bottom = { objCollisionBox.bottomLeft, objCollisionBox.bottomLeft + Vector2D{width, 0} };
					std::pair<Vector2D, Vector2D> left = { top.second, bottom.first };
					std::pair<Vector2D, Vector2D> right = { top.first, bottom.second };

					lineInterSect(top.first, top.second);
					lineInterSect(bottom.first, bottom.second);
					lineInterSect(left.first, left.second);
					lineInterSect(right.first, right.second);

					if (hasIntersectingLine)
					{
						dynamic_cast<SlimeObject*>(obj)->make_state_idle();
						dynamic_cast<SlimeObject*>(obj)->SetVelocity({ 0, 0 });
						dynamic_cast<SlimeObject*>(obj)->AddVelocity(GetWaveEnergy());
					}
				}
			}
		}

	}

}

void WaveGun::DrawAmmoStatus([[maybe_unused]]TransformMatrix displayMatrix) const
{
	Rect playerRect = World::GetObjects().GetPlayer()->GetCollisionBox();
	Vector2D playerSize = World::GetObjects().GetPlayer()->GetSize();

	double MaxLength = playerSize.x; //have to change it to player width
	double height = MaxLength / 8;
	Vector2D drawPos = playerRect.topRight + Vector2D{ -playerSize.x,  playerSize.y / 10 };

	displayMatrix *= TranslateMatrix(drawPos);

	doodle::push_settings();
	doodle::apply_matrix(displayMatrix[0][0], displayMatrix[1][0], displayMatrix[0][1], displayMatrix[1][1], displayMatrix[0][2], displayMatrix[1][2]);
	doodle::set_fill_color(doodle::HexColor{ 0x008888A0 });
	if (ammo >= 0)
	{
	    if(ammo == 0)
	    {
			doodle::draw_rectangle(0, 0, MaxLength * (static_cast<double>(1) / 3)
				* reloadTimer.GetElapsedTile() / reloadTimer.GetTimeInterval(), height);
	    }
		else if(ammo > 0)
		{
			doodle::draw_rectangle(0, 0, MaxLength * (static_cast<double>(1) / 3), height);
		}
	}
	if (ammo >= 1)
	{
		if(ammo == 1)
		{
			doodle::draw_rectangle(MaxLength * (static_cast<double>(1) / 3), 0, MaxLength * (static_cast<double>(1) / 3)
				* reloadTimer.GetElapsedTile() / reloadTimer.GetTimeInterval(), height);
		}
		else if (ammo > 1)
		{
			doodle::draw_rectangle(MaxLength * (static_cast<double>(1) / 3), 0, MaxLength * (static_cast<double>(1) / 3), height);
		}
	}
	if (ammo >= 2)
	{
		if(ammo == 3)
		{
			doodle::draw_rectangle(MaxLength * (static_cast<double>(2) / 3), 0, MaxLength* (static_cast<double>(1) / 3), height);
		}
		else if(ammo == 2)
		{
			doodle::draw_rectangle(MaxLength * (static_cast<double>(2) / 3), 0, MaxLength* (static_cast<double>(1) / 3)
				* reloadTimer.GetElapsedTile() / reloadTimer.GetTimeInterval(), height);
		}
	}
	doodle::pop_settings();
}