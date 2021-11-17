/*--------------------------------------------------------------
File Name: TriggerTileManager.cpp
Project: Slimy Doodly
Author: Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "TriggerTileManager.h"
#include <string>
#include <fstream>
#include "../Engine/Engine.h"
void TriggerScriptManager::Load()
{
	std::string data;

	data = "assets/"  + Engine::GetGameStateManager().GetCurrState()->GetName() +  "/Trigger_" + std::to_string(row) + "_" + std::to_string(col) + ".Ho";

	std::ifstream inFileTrigger(data);
	if (inFileTrigger.is_open() == false) {
		throw std::runtime_error("Failed to load " + data);
	}


	std::string label;
	while (inFileTrigger.eof() == false) {
		inFileTrigger >> label;
		if (label == "Door") 
		{
			std::pair<int, int> position;
			inFileTrigger >> position.first;
			inFileTrigger >> position.second;
			Storage.push_back(position);
		}
		else if (label == "Bridge") 
		{
			std::pair<int, int> position;
			inFileTrigger >> position.first;
			inFileTrigger >> position.second;
			Storage.push_back(position);
		}
		else if (label == "WaterSlime") 
		{
			slimename.emplace_back(label);
			std::pair<int, int> position;
			inFileTrigger >> position.first;
			inFileTrigger >> position.second;
			Storage.push_back(position);
		}
		else if (label == "NormalSlime")
		{
			slimename.emplace_back(label);
			std::pair<int, int> position;
			inFileTrigger >> position.first;
			inFileTrigger >> position.second;
			Storage.push_back(position);
		}
		else if (label == "LavaSlime")
		{
			slimename.emplace_back(label);
			std::pair<int, int> position;
			inFileTrigger >> position.first;
			inFileTrigger >> position.second;
			Storage.push_back(position);
		}
		else if (label == "MimicSlime")
		{
			slimename.emplace_back(label);
			std::pair<int, int> position;
			inFileTrigger >> position.first;
			inFileTrigger >> position.second;
			Storage.push_back(position);
		}
		else {
			Engine::GetLogger().LogError("Unknown data " + label + " in .Ho file " + data);
		}
	}

}

std::vector<std::pair<int, int>> TriggerScriptManager::GetStorage() const
{
	return Storage;
}
