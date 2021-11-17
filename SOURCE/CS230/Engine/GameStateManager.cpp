/*--------------------------------------------------------------
File Name: GameStateManager.cpp
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "Engine.h"				//Engine::GetLogger()
#include "GameStateManager.h"


GameStateManager::GameStateManager() : currGameState(nullptr), nextGameState(nullptr), state(State::START) { }

void GameStateManager::AddGameState(GameState& gameState) {
	gameStates.push_back(&gameState);
}

void GameStateManager::Update(double dt) {
	switch(state)
	{
		case State::START:
		{
			nextGameState = gameStates[0];
			state = State::UNLOAD;
			break;
		}
		
		case State::LOAD:
		{
			currGameState->Load();
			nextGameState = currGameState;
			Engine::GetLogger().LogEvent("Load Complete");
			state = State::RUNNING;
			break;
		}
		
		case State::RUNNING:
		{
			if (currGameState == nextGameState)
			{
				currGameState->Update(dt);
				currGameState->Draw();
			}
			else 
			{
				currGameState->Unload();
				state = State::UNLOAD;
			}
			break;
		}
		
		case State::UNLOAD:
		{
			currGameState = nextGameState;
			state = State::LOAD;
			break;
		}
		
		case State::SHUTDOWN:
		{
			state = State::EXIT;
			nextGameState = nullptr;
			break;
		}
		
		default:
		{
			state = State::EXIT;
			break;
		}
	}
}

void GameStateManager::SetNextState(int initState) {
	nextGameState = gameStates[initState];
}

void GameStateManager::ReloadState() {
	currGameState->Unload();
	state = State::UNLOAD;
	nextGameState = currGameState;
}

GameState* GameStateManager::GetCurrState()
{
	return currGameState;
}

void GameStateManager::Shutdown() {
	currGameState->Unload();
	state = State::SHUTDOWN;
}
