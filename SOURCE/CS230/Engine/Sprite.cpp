/*--------------------------------------------------------------
File Name: Sprite.cpp
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "Sprite.h"
#include "Engine.h"	        //Engine
#include "Texture.h"

Sprite::Sprite() : currAnim(0), texturePtr(nullptr) {}

void Sprite::Load(std::string spriteInfoFile) {
    animations.clear();
    hotSpots.clear();

    if (spriteInfoFile.substr(spriteInfoFile.find_last_of('.')) != ".spt") {
        throw std::runtime_error("Bad Filetype.  " + spriteInfoFile + " not a sprite info file (.spt)");
    }
    std::ifstream inFile(spriteInfoFile);

    if (inFile.is_open() == false) {
        throw std::runtime_error("Failed to load " + spriteInfoFile);
    }

    std::string text;
    inFile >> text;
    texturePtr = Engine::GetTextureManager().Load(text);
    frameSize = texturePtr->GetSize();

    while (inFile.eof() == false) {
        inFile >> text;
        if (text == "FrameSize") {
            inFile >> frameSize.x;
            inFile >> frameSize.y;
        }
        else if (text == "Frame") {
            int frameLocationX, frameLocationY;
            inFile >> frameLocationX;
            inFile >> frameLocationY;
            frameTexel.push_back({ frameLocationX, frameLocationY });
        }
        else if (text == "HotSpot") {
            int hotSpotX, hotSpotY;
            inFile >> hotSpotX;
            inFile >> hotSpotY;
            hotSpots.push_back({ hotSpotX, hotSpotY });
        }
        else if (text == "Anim") {
            inFile >> text;
            animations.push_back(new Animation(text));
        }
        else {
            Engine::GetLogger().LogError("Unknown spt command " + text);
        }
    }
    if (frameTexel.empty() == true) {
        frameTexel.push_back({ 0,0 });
    }
    if (animations.empty() == true) {
        animations.push_back(new Animation());
        PlayAnimation(0);
    }
}

void Sprite::Update(double dt)
{
    if (currAnim >= static_cast<int>(animations.size()) || currAnim < 0) {
        throw "bad animation index";
    }
    animations[currAnim]->Update(dt);
}

void Sprite::Draw(TransformMatrix displayMatrix)
{
    texturePtr->Draw(displayMatrix * TranslateMatrix(-hotSpots[0]),
        GetFrameTexel(animations[currAnim]->GetDisplayFrame()), GetFrameSize());
}

void Sprite::PlayAnimation(int anim)
{
    if (anim >= static_cast<int>(animations.size()) || anim < 0) {
        throw "bad animation index";
    }
    currAnim = anim;
    animations[currAnim]->Reset();
}

bool Sprite::IsAnimationDone()
{
    return animations[currAnim]->IsAnimationDone();
}

void Sprite::AddHotSpot(Vector2DInt position)
{
    hotSpots.push_back(position);
}

Vector2DInt Sprite::GetHotSpot(int index)
{
    if (index >= static_cast<int>(hotSpots.size()))
        Engine::GetLogger().LogError("Invalid hotspot index");
    return hotSpots[index];
}

Vector2DInt Sprite::GetFrameSize() const
{
    return frameSize;
}

Vector2DInt Sprite::GetFrameTexel(int frameNum) const
{
    return frameTexel[frameNum];
}

Sprite::~Sprite()
{
    for (Animation* anim : animations)
    {
        delete anim;
    }
    animations.clear();

}
