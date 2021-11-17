/*--------------------------------------------------------------
File Name: Texture.cpp
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "Texture.h"
#include <doodle/drawing.hpp>		// doodle::Image, draw_image

Texture::Texture(const std::filesystem::path& filePath) : image(filePath)
{
    size = { image.GetWidth(), image.GetHeight() };
}

void Texture::Draw(TransformMatrix displayMatrix) const
{
    doodle::push_settings();
    doodle::apply_matrix(displayMatrix[0][0], displayMatrix[1][0], displayMatrix[0][1], displayMatrix[1][1], displayMatrix[0][2], displayMatrix[1][2]);
    doodle::draw_image(image, 0, 0, size.x, size.y);
    doodle::pop_settings();
}

void Texture::Draw(TransformMatrix displayMatrix, Vector2DInt texelPos, Vector2DInt frameSize) const {
    doodle::push_settings();
    doodle::apply_matrix(displayMatrix[0][0], displayMatrix[1][0], displayMatrix[0][1], displayMatrix[1][1], displayMatrix[0][2], displayMatrix[1][2]);
    doodle::draw_image(image, 0, 0, static_cast<double>(frameSize.x), static_cast<double>(frameSize.y), texelPos.x, texelPos.y);
    doodle::pop_settings();
}

Vector2DInt Texture::GetSize() const { return size; }

Color Texture::GetPixel(Vector2DInt pos) const {
    const int index = pos.y * size.x + pos.x;
    return image[index].red << 24 | image[index].green << 16 | image[index].blue << 8 | image[index].alpha;
}