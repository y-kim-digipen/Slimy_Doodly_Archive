/*--------------------------------------------------------------
File Name: GameStateManager.h
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include <vector>	//std::vector
#include "../Engine/GameState.h"	//GameState

class GameStateManager {
public:
	GameStateManager();

	void AddGameState(GameState& gameState);
	void Update(double);
	void SetNextState(int initState);
	void Shutdown();
	void ReloadState();
	bool HasGameEnded() { return state == State::EXIT; }
	GameState* GetCurrState();
private:
	enum class State {
		START,
		LOAD,
		RUNNING,
		UNLOAD,
		SHUTDOWN,
		EXIT,
	};

	std::vector<GameState*> gameStates;
	State state;
	GameState* currGameState;
	GameState* nextGameState;
};

