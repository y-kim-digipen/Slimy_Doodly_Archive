/*--------------------------------------------------------------
File Name: Input.h
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include <vector>

class Input {
public:
	enum class KeyboardButton {
		None, Enter, Escape, Space, Left, Up, Right, Down,
		A, B, C, D, E, F, G, H, I, J,
		K, L, M, N, O, P, Q, R, S, T,
		U, V, W, X, Y, Z,
		Count
	};

	class [[nodiscard]] InputKey{
	public:
		InputKey(KeyboardButton button) : button{button} {};
		bool IsKeyDown() const;
		bool IsKeyRelease() const;
	private:
		KeyboardButton button;
	};

	Input();
	bool IsKeyDown(KeyboardButton key) const;
	bool IsKeyUp(KeyboardButton key) const;
	bool IsKeyReleased(KeyboardButton key) const;
	void SetKeyDown(KeyboardButton key, bool value);
	void Update();

private:
	std::vector<bool> keyDown;
	std::vector<bool> wasKeyDown;
};
