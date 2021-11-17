/*--------------------------------------------------------------
File Name: BackGround.h
Project: Slimy Doodly
Author: Yoonki Kim
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include <string>						//std::string
#include <vector>						//std::vector
#include "../Engine/BasicDataTypes.h"	//Vector2D, Rect

class Texture;

class BackGround
{
public:
	BackGround();
	void Add(const std::string& texturePath, int level);
	void Unload();
	void Draw(Vector2D camera);
	Rect GetCameraAngle() const;

private:
	struct ParallaxInfo
	{
		Texture* texturePtr;
		int level;
	};
	Rect cameraRange;
	std::vector<ParallaxInfo> backgrounds;
};