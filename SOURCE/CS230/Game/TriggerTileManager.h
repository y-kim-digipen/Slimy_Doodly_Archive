/*--------------------------------------------------------------
File Name: TriggerTileManager.h
Project: Slimy Doodly
Author: Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include<vector>
#include<string>

class TriggerScriptManager
{
public:
	TriggerScriptManager(int row, int col, int types) : row(row), col(col), types(types) {}
	void Load();
	std::vector<std::pair<int, int>> GetStorage() const;
	std::string GetSlimeName(int i) { return slimename[i]; }
private:
	int types;
	int row;
	int col;
	std::vector<std::pair<int, int>> Storage;
	std::vector<std::string> slimename;

};
