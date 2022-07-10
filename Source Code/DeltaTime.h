#pragma once
class DeltaTime
{
private:
	double lastFrame, currentFrame, deltaTime;
public:
	DeltaTime();
	~DeltaTime();
	void Update();
	double getDeltaTime();
};

