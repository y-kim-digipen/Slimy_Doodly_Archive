/*--------------------------------------------------------------
File Name: Tile.h
Project: Slimy Doodly
Author: Hoseob Jeong ,Yoonki Kim
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "../Engine/BasicDataTypes.h"
#include "../Game/Player.h"
//#include "../Game/Physics.h"
class Tile
{
public:
    Tile() = delete;
    virtual ~Tile() = default;
    virtual void Draw(TransformMatrix cameraMatrix);
    virtual void Update(double) = 0;
    [[nodiscard]] Rect GetRect() const { return rect; }
    virtual void CollisionInteract(double dt) = 0;
    virtual void Load() = 0;
    void Unload() {
        isdead = true;
    }
    bool Isdead() {
        return isdead;
    }
    void Destroy() { destroyObject = true; }
    bool ShouldDestroy() { return destroyObject; }

    [[nodiscard]] double GetLeftX() const { return rect.bottomLeft.x; }
    [[nodiscard]] double GetRightX() const { return rect.topRight.x; }
    [[nodiscard]] double GetUpperY() const { return rect.topRight.y; }
    [[nodiscard]] double GetLowerY() const { return rect.bottomLeft.y; }
    [[nodiscard]] double GetHeight() const { return rect.topRight.y - rect.bottomLeft.y; }
    [[nodiscard]] double GetWidth() const { return rect.topRight.x - rect.bottomLeft.x; }
    [[nodiscard]] Vector2D GetCenter() const;

    [[nodiscard]] bool IsCollision(Vector2D otherObject) const;


protected:
    Tile(Rect _rect, int row, int column) : rect(_rect), row(row) , col(column) {}
    [[nodiscard]] constexpr int GetColumn() const;
    [[nodiscard]] constexpr int GetRow() const;
    Rect rect;
    Sprite sprite;
    TransformMatrix objectMatrix;
private:
    int col;
    int row;
    bool isdead = false;
    bool destroyObject = false;
};

inline void Tile::Draw(TransformMatrix cameraMatrix)
{
    objectMatrix = TranslateMatrix{{rect.bottomLeft}};
    sprite.Draw(cameraMatrix * objectMatrix * ScaleMatrix{{0.25, 0.25}});
}

inline Vector2D Tile::GetCenter() const
{
    const Vector2D widthHeight{rect.topRight.x - rect.bottomLeft.x, rect.topRight.y - rect.bottomLeft.y};
    return {rect.bottomLeft + widthHeight / 2};
}

inline bool Tile::IsCollision(Vector2D otherObject) const
{
    if (otherObject.x < rect.topRight.x && otherObject.x > rect.bottomLeft.x)
    {
        if (otherObject.y < rect.topRight.y + 10 && otherObject.y >= rect.bottomLeft.y)
        {
            return true;
        }
    }
    return false;
}

constexpr int Tile::GetColumn() const
{
    return col;
}

constexpr int Tile::GetRow() const
{
    return row;
}

