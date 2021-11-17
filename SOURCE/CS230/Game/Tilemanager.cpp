/*--------------------------------------------------------------
File Name: Tilemanager.cpp
Project: Slimy Doodly
Author: Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "Tilemanager.h"

#include "NormalTile.h"
#include "TriggerTile.h"
#include "WaterTIle.h"
#include "LavaTile.h"
#include "EndingTile.h"
#include "World.h"
#include <fstream>
#include "../Engine/Engine.h"
void Tilemanager::Load(std::string fileIntoMap)
{
	//read row and column from file
	//calculate gameSize by using column and row
	//todo gamesize change
	//World::SetGameSize({ , }); read from file and set this
	//read files and make array
	//lastly do same thing what did at init


	if (fileIntoMap.substr(fileIntoMap.find_last_of('.')) != ".Map") {
		throw std::runtime_error("Bad Filetype.  " + fileIntoMap + " not a Map info file (.map)");
	}
	std::ifstream inFile(fileIntoMap);

	if (inFile.is_open() == false) {
		throw std::runtime_error("Failed to load " + fileIntoMap);
	}
	std::string str;
	inFile >> str;
	if (!inFile || str != "Row")
	{
		throw std::runtime_error("Fail to read an Row ");
	}
	inFile >> row;
	inFile >> str;
	if (!inFile || str != "column")
	{
		throw std::runtime_error("Fail to read an Column");
	}
	inFile >> column;
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < column; c++)
		{
			char Tilearray;
			inFile >> Tilearray;
			switch (Tilearray)
			{
			case '0':
				tiles[r][c] = nullptr;
				break;
			case '*':
				tiles[r][c] = new NormalTile({ { static_cast<double>(c) * TileWidth , static_cast<double>(row - static_cast<double>(r + 1.0)) * TileHeight },
				  { static_cast<double>(c) * TileWidth + TileWidth , static_cast<double>(row - static_cast<double>(r + 1.0)) * TileHeight + TileHeight } }, r, c, NormalTile::Normal_style::Edge);
				break;
			case 'T':
				tiles[r][c] = new TriggerTile({ { static_cast<double>(c) * TileWidth , static_cast<double>(row - static_cast<double>(r + 1.0)) * TileHeight  },
				  { static_cast<double>(c) * TileWidth + TileWidth , static_cast<double>(row - static_cast<double>(r + 1.0)) * TileHeight + TileHeight } }, r, c, TriggerTile::Trigger_style::Construct);
				break;
			case 't':
				tiles[r][c] = new TriggerTile({ { static_cast<double>(c) * TileWidth , static_cast<double>(row - static_cast<double>(r + 1.0)) * TileHeight  },
				  { static_cast<double>(c) * TileWidth + TileWidth , static_cast<double>(row - static_cast<double>(r + 1.0)) * TileHeight + TileHeight } }, r, c, TriggerTile::Trigger_style::Door);
				break;
			case 'S':
				tiles[r][c] = new TriggerTile({ { static_cast<double>(c) * TileWidth , static_cast<double>(row - static_cast<double>(r + 1.0)) * TileHeight  },
				  { static_cast<double>(c) * TileWidth + TileWidth , static_cast<double>(row - static_cast<double>(r + 1.0)) * TileHeight + TileHeight } }, r, c, TriggerTile::Trigger_style::SlimeRepawn);
				break;
			case 'W':
				tiles[r][c] = new LavaTile({ { static_cast<double>(c) * TileWidth , static_cast<double>(row - static_cast<double>(r + 1.0)) * TileHeight  },
				  { static_cast<double>(c) * TileWidth + TileWidth , static_cast<double>(row - static_cast<double>(r + 1.0)) * TileHeight + TileHeight } }, r, c);
				break;
			case '~':
				tiles[r][c] = new WaterTile({ { static_cast<double>(c) * TileWidth , static_cast<double>(row - static_cast<double>(r + 1.0)) * TileHeight  },
				  { static_cast<double>(c) * TileWidth + TileWidth , static_cast<double>(row - static_cast<double>(r + 1.0)) * TileHeight + TileHeight } }, r, c);
				break;
			case 'E':
				tiles[r][c] = new EndingTile({ { static_cast<double>(c) * TileWidth , static_cast<double>(row - static_cast<double>(r + 1.0)) * TileHeight  },
				  { static_cast<double>(c) * TileWidth + TileWidth , static_cast<double>(row - static_cast<double>(r + 1.0)) * TileHeight + TileHeight } }, r, c);
				break;
			case '=':
				tiles[r][c] = new NormalTile({ { static_cast<double>(c) * TileWidth , static_cast<double>(row - static_cast<double>(r + 1.0)) * TileHeight },
			  { static_cast<double>(c) * TileWidth + TileWidth , static_cast<double>(row - static_cast<double>(r + 1.0)) * TileHeight + TileHeight } }, r, c, NormalTile::Normal_style::Inside);
			}
		}
	}
	char protect_char;
	inFile >> protect_char;
	if (!inFile.eof()) 
	{
		throw std::runtime_error("Fail to load : too many data than col and row" );
	}

	

	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < column; c++)
		{
			if (tiles[r][c] != nullptr)
				tiles[r][c]->Load();
		}
	}



}


void Tilemanager::Draw(TransformMatrix cameraMatrix)
{
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < column; c++)
		{
			if (tiles[r][c] != nullptr)
				tiles[r][c]->Draw(cameraMatrix);
		}
	}
}
void Tilemanager::Update(double dt)
{
	std::list<Tile*> destroyList;
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < column; c++)
		{
			if (tiles[r][c] != nullptr) 
			{
				tiles[r][c]->Update(dt);
				if (tiles[r][c]->ShouldDestroy() == true)
				{
					destroyList.push_back(tiles[r][c]);
				}
			}
		}
	}
	for (Tile* obj : destroyList)
	{
		delete obj;
	}
}

void Tilemanager::Unload()
{
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < column; c++)
		{
			if (tiles[r][c] != nullptr)
			{
				delete tiles[r][c];
				tiles[r][c] = nullptr;
			}
		}
	}

}

Tile* Tilemanager::GetTile(Vector2D position) const
{
    if (static_cast<int>((TileHeight * row - position.y) / TileHeight) > 0 && static_cast<int>(position.x) > 0)
    {
        if (static_cast<int>((TileHeight * row - position.y) / TileHeight) < row 
			&& static_cast<int>(position.x / TileWidth) < column)
        {
            return tiles[static_cast<int>((TileHeight * row - position.y) / TileHeight)][static_cast<int>(position.x / TileWidth)];
        }
    }
    return nullptr;
}

std::pair<int, int> Tilemanager::GetTileToPair(Vector2D position) const
{

   return {
       static_cast<int>((TileHeight * row - position.y) / TileHeight), static_cast<int>(position.x / TileWidth)
   };

}

Tile* Tilemanager::GetTile(int whatRow, int whatCol) const
{
    if(tiles[whatRow][whatCol] != nullptr)
    {
		return tiles[whatRow][whatCol];
    }
	return nullptr;
}

Tilemanager::TileTypes Tilemanager::GetTileType(Vector2D bottomPosition)
{
	if (static_cast<int>((TileHeight * row - bottomPosition.y) / TileHeight) > 0 && static_cast<int>(bottomPosition.x) > 0)
	{
		if (static_cast<int>((TileHeight * row - bottomPosition.y) / TileHeight) < row && static_cast<int>(bottomPosition.x / TileWidth) < column )
		{
			Tile* tilenum = tiles[static_cast<int>((TileHeight * row - bottomPosition.y) / TileHeight)][static_cast<int>(bottomPosition.x / TileWidth)];

			if (dynamic_cast<NormalTile*>(tilenum))
			{
				return TileTypes::NormalTIle;
			}
			if (dynamic_cast<TriggerTile*>(tilenum))
			{
				return TileTypes::TriggerTile;
			}
			if (dynamic_cast<LavaTile*>(tilenum))
			{
				return TileTypes::LavaTile;
			}
			if (dynamic_cast<WaterTile*>(tilenum))
			{
				return TileTypes::WaterTile;
			}
			if (dynamic_cast<EndingTile*>(tilenum))
			{
				return TileTypes::EndingTile;
			}
			if (tilenum == nullptr)
			{
				return TileTypes::None;
			}
		}
	}
	return TileTypes::OutofRange;
}


void Tilemanager::ChangeTile(int y, int x)
{

	//delete tiles[y][x];
	tiles[y][x] = new NormalTile({ { static_cast<double>(x) * TileWidth , static_cast<double>(row - static_cast<double>(y + 1.0)) * TileHeight },
			  { static_cast<double>(x) * TileWidth + TileWidth , static_cast<double>(row - static_cast<double>(y + 1.0)) * TileHeight + TileHeight } }, y, x,NormalTile::Normal_style::Edge);
	tiles[y][x]->Load();

}

void Tilemanager::DeleteTile(int y, int x)
{

	if (dynamic_cast<NormalTile*>(tiles[y][x]))
	{
		delete tiles[y][x];
		tiles[y][x] = nullptr;
	}
}

void Tilemanager::SetNewTile(int y, int x)
{

	if (tiles[y][x] == nullptr)
	{
		tiles[y][x] = new NormalTile({ { static_cast<double>(x) * TileWidth , static_cast<double>(row - static_cast<double>(y + 1.0)) * TileHeight },
				  { static_cast<double>(x) * TileWidth + TileWidth , static_cast<double>(row - static_cast<double>(y + 1.0)) * TileHeight + TileHeight   } }, y, x,NormalTile::Normal_style::Inside);
		tiles[y][x]->Load();
	}
}

std::vector<Tile*> Tilemanager::GetCollidingTiles(Rect object)
{
    std::vector<Tile*> returnVec;

    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < column; c++)
        {
			if (tiles[r][c] != nullptr && IsCollisingTile(tiles[r][c]))
			{
				Rect tileRec = tiles[r][c]->GetRect();
				if (IsCollision(tileRec, object))
					returnVec.emplace_back(tiles[r][c]);
			}

        }
    }
    return returnVec;
}

std::vector<Tile*> Tilemanager::GetAllTiles()
{
    std::vector<Tile*> alltiles;
    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < column; c++)
        {
            if (tiles[r][c] != nullptr)
                if (IsCollisingTile(tiles[r][c]))
                {
                    alltiles.emplace_back(tiles[r][c]);
                }
        }
    }
    return alltiles;
}


bool Tilemanager::IsCollisingTile(Tile* tile)
{
	if (dynamic_cast<NormalTile*>(tile))
	{
		return true;
	}
	else if (dynamic_cast<TriggerTile*>(tile))
	{
		return true;
	}
	else if (dynamic_cast<EndingTile*>(tile))
	{
		return true;
	}
	else
	{
		return false;
	}
}

