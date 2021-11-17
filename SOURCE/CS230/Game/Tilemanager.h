/*--------------------------------------------------------------
File Name: Tilemanager.h
Project: Slimy Doodly
Author: Hoseob Jeong
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include <doodle/environment.hpp>
#include <iostream>
#include "NormalTile.h"
#include "Tile.h"
#include "TriggerTile.h"
#include "EndingTile.h"

class Tilemanager
{
public:
    void Load(std::string fileIntoMap);
    void Draw(TransformMatrix cameraMatrix);
    void Update(double dt);
    void Unload();
    [[nodiscard]] Tile* GetTile(Vector2D position) const;

    std::pair<int, int> GetTileToPair(Vector2D position) const;

    Tile* GetTile(int row, int col) const;

    bool IsCollisingTile(Tile* tile);

    enum class TileTypes
    {
        None = 0,
        NormalTIle,
        TriggerTile,
        LavaTile,
        WaterTile,
        EndingTile,
        OutofRange,
    };
    constexpr static int Maxrow = 500;
    constexpr static int Maxcolumn = 500;

    const double  TileWidth = 60;
    const double  TileHeight = 47.5;

    int GetColumn() const { return column; };
    int GetRow() const { return row; };

    Tilemanager::TileTypes GetTileType(Vector2D bottomPosition);

    void ChangeTile(int y, int x);
    void DeleteTile(int y, int x);
    void SetNewTile(int y, int x);
    void SetColumn(int col) { column = col; }
    void SetRow(int rows) { row = rows; }
    bool isCollidingTile(Tile* tile) const {
        return dynamic_cast<NormalTile*>(tile) || dynamic_cast<TriggerTile*>(tile);
    }

    std::vector<Tile*> GetCollidingTiles(Rect object);
    std::vector<Tile*> GetAllTiles();

private:
    int row;
    int column;
    Tile* tiles[Maxrow][Maxcolumn]{ {nullptr} };
    std::vector<std::pair<int, int>> triggertileobject;

};



