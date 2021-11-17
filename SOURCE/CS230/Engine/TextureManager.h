/*--------------------------------------------------------------
File Name: TextureManager.h
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include <string>		//std::string
#include <map>			//std::map

class Texture;

class TextureManager {
public:
	Texture* Load(const std::string& filePath);
	void Unload();

private:
	std::map<std::string, Texture*> pathToTexture;
};