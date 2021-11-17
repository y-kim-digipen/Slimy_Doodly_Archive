/*--------------------------------------------------------------
File Name: Mouse.h
Project: Slimy Doodly
Author: Yoonki Kim
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include <vector>		//std::vector
#include "BasicDataTypes.h"		//Vector2DInt

class Mouse
{
public:
	enum class MouseButton {
		None, Right, Wheel, Left, Count
	};

	class [[nodiscard]] InputKey{
	public:
		InputKey(MouseButton button) : button{button} {};
		bool IsKeyDown() const;
		bool IsKeyRelease() const;
	private:
		MouseButton button;
	};

	Mouse();
	bool IsKeyDown(MouseButton key) const;
	bool IsKeyUp(MouseButton key) const;
	bool IsKeyReleased(MouseButton key) const;
	void SetKeyDown(MouseButton key, bool value);
	void SetMousePos(Vector2DInt pos);
	Vector2DInt GetMousePos();
	void Update();

private:
	std::vector<bool> keyDown;
	std::vector<bool> wasKeyDown;
	Vector2DInt position;
};


