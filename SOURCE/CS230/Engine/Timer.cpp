#include <chrono>				//std::chrono::system_clock
class Timer
{
	Timer(double intervalTime)
	:settedIntervalTime(intervalTime), alertTime(settedIntervalTime)
	{};

	void update(double dt)
	{
		elapsedTime += dt;
	};
	
	bool isSettedTime()
	{
		if(elapsedTime >= alertTime)
		{
			elapsedTime += settedIntervalTime;
			return true;
		}
		else
		{
			return false;
		}
	};

	[[nodiscard]] double getTimeInterval() const
	{
		return settedIntervalTime;
	}

private:
	const double settedIntervalTime;
	double elapsedTime = 0.0;
	double alertTime;
};

