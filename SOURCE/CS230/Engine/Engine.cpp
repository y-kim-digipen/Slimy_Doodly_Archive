/*--------------------------------------------------------------
File Name: Engine.cpp
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "Engine.h"

Engine::Engine() : FPSTimer(std::make_unique<Timer>(FPS_TimeInterval)), window({200, 100}),
#ifdef _DEBUG
							logger(Logger::Severity::Debug, true)
#else 
							logger(Logger::Severity::Event, false)
#endif

{}

Engine::~Engine() {}

void Engine::Init(std::string windowName)
{
	window.Init(windowName);
	FPSTimer->Init();
	lastTick = std::chrono::system_clock::now();
	GetLogger().LogEvent("Engine Init");
}

void Engine::Shutdown()
{
	GetLogger().LogEvent("Engine Shutdown");
	GetGameStateManager().Shutdown();
}

void Engine::Update()
{
	const std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	const double dt = std::chrono::duration<double>(now - lastTick).count();
	
	if (dt >= 1 / Engine::Target_FPS) {
		Engine::GetLogger().LogVerbose("Engine Update");
		lastTick = now;
		++ElapsedFrame;
		
		FPSTimer->Update(dt);

		if (FPSTimer->IsSettedTime() == true)
		{
			DisplayFPS();
		}

		if (HasGameEnded() == false)
		{
			GetGameStateManager().Update(dt);
			GetInput().Update();
			GetMouseInput().Update();
			window.Update();
		}
	}	
}

void Engine::DisplayFPS()
{
	const auto aveFrameRate = 
		static_cast<double>(ElapsedFrame) / FPSTimer->GetTimeInterval();
	GetLogger().LogEvent("FPS: " + std::to_string(aveFrameRate));
	ElapsedFrame = 0;
}

bool Engine::HasGameEnded()
{
	if (GetGameStateManager().HasGameEnded() == true)
	{
		return true;
	}
	return false;
}


