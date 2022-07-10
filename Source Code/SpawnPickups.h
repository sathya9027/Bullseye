#pragma once
class SpawnPickups
{
private:
	Sprite lifePickup;
	Sprite timeBoostPickup;
	Sprite clearTargetsPickup;
	vec2 lifePickupPos;
	vec2 timeBoostPickupPos;
	vec2 clearTargetsPickupPos;
	int topOrBottom;
	int spawnMinX;
	int spawnMinY;
	int spawnMaxX;
	int spawnMaxY;
	float lifeTimer, lifeTimerMax;
	float timeBoostTimer, timeBoostTimerMax;
public:
	SpawnPickups();
	~SpawnPickups();
	Sprite &getLifePickup();
	Sprite &getTimeBoostPickup();
	Sprite &getClearTargetsPickup();
	void LifePickupMovement();
	void ResetClearTargetsPickup();
	void TimeBoostPickupMovement();
	void ClearTargetsPickupMovement();
	void InitPickupSprite();
	void RenderLifePickups(Shader shader);
	void RenderTimeBoostPickups(Shader shader);
	void RenderClearTargetsPickups(Shader shader);
};

