/*--------------------------------------------------------------
File Name: GameObject.cpp
Project: Slimy Doodly
Author: Kevin Wright, Yoonki Kim
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "GameObject.h"

#include <set>


#include "../Engine/Engine.h"
#include "Level1.h"
#include "World.h"
static const Color HitBoxColor = 0xFF0000FF;
static const double HitBoxLineWidth = 5.;

#if _DEBUG
static const bool isDebug = true;
#else
static const bool isDebug = false;
#endif


GameObject::GameObject(Vector2D position, Vector2D size) : GameObject(position, size, 0, { 1, 1 }) {}

GameObject::GameObject(Vector2D position, Vector2D size, double rotation, Vector2D scale)
    : velocity{ 0,0 }, position(position), updateMatrix(true), isOnGround(true),
    scale(scale), rotation(rotation), currState(&state_nothing), size(size), isFlipped(false), tileOnGround(nullptr), isDead(false)
{}

void GameObject::Update(double dt) {
    int collisionUpdateRate = 5;
    double collisionDt = dt / collisionUpdateRate;
    double physicsCollisionCurDt = 0;
    if(!isOnGround)
        ApplyGravity(dt);
    if(GetIsDead() == false)
    {
        currState->Update(this, dt);
    }
    while (physicsCollisionCurDt <= dt)
    {
        ResolveMapCollision(physicsCollisionCurDt);
        physicsCollisionCurDt += collisionDt;
    }
    if (velocity.x != 0 || velocity.y != 0) {
        UpdatePosition(velocity * dt);
    }
    updateIsOnGround();
    sprite.Update(dt);
    if (GetIsDead() == false)
    {
        currState->TestForExit(this);
    }
}

void GameObject::Draw(TransformMatrix displayMatrix) {
    if(GetIsDead() == false)
    {
        if constexpr (isDebug == true)
        {
            DrawHitBox(displayMatrix * GetMatrix());
        }

        if (size.x == 0 || size.y == 0)
        {
            sprite.Draw(displayMatrix * GetMatrix());
        }
        else
        {
            ScaleMatrix sprite_HitboxRatio = Vector2D{ GetSize().x / sprite.GetFrameSize().x , GetSize().y / sprite.GetFrameSize().y };
            sprite.Draw(displayMatrix * GetMatrix() * sprite_HitboxRatio);
        }
    }
}

Vector2D GameObject::GetPosition() const { return position; }
Vector2D GameObject::GetScale() const { return scale; }
double GameObject::GetRotation() const { return rotation; }

Vector2D GameObject::GetSize() const
{
    Rect collisionBox = GetCollisionBox();
    return { collisionBox.topRight.x - collisionBox.bottomLeft.x, collisionBox.topRight.y - collisionBox.bottomLeft.y };
}

const TransformMatrix& GameObject::GetMatrix() {
    if (updateMatrix == true) {
        objectMatrix = TranslateMatrix(position) * RotateMatrix(rotation) * ScaleMatrix(scale);
        updateMatrix = false;
    }
    return objectMatrix;
}

void GameObject::SetPosition(Vector2D newPosition)
{
    position = newPosition;
    updateMatrix = true;
}

void GameObject::SetPositionX(double newPosX)
{
    position.x = newPosX;
    updateMatrix = true;
}

void GameObject::SetPositionY(double newPosY)
{
    position.y = newPosY;
    updateMatrix = true;
}

void GameObject::UpdatePosition(Vector2D adjustPosition)
{
    position += adjustPosition;
    updateMatrix = true;
}

void GameObject::SetScale(Vector2D newScale)
{
    scale = newScale;
    updateMatrix = true;
}

void GameObject::SetRotation(double newRotationAmount)
{
    rotation = newRotationAmount;
    updateMatrix = true;
}

void GameObject::UpdateRotation(double newRotationAmount)
{
    rotation += newRotationAmount;
    updateMatrix = true;
}

void GameObject::SetVelocity(Vector2D newVelocity)
{
    velocity = newVelocity;
}

void GameObject::AddVelocity(Vector2D anotherVelocity)
{
    velocity += anotherVelocity;
}

Rect GameObject::GetCollisionBox() const
{
    return Rect(position - Vector2D{size.x /2, 0}, position + Vector2D{ size.x / 2, size.y });
}

void GameObject::ApplyGravity(double dt)
{
    velocity.y -= dt * World::Instance().GetGravityConstant();
}

void GameObject::ResolveMapCollision(double dt)
{
    bool allCollisionResolved;
    do
    {
        const Rect curFrameObjectRect = GetCollisionBox();
        const Rect nextFrameObjectRect = { GetCollisionBox().bottomLeft + velocity * dt, GetCollisionBox().topRight + velocity * dt };
        std::vector<Tile*> collidingNextTiles = World::GetTileManager().GetCollidingTiles(nextFrameObjectRect);

        //allCollisionResolved = collidingNextTiles.empty();
        allCollisionResolved = true;
        for (auto tile : collidingNextTiles)
        {
            //CollideFromTop
            if(curFrameObjectRect.bottomLeft.y > tile->GetUpperY() && nextFrameObjectRect.bottomLeft.y <= tile->GetUpperY())
            {
                SetPositionY(tile->GetUpperY() + 0.1);
                velocity.y = 0;
                isOnGround = true;
            }
            else
            {
                isOnGround = false;
            }
            //CollideFromLeft
            if(curFrameObjectRect.topRight.x < tile->GetLeftX() && nextFrameObjectRect.topRight.x >= tile->GetLeftX())
            {
                SetPositionX(tile->GetLeftX() - 0.1 - size.x / 2);
                velocity.x = 0;
            }
            //CollideFromRight
            if (curFrameObjectRect.bottomLeft.x > tile->GetRightX() && nextFrameObjectRect.bottomLeft.x <= tile->GetRightX())
            {
                SetPositionX(position.x = tile->GetRightX() + 0.1 + size.x / 2);
                velocity.x = 0;
            }
            //CollideFromBottom
            if (curFrameObjectRect.topRight.y < tile->GetLowerY() && nextFrameObjectRect.topRight.y >= tile->GetLowerY())
            {
                SetPositionY(tile->GetLowerY() - 0.1 - size.y);
                velocity.y = 0;
            }
        }
    } while (allCollisionResolved != true);
}

void GameObject::DrawHitBox(TransformMatrix displayMatrix) const
{
    const double hitBoxWidth = size.x;;
    const double hitBoxHeight = size.y;

    doodle::push_settings();
    doodle::no_fill();
    doodle::set_outline_width(HitBoxLineWidth);
    doodle::set_outline_color(doodle::HexColor(HitBoxColor));
    doodle::apply_matrix(displayMatrix[0][0], displayMatrix[1][0], displayMatrix[0][1], displayMatrix[1][1], displayMatrix[0][2], displayMatrix[1][2]);
    doodle::draw_rectangle(- hitBoxWidth / 2, 0, hitBoxWidth, hitBoxHeight);
    doodle::pop_settings();
}

bool GameObject::IsOnGround() const
{
    return isOnGround;
}

void GameObject::updateIsOnGround()
{
    Vector2D checkPos1 = GetCollisionBox().bottomLeft + Vector2D{ 0.1, -0.2 };
    Vector2D checkPos2 = GetCollisionBox().topRight + Vector2D{ -0.1 , -0.2 - size.y };

    bool onground1 = World::GetTileManager().IsCollisingTile(World::GetTileManager().GetTile(checkPos1));
    bool onground2 = World::GetTileManager().IsCollisingTile(World::GetTileManager().GetTile(checkPos2));

    isOnGround = onground1 | onground2;
}

void GameObject::ChangeState(State* newState)
{
    currState = newState;
    currState->Enter(this);
}
