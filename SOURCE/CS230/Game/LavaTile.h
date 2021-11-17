/*--------------------------------------------------------------
File Name: LavaTile.h
Project: Slimy Doodly
Author: Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "Tile.h"
#include "../Engine/BasicDataTypes.h"
#include "../Engine/Timer/Timer.h"
class LavaTile : public Tile
{
public:
	LavaTile(Rect rect, int row, int column);
	virtual void Draw(TransformMatrix cameraMatrix) override;
	virtual void Update(double dt) override;
	virtual void CollisionInteract(double dt) override;
	virtual void Load() override;

private:
	Timer timer;
	bool playerhitted = false;
	bool slimehitted = false;
	bool slimeinteract = false;
	bool Isinteract = false;
	bool slimedead = false;
};

