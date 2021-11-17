/*--------------------------------------------------------------
File Name: Texture.h
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once

#include <doodle/image.hpp> //doodle::image
#include "BasicDataTypes.h" //Vector2D, Vector2DInt
#include "TransformMatrix.h"//TransformMatrix

class Texture
{
	friend class TextureManager;
	friend class SpriteFont;

public:
	void Draw(TransformMatrix displayMatrix) const;
	void Draw(TransformMatrix matrix, Vector2DInt texelPos, Vector2DInt frameSize) const;
	Vector2DInt GetSize() const;
	Color GetPixel(Vector2DInt pos) const;

private:
	Texture(const std::filesystem::path& filePath);
	doodle::Image image;
	Vector2DInt size;
};
