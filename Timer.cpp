#include "Timer.h"

Timer::Timer(int maxTime)
{
	this->maxTime = maxTime;
	time = 0;

}

void Timer::Reset()
{
	time = 0;
}

void Timer::Update()
{
	time++;
	if (time >= maxTime)time = maxTime;
}

bool Timer::isEnd()
{
	return time >= maxTime;
}

int Timer::GetTime()
{
	return time;
}

void Timer::SetMaxTime(int maxTime)
{

	this->maxTime = maxTime;

}


