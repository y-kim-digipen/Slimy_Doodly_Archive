/*--------------------------------------------------------------
File Name: TriggerTile.h
Project: Slimy Doodly
Author: Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "Tile.h"
#include "../Engine/BasicDataTypes.h"
#include "TriggerTileManager.h"
#include "SlimeObject.h"

class TriggerTile : public Tile
{
public:
	enum Trigger_style
	{
		Construct,
		Door,
		SlimeRepawn
	};

public:
	TriggerTile(Rect rect, int row, int column, Trigger_style type);
	virtual void Draw(TransformMatrix cameraMatrix) override;
	virtual void Update(double dt) override;
	virtual void CollisionInteract(double dt) override;
	virtual void Load() override;
	void checkcolrow();
	void Collisioncheck();


private:
	TriggerScriptManager triggerscript;
	Trigger_style style = Trigger_style::Construct;
	SlimeObject* trackofslime = nullptr ;
	bool objecthitted = false;
	bool objectIsinteract = false;

};

