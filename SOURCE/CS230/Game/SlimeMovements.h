/*--------------------------------------------------------------
File Name: SlimeMovements.h
Project: Slimy Doodly
Author: Haneul Lee
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include <string>

enum class MoveStatus {
	Idle = 0,
	Left = 1,
	Right = 2,
	Jump = 3,
};

class SlimeMovements {
public:
	void Update(double dt);
	void setMoveLeft(bool boolean) { MoveLeft = boolean; }
	void setMoveRight(bool boolean) { MoveRight = boolean; }
	void setJump(bool boolean) { Jump_after_moving = boolean; }
	void setMoveLeftTime(double time) { MoveLeftTime = time; }
	void setMoveRightTime(double time) { MoveRightTime = time; }
	void setCurrMoveStatus(MoveStatus newMoveStatus) { currMoveStatus = newMoveStatus; }
	void setPrevMoveStatus(MoveStatus newMoveStatus) { prevMoveStatus = newMoveStatus; }
	void setPrevLeftRightStatus(MoveStatus newMoveStatus) { prevLeftRightStatus = newMoveStatus; }
	bool getMoveLeft() { return MoveLeft; }
	bool getMoveRight() { return MoveRight; }
	bool getJump() { return Jump_after_moving; }
	double getMoveLeftTime() { return MoveLeftTime; }
	double getMoveRightTime() { return MoveRightTime; }
	MoveStatus getCurrMoveStatus() { return currMoveStatus; }
	MoveStatus getPrevMoveStatus() { return prevMoveStatus; }
	MoveStatus getPrevLeftRightStatus() { return prevLeftRightStatus; }

private:
	MoveStatus currMoveStatus = MoveStatus::Jump;
	MoveStatus prevMoveStatus = MoveStatus::Jump;
	MoveStatus prevLeftRightStatus = MoveStatus::Left;

	double timer = 0;
	bool MoveLeft = false;
	double MoveLeftTime = 0;
	bool MoveRight = false;
	double MoveRightTime = 0;
	bool Jump_after_moving = false;
	bool is_jumping_now = false;
};