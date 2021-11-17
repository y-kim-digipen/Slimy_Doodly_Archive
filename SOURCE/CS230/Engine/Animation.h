/*--------------------------------------------------------------
File Name: Animation.h
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include <vector>  //std::vector
#include <string>  //std::string

class Animation {
public:
    Animation();
    Animation(std::string file);
    void Update(double dt);
    int GetDisplayFrame();
    void Reset();
    bool IsAnimationDone();
    ~Animation();
private:
    enum class Command {
        PlayFrame,
        Loop,
        End,
    };
    class CommandData {
    public:
        virtual Command GetType() = 0;
        virtual ~CommandData() = default;
    };
    class PlayFrame : public CommandData {
    public:
        PlayFrame(int frame, double duration);
        Command GetType() override { return Command::PlayFrame; }
        void Update(double dt);
        bool IsFrameDone();
        void Reset();
        int GetFrameNum();
    private:
        int frame;
        double targetTime;
        double timer;
    };
    class Loop : public CommandData {
    public:
        Loop(int loopToIndex);
        Command GetType() override { return Command::Loop; }
        int GetLoopToIndex();
    private:
        int loopToIndex;
    };
    class End : public CommandData {
    public:
        Command GetType() override { return Command::End; }
    private:
    };

    bool isAnimationDone;
    int animCommandIndex;
    PlayFrame* currPlayFrameData;
    std::vector<CommandData*> animation;
};