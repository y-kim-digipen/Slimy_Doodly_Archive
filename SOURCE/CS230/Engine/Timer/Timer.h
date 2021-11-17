/*--------------------------------------------------------------
File Name: Timer.h
Project: Slimy Doodly
Author: Yoonki Kim
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
class Timer
{
public:
	Timer(double intervalTime);

	void Init();
	void Update(double dt);
	bool IsSettedTime();
	double GetTimeInterval() const;
	double GetElapsedTile() const { return elapsedTime; }

private:
	const double settedIntervalTime;
	double elapsedTime = 0.0;
	double alertTime = 0.0;
};
#pragma once
