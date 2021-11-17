/*--------------------------------------------------------------
File Name: Window.h
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "BasicDataTypes.h" //Vector2DInt
#include "doodle/color.hpp" //doodle::Color

class Window {
public:
    Window(Vector2DInt _screenSize);
    ~Window();
    void Init(std::string windowName);
    void Resize(int newWidth, int newHeight);
    Vector2DInt GetSize();
    void Clear(doodle::HexColor color);
    void Update();
	
private:
    Vector2DInt screenSize;
};
