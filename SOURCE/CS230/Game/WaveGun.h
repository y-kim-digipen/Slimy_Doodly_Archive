/*--------------------------------------------------------------
File Name: WaveGun.cpp
Project: Slimy Doodly
Author: Yoonki Kim
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "../Engine/BasicDataTypes.h"
#include "../Engine/Mouse.h"
#include "../Engine/Timer/Timer.h"
#include "../Engine/TransformMatrix.h"
#include "../Engine/Sprite.h"
class Player;

class WaveGun
{
	friend Player;
public:
	WaveGun();
	void Update(double dt);
	void Draw(TransformMatrix displayMatrix);
	Vector2D GetWaveEnergy() const;
	bool HasAmmo() const;

private:
	void UpdateMousePos();
	void UpdateAmmo(double dt);
	void Shoot();
	void DrawAmmoStatus(TransformMatrix displayMatrix) const;
	void DrawAim(TransformMatrix displayMatrix);

private:
	static const double EnergyRatio;
	Vector2D mousePosition;
	Sprite crosshair;
	int ammo = 3;
	Timer reloadTimer;
};

