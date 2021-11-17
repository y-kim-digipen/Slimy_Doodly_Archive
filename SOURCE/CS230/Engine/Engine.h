/*--------------------------------------------------------------
File Name: Engine.h
Project: Slimy Doodly
Author: Kevin Wright, Yoonki Kim, Haneul Lee
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "GameStateManager.h"	//GameStateManager
#include "Input.h"				//Input
#include "Mouse.h"
#include "Window.h"				//Window
#include "Logger.h"				//Logger
#include "Timer/Timer.h"		//Timer
#include <chrono>				//std::chrono::system_clock::time_point

#include "TextureManager.h"
#include "SoundManager.h"


class Engine {
public:
	static Engine& Instance() { static Engine instance; return instance; }
	static Logger& GetLogger() { return Instance().logger; };
	static Input& GetInput() { return Instance().input; }
	static Mouse& GetMouseInput() { return Instance().mouseInput; };
	static Window& GetWindow() { return Instance().window; }
	static GameStateManager& GetGameStateManager() { return Instance().gameStateManager; }
	static TextureManager& GetTextureManager() { return Instance().textureManager; }
	static SoundManager& GetSoundManager() { return Instance().soundManager; }

	void Init(std::string windowName);
	void Shutdown();
	void Update();
	void DisplayFPS();
	bool HasGameEnded();
	static constexpr double GetTargetFPS(){ return Target_FPS; }
private:
	Engine();
	~Engine();

	std::unique_ptr<Timer> FPSTimer;
	
	Logger logger;
	GameStateManager gameStateManager;
	Input input;
	Mouse mouseInput;
	Window window;
	TextureManager textureManager;
	SoundManager soundManager;
	
	static constexpr double Target_FPS = 30.0;
	static constexpr double FPS_TimeInterval = 5.0;
	std::chrono::system_clock::time_point lastTick;
	int ElapsedFrame = { 0 };
};
