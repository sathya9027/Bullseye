#pragma once
class CoreGame
{
private:
	//Audio
	Audio shootSFX;
	Audio pointSFX;
	//sprite's
	Sprite scoreSprite;
	Sprite lifeSprite;
	Sprite boomSprite;
	Sprite healthSprite;
	Sprite scope;
	Sprite explosion;
	Sprite bg;
	Sprite gun;
	//vec2 for sprite positions
	vec2 scopePos;
	vec2 explosionPos;
	vec2 bgPos;
	vec2 gunPos;
	//getting mouse x and y position
	double xPos, yPos;
	//all integer variables
	int score;
	int spawnCapacity;
	int life;
	int redCount;
	int greenCount;
	//spawn timer variable
	float spawnTimerMax;
	float spawnTimer;
	//vector for storing all target's
	vector<Targets> targets;
	//bool variable's
	bool isTimerGotShot;
	bool isClearPickupGotShot;
	//functions to run the game
	int RandomType();
	int RandomPhrase();
	void CursorMovement(Window window);
	void KeyboardMovement(Window window);
	void ShootTarget(Window window, Shader shader);
	void SpawnTarget();
	void SpawnTimer();
public:
	CoreGame();
	~CoreGame();
	//public functions which will be access by other class
	int GetPlayerLife();
	int GetGreenTargetCount();
	int GetCapacity();
	void InitSprite();
	void Reset();
	void ShootLifePickups(Window window, Shader shader, Sprite pickups);
	void ShootTimeBoostPickups(Window window, Shader shader, Sprite pickups);
	void ShootClearTargetsPickups(Window window, Shader shader, Sprite pickups);
	bool& SetTimerBool();
	bool GetTimerBool();
	bool& SetClearBool();
	bool GetClearBool();
	void UpdateGameplay(Window window, Shader shader);
	void RenderBackground(Shader shader);
	void RenderPlayer(Shader shader);
	void RenderTarget(Window window, Shader shader);
	void RenderBoomSprite(Shader shader);
};

