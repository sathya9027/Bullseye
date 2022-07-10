#pragma once
class Timer
{
private:
	int seconds;
	int temp;
	int maxSeconds;
	int currentTime;
public:
	Timer();
	~Timer();
	int& SetCurrentTime();
	void SetTimer(int _maxSeconds);
	void RunTimer();
	int GetTimer();
	int GetMaxTimeLimit();
};

