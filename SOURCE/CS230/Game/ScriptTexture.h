/*--------------------------------------------------------------
File Name: ScriptTexture.h
Project: Slimy Doodly
Author: Yoonki Kim
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "../Engine/Texture.h"

class ScriptTexture
{
public:
    ScriptTexture(std::string filename, Vector2D position_, double scale_);

    void Draw(TransformMatrix cameraMatrix);


private:
    Vector2D position;
    Texture* texture;
    double   scale;
};

