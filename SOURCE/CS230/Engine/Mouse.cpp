/*--------------------------------------------------------------
File Name: Mouse.cpp
Project: Slimy Doodly
Author: Yoonki Kim
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "Mouse.h"
#include "Engine.h"

bool Mouse::InputKey::IsKeyDown() const
{
	return Engine::GetMouseInput().IsKeyDown(button);
}

bool Mouse::InputKey::IsKeyRelease() const
{
	return Engine::GetMouseInput().IsKeyReleased(button);
}

Mouse::Mouse()
{
	keyDown.resize(static_cast<int>(MouseButton::Count));
	wasKeyDown.resize(static_cast<int>(MouseButton::Count));
}

bool Mouse::IsKeyDown(MouseButton key) const
{
	return keyDown[static_cast<int>(key)];
}

bool Mouse::IsKeyUp(MouseButton key) const
{
	return keyDown[static_cast<int>(key)] == false;
}

bool Mouse::IsKeyReleased(MouseButton key) const
{
	return keyDown[static_cast<int>(key)] == false && wasKeyDown[static_cast<int>(key)] == true;
}

void Mouse::SetKeyDown(MouseButton key, bool value)
{
	keyDown[static_cast<int>(key)] = value;
}

void Mouse::SetMousePos(Vector2DInt pos)
{
	position = pos;
}

Vector2DInt Mouse::GetMousePos()
{
	return position;
}

void Mouse::Update()
{
	wasKeyDown = keyDown;
}
