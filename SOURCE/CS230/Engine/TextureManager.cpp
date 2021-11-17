/*--------------------------------------------------------------
File Name: TextureManager.cpp
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "Engine.h"					//Engine::GetLogger()
#include "Texture.h"				//Texture
#include "TextureManager.h"

Texture* TextureManager::Load(const std::string& filePath) {
	if (pathToTexture.find(filePath) == pathToTexture.end()) {
		pathToTexture[filePath] = new Texture(filePath);
	}
	return pathToTexture[filePath];
}

void TextureManager::Unload() {
	Engine::GetLogger().LogEvent("Clear Textures");
	for (std::pair<std::string, Texture*> texturePtr : pathToTexture) {
		delete texturePtr.second;
	}
	pathToTexture.clear();
}