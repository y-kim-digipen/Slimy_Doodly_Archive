/*--------------------------------------------------------------
File Name: SlimeObject.h
Project: Slimy Doodly
Author: Haneul Lee
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "GameObject.h"
#include "SlimeMovements.h"

class SlimeObject : public GameObject {
public:
	using GameObject::GameObject;
protected:
	static const double jumpVelocity;
	static const double xAccel;
	static const double xDrag;
	static const double maxXvelocity;
	double timer;

	class State_Idle : public State {
		virtual void Enter(GameObject* object);
		virtual void Update(GameObject* object, double dt);
		virtual void TestForExit(GameObject* object);
		std::string GetName() override { return "Idle"; }
	};
	class State_Moving : public State {
		virtual void Enter(GameObject* object);
		virtual void Update(GameObject* object, double dt);
		virtual void TestForExit(GameObject* object);
		std::string GetName() override { return "Moving"; }
	};
	class State_Jumping : public State {
		virtual void Enter(GameObject* object);
		virtual void Update(GameObject* object, double dt);
		virtual void TestForExit(GameObject* object);
		std::string GetName() override { return "Jumping"; }
	};
	class State_Falling : public State {
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Falling"; }
	};

	State_Idle stateIdle;
	State_Moving stateMoving;
	State_Jumping stateJumping;
	State_Falling stateFalling;

	SlimeMovements movements;
public:
	void make_state_idle() { ChangeState(&stateIdle); }
};