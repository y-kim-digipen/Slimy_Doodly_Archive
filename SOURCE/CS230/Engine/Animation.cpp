/*--------------------------------------------------------------
File Name: Animation.cpp
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "Animation.h"  

#include <fstream>    // file input stuff & runtime_error
#include "Engine.h"    // Engine::GetLogger

Animation::Animation() : Animation("assets/none.anm") { }

Animation::Animation(std::string fileName) : isAnimationDone(false), animCommandIndex(0), currPlayFrameData(nullptr) {
    std::ifstream inFile(fileName);
    std::string label;

    if (fileName.substr(fileName.find_last_of('.')) != ".anm") {
        throw std::runtime_error("Bad Filetype.  " + fileName + " not a sprite info file (.anm)");
    }
    if (inFile.is_open() == false) {
        throw std::runtime_error("Failed to load " + fileName);
    }

    while (inFile.eof() == false) {
        inFile >> label;
        if (label == "PlayFrame") {
            int frame;
            float targetTime;
            inFile >> frame;
            inFile >> targetTime;

            animation.push_back(new PlayFrame(frame, targetTime));
        }
        else if (label == "Loop") {
            int loopToIndex;
            inFile >> loopToIndex;
            animation.push_back(new Loop(loopToIndex));
        }
        else if (label == "End") {
            animation.push_back(new End());
        }
        else {
            Engine::GetLogger().LogError("Unknown command " + label + " in anm file " + fileName);
        }
    }
    Reset();
}

void Animation::Update(double dt) {
    currPlayFrameData->Update(dt);
    if (currPlayFrameData->IsFrameDone() == true) {
        currPlayFrameData->Reset();
        ++animCommandIndex;
        if (animation[animCommandIndex]->GetType() == Command::PlayFrame) {
            currPlayFrameData = static_cast<PlayFrame*>(animation[animCommandIndex]);
        }
        else if (animation[animCommandIndex]->GetType() == Command::Loop) {
            Loop* loopData = static_cast<Loop*>(animation[animCommandIndex]);
            animCommandIndex = loopData->GetLoopToIndex();
            if (animation[animCommandIndex]->GetType() == Command::PlayFrame) {
                currPlayFrameData = static_cast<PlayFrame*>(animation[animCommandIndex]);
            }
            else {
                Engine::GetLogger().LogError("Loop does not go to PlayFrame");
                Reset();
            }
        }
        else if (animation[animCommandIndex]->GetType() == Command::End) {
            isAnimationDone = true;
            return;
        }
    }
}

int Animation::GetDisplayFrame()
{
    return currPlayFrameData->GetFrameNum();
}

void Animation::Reset()
{
    isAnimationDone = false;
    animCommandIndex = 0;
    currPlayFrameData = static_cast<PlayFrame*>(animation[animCommandIndex]);
    //currPlayFrameData->Reset();
}

bool Animation::IsAnimationDone()
{
    return isAnimationDone;
}

Animation::~Animation()
{
  for (CommandData* command : animation)
  {
    delete command;
  }
  animation.clear();

}


Animation::PlayFrame::PlayFrame(int frame, double duration) : frame(frame), targetTime(duration), timer(.0)
{}

void Animation::PlayFrame::Update(double dt)
{
    timer += dt;
}

bool Animation::PlayFrame::IsFrameDone()
{
    return timer >= targetTime;
}

void Animation::PlayFrame::Reset()
{
    timer = 0;
}

int Animation::PlayFrame::GetFrameNum()
{
    return frame;
}

Animation::Loop::Loop(int loopToIndex) : loopToIndex(loopToIndex)
{}

int Animation::Loop::GetLoopToIndex()
{
    return loopToIndex;
}
