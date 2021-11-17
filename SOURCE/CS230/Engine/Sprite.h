/*--------------------------------------------------------------
File Name: Sprite.h
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include <string>			    //std::string
#include "Animation.h"          //Animation
#include "BasicDataTypes.h"     //Vector2D, Vector2DInt
#include "TransformMatrix.h"    //TransformMatrix

class Texture;
class GameObject;

class Sprite {
public:
    Sprite();
    void Load(std::string spriteInfoFile);
    void Update(double dt);
    void Draw(TransformMatrix displayMatrix);
    void PlayAnimation(int anim);
    bool IsAnimationDone();
    void AddHotSpot(Vector2DInt position);
    Vector2DInt GetHotSpot(int index);
    Vector2DInt GetFrameSize() const;
    Vector2DInt GetFrameTexel(int frameNum) const;
    ~Sprite();
private:
    Texture* texturePtr;
    int currAnim;
    Vector2DInt frameSize;
    std::vector<Vector2DInt> frameTexel;
    std::vector<Animation*> animations;
    std::vector<Vector2DInt> hotSpots;
};

