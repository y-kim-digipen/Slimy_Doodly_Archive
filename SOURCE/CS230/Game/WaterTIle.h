/*--------------------------------------------------------------
File Name: WaterTile.h
Project: Slimy Doodly
Author: Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "Tile.h"
#include "../Engine/BasicDataTypes.h"

class WaterTile : public Tile
{
public:
	WaterTile(Rect rect, int row, int column);
	virtual void Draw(TransformMatrix cameraMatrix) override;
	virtual void Update(double dt) override;
	virtual void CollisionInteract(double dt) override;
	virtual void Load() override;


private:

	bool playerhitted = false;
	bool slimehitted = false;
	bool slimeinteract = false;
	bool Isinteract = false;
	Timer timer;
	bool slimedead = false;
};

