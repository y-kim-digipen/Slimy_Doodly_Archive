/*--------------------------------------------------------------
File Name: Timer.cpp
Project: Slimy Doodly
Author: Yoonki Kim
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "Timer.h"

Timer::Timer(double intervalTime): settedIntervalTime(intervalTime) {}

void Timer::Init()
{
	elapsedTime = 0.0;
	alertTime = elapsedTime + settedIntervalTime;
}

void Timer::Update(double dt)
{
	elapsedTime += dt;
}

bool Timer::IsSettedTime()
{
	if (elapsedTime >= alertTime)
	{
		elapsedTime = 0.0;
		return true;
	}
	else
	{
		return false;
	}
}

double Timer::GetTimeInterval() const
{
	return settedIntervalTime;
}


