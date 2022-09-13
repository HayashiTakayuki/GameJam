#pragma once
#pragma once
class Timer
{
private:
	int maxTime;
	int time;

public:
	Timer(int maxTime);
	~Timer() {};

	void Reset();
	void Update();
	bool isEnd();
	int GetTime();
	void SetMaxTime(int maxTime);
};

