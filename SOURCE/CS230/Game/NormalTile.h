/*--------------------------------------------------------------
File Name: NormalTile.h
Project: Slimy Doodly
Author: Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "Tile.h"
#include "../Engine/BasicDataTypes.h"

class NormalTile : public Tile
{
public:
    enum Normal_style
    {
       Edge,
       Inside
    };
    NormalTile(Rect rect, int row, int column, Normal_style types );
    virtual void Draw(TransformMatrix cameraMatrix) override;
    virtual void Update(double dt) override;
    virtual void CollisionInteract(double dt) override;
    virtual void Load() override;
    Normal_style style = Normal_style::Inside;

};

