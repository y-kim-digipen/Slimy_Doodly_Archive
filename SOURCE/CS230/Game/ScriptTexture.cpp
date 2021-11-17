/*--------------------------------------------------------------
File Name: ScriptTexture.cpp
Project: Slimy Doodly
Author: Yoonki Kim
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "ScriptTexture.h"

#include "../Engine/Engine.h"
#include "World.h"

ScriptTexture::ScriptTexture(std::string fileName, Vector2D position_, double scale_) : position(position_), scale(scale_)
{
    texture = Engine::GetTextureManager().Load("Assets/ScriptTextures/" + fileName + ".png");
}

void ScriptTexture::Draw(TransformMatrix cameraMatrix)
{
    Vector2D cameraPos = World::Instance().GetCamera();
    texture->Draw(cameraMatrix * (TranslateMatrix(position) * ScaleMatrix({ scale, scale }) ));
}
