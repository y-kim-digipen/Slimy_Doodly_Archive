/*--------------------------------------------------------------
File Name: GameObjectManager.h
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once

#include <vector>
#include "GameObject.h"
class Player;

class GameObjectManager {
public:
	void Load(std::string fileIntoObject);
	void Add(GameObject* obj);
	void Unload();

	void UpdateAll(double dt);
	void DrawAll(TransformMatrix& cameraMatrix);
	Player* GetPlayer() const { return  playerPtr; }

	GameObject* operator[](unsigned int index) { return gameObjects[index]; }
	int GetGameObjectAmount() { return static_cast<int>(gameObjects.size()); }
	std::vector<GameObject*> GetGameObjectStorage() { return gameObjects; }
	void Erase(int i) {
		gameObjects[i]->MakeDead();
		gameObjects.erase(gameObjects.begin() + i);
	}
private:
	std::vector<GameObject*> gameObjects;
	Player* playerPtr = nullptr;
};
