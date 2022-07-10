#pragma once
enum TargetPhase { GREEN, RED };
enum TargetType { LeftToRight, UpToDown, RandomTeleport, Diagonal };
class Targets
{
private:
	Sprite target;
	vec2 targetPosition;
	int targetPhrase;
	int targetType;
	int spawnMinX;
	int spawnMinY;
	int spawnMaxX;
	int spawnMaxY;
	bool leftOrRight;	
	float timer, timerMax;
	float targetSpeed;
	void InitTarget();
public:
	Targets(int targetPhrase, int targetType);
	~Targets();
	int getTargetPhrase();
	Sprite &getTarget();
	void UpdatePosition(Window window);
	void Shoot(Sprite scope, Window window);
};

