/*--------------------------------------------------------------
File Name: GameObjectManager.cpp
Project: Slimy Doodly
Author: Kevin Wright, Yoonki Kim, Haneul Lee
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "GameObjectManager.h"
#include <fstream>
#include "../Engine/Engine.h"
#include "Player.h"
#include "NormalSlime.h"
#include "MimicSlime.h"
#include "LavaSlime.h"
#include "WaterSlime.h"
#include "SlimeMovements.h"
#include "ObjectSize.h"
static Vector2D playerSize = { PlayerSize_X , PlayerSize_Y };
static Vector2D SlimeSize = { SlimeSize_X, SlimeSize_Y };

void GameObjectManager::Load(std::string fileIntoObject)
{
    if (fileIntoObject.substr(fileIntoObject.find_last_of('.')) != ".lvl") {
        throw std::runtime_error("Bad Filetype.  " + fileIntoObject + " not a level object file (.lvl)");
    }
    std::ifstream inFile(fileIntoObject);

    if (inFile.is_open() == false) {
        throw std::runtime_error("Failed to load " + fileIntoObject);
    }

    std::string text;
    inFile >> text;
    if(text == "Player")
    {
        double playerPositionX, playerPositionY;
        inFile >> playerPositionX;
        inFile >> playerPositionY;
        playerPtr = new Player({ playerPositionX , playerPositionY }, playerSize);
        Add(playerPtr);
    }
    else
    {
        Engine::GetLogger().LogError("failed to load player position, check player position info is first");
        throw;
    }

    while (inFile.eof() == false) {
        inFile >> text;
        if (text == "NormalSlime") {
            double slimePositionX, slimePositionY;
            SlimeMovements movements;
            inFile >> slimePositionX;
            inFile >> slimePositionY;
            inFile >> text;
            if (text.substr(text.find_last_of('.')) != ".sms") {
                throw std::runtime_error("Bad Filetype.  " + fileIntoObject + " not a slime move script object file (.sms)");
            }
            std::ifstream inMoveFile(text);
            if (inMoveFile.is_open() == false) {
                throw std::runtime_error("Failed to load " + text);
            }
            while (inMoveFile.eof() == false)
            {
                inMoveFile >> text;
                if (text == "Left") {
                    double moving_time;
                    movements.setMoveLeft(true);
                    inMoveFile >> moving_time;
                    movements.setMoveLeftTime(moving_time);
                }
                if (text == "Right") {
                    double moving_time;
                    movements.setMoveRight(true);
                    inMoveFile >> moving_time;
                    movements.setMoveRightTime(moving_time);
                }
                if (text == "Jump") {
                    movements.setJump(true);
                }
            }

            Add(new NormalSlime({ slimePositionX, slimePositionY }, SlimeSize, movements));
        }
        else if (text == "LavaSlime") {
            double slimePositionX, slimePositionY;
            SlimeMovements movements;
            inFile >> slimePositionX;
            inFile >> slimePositionY;
            inFile >> text;
            if (text.substr(text.find_last_of('.')) != ".sms") {
                throw std::runtime_error("Bad Filetype.  " + fileIntoObject + " not a slime move script object file (.sms)");
            }
            std::ifstream inMoveFile(text);
            if (inMoveFile.is_open() == false) {
                throw std::runtime_error("Failed to load " + text);
            }
            while (inMoveFile.eof() == false)
            {
                inMoveFile >> text;
                if (text == "Left") {
                    double moving_time;
                    movements.setMoveLeft(true);
                    inMoveFile >> moving_time;
                    movements.setMoveLeftTime(moving_time);
                }
                if (text == "Right") {
                    double moving_time;
                    movements.setMoveRight(true);
                    inMoveFile >> moving_time;
                    movements.setMoveRightTime(moving_time);
                }
                if (text == "Jump") {
                    movements.setJump(true);
                }
            }

            Add(new LavaSlime({ slimePositionX, slimePositionY }, SlimeSize, movements));
        }
        else if (text == "WaterSlime") {
            double slimePositionX, slimePositionY;
            SlimeMovements movements;
            inFile >> slimePositionX;
            inFile >> slimePositionY;
            inFile >> text;
            if (text.substr(text.find_last_of('.')) != ".sms") {
                throw std::runtime_error("Bad Filetype.  " + fileIntoObject + " not a slime move script object file (.sms)");
            }
            std::ifstream inMoveFile(text);
            if (inMoveFile.is_open() == false) {
                throw std::runtime_error("Failed to load " + text);
            }
            while (inMoveFile.eof() == false)
            {
                inMoveFile >> text;
                if (text == "Left") {
                    double moving_time;
                    movements.setMoveLeft(true);
                    inMoveFile >> moving_time;
                    movements.setMoveLeftTime(moving_time);
                }
                if (text == "Right") {
                    double moving_time;
                    movements.setMoveRight(true);
                    inMoveFile >> moving_time;
                    movements.setMoveRightTime(moving_time);
                }
                if (text == "Jump") {
                    movements.setJump(true);
                }
            }
            Add(new WaterSlime({ slimePositionX, slimePositionY }, SlimeSize, movements));
        }
        else if (text == "MimicSlime") {
            double slimePositionX, slimePositionY;
            SlimeMovements movements;
            inFile >> slimePositionX;
            inFile >> slimePositionY;
            inFile >> text;
            if (text.substr(text.find_last_of('.')) != ".sms") {
                throw std::runtime_error("Bad Filetype.  " + fileIntoObject + " not a slime move script object file (.sms)");
            }
            std::ifstream inMoveFile(text);
            if (inMoveFile.is_open() == false) {
                throw std::runtime_error("Failed to load " + text);
            }
            while (inMoveFile.eof() == false)
            {
                inMoveFile >> text;
                if (text == "Left") {
                    double moving_time;
                    movements.setMoveLeft(true);
                    inMoveFile >> moving_time;
                    movements.setMoveLeftTime(moving_time);
                }
                if (text == "Right") {
                    double moving_time;
                    movements.setMoveRight(true);
                    inMoveFile >> moving_time;
                    movements.setMoveRightTime(moving_time);
                }
                if (text == "Jump") {
                    movements.setJump(true);
                }
            }
            Add(new MimicSlime({ slimePositionX, slimePositionY }, { SlimeSize.x,SlimeSize.y + 10 }, movements));
        }
        else {
           Engine::GetLogger().LogError("Unknown lvl command " + text);
        }
    }
}

void GameObjectManager::Add(GameObject* obj)
{
    gameObjects.emplace_back(obj);
}

void GameObjectManager::Unload()
{
    for (auto& obj : gameObjects)
    {
        delete obj;
    }
    gameObjects.clear();
}

void GameObjectManager::UpdateAll(double dt)
{
    for (auto obj : gameObjects)
    {
        obj->Update(dt);
    }
}

void GameObjectManager::DrawAll(TransformMatrix& cameraMatrix)
{
    for (auto obj : gameObjects)
    {
        obj->Draw(cameraMatrix);
    }       
}
