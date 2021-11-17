/*--------------------------------------------------------------
File Name: Input_Doodle.cpp
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "Input.h"		
#include "doodle/input.hpp"	//doodle::KeyBoardButtons, and functions
#include "Engine.h"			//Engine::GetLogger, GetInput

Input::KeyboardButton DoodleKeyToCS230Key(doodle::KeyboardButtons button) {
	if (button == doodle::KeyboardButtons::Enter) {
		return Input::KeyboardButton::Enter;
	}
	else if (button == doodle::KeyboardButtons::Escape) {
		return Input::KeyboardButton::Escape;
	}
	else if (button == doodle::KeyboardButtons::Space) {
		return Input::KeyboardButton::Space;
	}
	else if (button == doodle::KeyboardButtons::Left) {
		return Input::KeyboardButton::Left;
	}
	else if (button == doodle::KeyboardButtons::Right) {
		return Input::KeyboardButton::Right;
	}
	else if (button == doodle::KeyboardButtons::Up) {
		return Input::KeyboardButton::Up;
	}
	else if (button == doodle::KeyboardButtons::Down) {
		return Input::KeyboardButton::Down;
	}
	else if (button >= doodle::KeyboardButtons::A && button <= doodle::KeyboardButtons::Z) {
		int offset = static_cast<int>(button) - static_cast<int>(doodle::KeyboardButtons::A);
		return static_cast<Input::KeyboardButton>(static_cast<int>(Input::KeyboardButton::A) + offset);
	}
	return Input::KeyboardButton::None;
}

Mouse::MouseButton DoodleMouseKeyToCS230Key(doodle::MouseButtons button)
{
	if (button == doodle::MouseButtons::Left) {
		return Mouse::MouseButton::Left;
	}
	else if (button == doodle::MouseButtons::Middle)
	{
		return Mouse::MouseButton::Wheel;
	}
	else if (button == doodle::MouseButtons::Right)
	{
		return Mouse::MouseButton::Right;
	}
	return Mouse::MouseButton::None;
}

void on_key_pressed(doodle::KeyboardButtons doodleButton) {
	Input::KeyboardButton button = DoodleKeyToCS230Key(doodleButton);
	if (button != Input::KeyboardButton::None) {
		Engine::GetLogger().LogEvent("on_key_pressed");
		Engine::GetInput().SetKeyDown(button, true);
	}
}

void on_key_released(doodle::KeyboardButtons doodleButton) {
	Input::KeyboardButton button = DoodleKeyToCS230Key(doodleButton);
	if (button != Input::KeyboardButton::None) {
		Engine::GetLogger().LogEvent("on_key_released");
		Engine::GetInput().SetKeyDown(button, false);
	}
}

void on_mouse_pressed(doodle::MouseButtons doodleButton)
{
	Mouse::MouseButton button = DoodleMouseKeyToCS230Key(doodleButton);
	if (button != Mouse::MouseButton::None)
	{
		//Engine::GetLogger().LogEvent("on_mouse_key_pressed");
		Engine::GetMouseInput().SetKeyDown(button, true);
	}
}

void on_mouse_released(doodle::MouseButtons doodleButton)
{
	Mouse::MouseButton button = DoodleMouseKeyToCS230Key(doodleButton);
	if (button != Mouse::MouseButton::None)
	{
		//Engine::GetLogger().LogEvent("on_mouse_key_released");
		Engine::GetMouseInput().SetKeyDown(button, false);
	}
}

void on_mouse_moved(int mouse_x, int mouse_y)
{
	Engine::GetMouseInput().SetMousePos({ mouse_x, mouse_y });
}