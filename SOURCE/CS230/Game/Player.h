/*--------------------------------------------------------------
File Name: Player.h
Project: Slimy Doodly
Author: Yoonki Kim
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "../Engine/Input.h"
#include "WaveGun.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
    Player(Vector2D startPos, Vector2D size);

    void Update(double dt) override;
    void Draw(TransformMatrix displayMatrix) override;
    Vector2D GetWaveGunEnergy() const;

private:
    //Physics


    Input::InputKey moveLeftKey;
    Input::InputKey moveRightKey;
    Input::InputKey jumpKey;
    Mouse::InputKey shootKey;

    WaveGun waveGun;
    static const double jumpVelocity;
    static const double xAccel;
    static const double xDrag;
    static const double maxXvelocity;
    bool isFlipped = false;

    class State_Idle : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };
    class State_Running : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Running"; }
    };
    class State_Jumping : public State {
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };
    class State_Flying : public State
    {
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Flying"; }
    };
    class State_Falling : public State {
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Falling"; }
    };
    class State_Skidding : public State {
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Skidding"; }
    };

    State_Idle stateIdle;
    State_Running stateRunning;
    State_Jumping stateJumping;
    State_Falling stateFalling;
    State_Skidding stateSkidding;
    State_Flying stateFlying;
};

