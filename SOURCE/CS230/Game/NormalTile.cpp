/*--------------------------------------------------------------
File Name: NormalTile.cpp
Project: Slimy Doodly
Author: Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "NormalTile.h"

#include <doodle/drawing.hpp>

#include "Screens.h"
#include "../Engine/Engine.h"
#include <iostream>
NormalTile::NormalTile(Rect rect, int row, int column, Normal_style types) : Tile(rect, row, column) , style(types) {}
void NormalTile::Draw(TransformMatrix cameraMatrix)
{

    objectMatrix = TranslateMatrix{ {rect.bottomLeft} };
    sprite.Draw(cameraMatrix * objectMatrix * ScaleMatrix{ {0.3, 0.35986} });
    
}


void NormalTile::Load() {
    if (style == Normal_style::Edge)
    {
        sprite.Load("Assets/ScriptSprites/NormalTileEdge.spt");
    }
    if (style == Normal_style::Inside)
    {
        sprite.Load("Assets/ScriptSprites/NormalTileInside.spt");
    }
    sprite.PlayAnimation(1);
}


void NormalTile::Update(double dt)
{
    sprite.Update(dt);
}

void NormalTile::CollisionInteract(double)
{

}
