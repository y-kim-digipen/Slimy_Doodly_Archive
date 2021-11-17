/*--------------------------------------------------------------
File Name: Window.cpp
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "doodle/window.hpp"        // doodle stuff
#include "Window.h"

#include "doodle/window.hpp"        // doodle window stuff
#include "doodle/drawing.hpp"	// doodle clear background
#include "Engine.h"			// Engine.GetWindow()
#include "Window.h"

Window::Window(Vector2DInt _screenSize) : screenSize(_screenSize)
{
}

Window::~Window()
{
}

void Window::Init(std::string windowName) {
	doodle::create_window(windowName, 1440, 810);
	doodle::set_frame_of_reference(doodle::FrameOfReference::RightHanded_OriginBottomLeft);
	doodle::set_image_mode(doodle::RectMode::Corner);
}

void Window::Resize(int newWidth, int newHeight) { screenSize.x = newWidth; screenSize.y = newHeight; }

Vector2DInt Window::GetSize() { return screenSize; }

void Window::Clear(doodle::HexColor color) { doodle::clear_background(doodle::HexColor{ color }); }

void Window::Update()
{
	if(!doodle::is_full_screen())
	{
		doodle::toggle_full_screen();
	}
    doodle::update_window();

}

void on_window_resized(int new_width, int new_height) { Engine::GetWindow().Resize(new_width, new_height); }
