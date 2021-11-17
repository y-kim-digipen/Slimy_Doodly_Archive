/*--------------------------------------------------------------
File Name: GameState.h
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include <string>		//std::string

class GameState {
public:
	virtual void Load() = 0;
	virtual void Update(double) = 0;
	virtual void Draw() = 0;
	virtual void Unload() = 0;
	virtual std::string GetName() = 0;
private:
};

