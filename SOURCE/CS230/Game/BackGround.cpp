/*--------------------------------------------------------------
File Name: BackGround.cpp
Project: Slimy Doodly
Author: Yoonki Kim
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "BackGround.h"

#include "../Engine/Engine.h" //Engile::GetWindow().GetSize()
#include "../Engine/TransformMatrix.h"
#include "../Engine/Texture.h"

BackGround::BackGround()
{
}

void BackGround::Add(const std::string& texturePath, int level)
{
	backgrounds.push_back({ Engine::GetTextureManager().Load(texturePath), level });
	if (level == 1)
	{
		cameraRange.bottomLeft = { 0, 0 };
		cameraRange.topRight = (backgrounds.back().texturePtr->GetSize() - Engine::GetWindow().GetSize())();
	}
}

void BackGround::Unload()
{}

void BackGround::Draw(Vector2D camera)
{
	for (auto&& levelInfo : backgrounds)
	{
		levelInfo.texturePtr->Draw(TranslateMatrix{ Vector2D{ -camera.x / levelInfo.level, -camera.y } });
	}
}

Rect BackGround::GetCameraAngle() const
{
	return cameraRange;
}
