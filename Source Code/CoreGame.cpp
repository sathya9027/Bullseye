#include "Common.h"
CoreGame::CoreGame() {
	this->spawnCapacity = 5;
	this->scopePos = vec2(0.0f, 0.0f);
	this->explosionPos = vec2(0.0f, 0.0f);
	this->bgPos = vec2(0.0f, 0.0f);
	this->gunPos = vec2(0.0f, 0.0f);
	this->score = 0;
	this->xPos = 0;
	this->yPos = 0;
	this->life = 5;
	this->spawnTimerMax = 3000;
	this->spawnTimer = 0;
	this->isTimerGotShot = false;
	this->isClearPickupGotShot = false;
	this->greenCount = 0;
	this->redCount = 0;
	this->shootSFX.InitAudio("Assets\\shoot.wav");
	this->pointSFX.InitAudio("Assets\\pickupSFX.wav");
}
CoreGame::~CoreGame() {
	this->targets.clear();
}
int CoreGame::GetPlayerLife() {
	return this->life;
}
void CoreGame::Reset() {
	this->spawnCapacity = 5;
	this->scopePos = vec2(0.0f, 0.0f);
	this->explosionPos = vec2(0.0f, 0.0f);
	this->bgPos = vec2(0.0f, 0.0f);
	this->gunPos = vec2(0.0f, 0.0f);
	this->score = 0;
	this->xPos = 0;
	this->yPos = 0;
	this->life = 5;
	this->greenCount = 0;
	this->redCount = 0;
	this->spawnTimerMax = 3000;
	this->spawnTimer = 0;
	this->isTimerGotShot = false;
	this->isClearPickupGotShot = false;
}
int CoreGame::RandomType() {
	int type;
	int randValue = rand() % 100 + 1;
	if (randValue > 40 && randValue <= 80) {
		type = TargetType::RandomTeleport;
	}
	else if (randValue > 80) {
		type = TargetType::UpToDown;
	}
	else {
		type = TargetType::LeftToRight;
	}
	return type;
}
int CoreGame::RandomPhrase() {
	int type;
	int randValue = rand() % 100 + 1;
	if (randValue > 30) {
		type = TargetPhase::RED;
	}
	else {
		type = TargetPhase::GREEN;
	}
	return type;
}
void CoreGame::InitSprite() {
	this->scope.CreateBuffers(100, 100);
	this->scope.LoadTexture("Assets\\tempScope.png");

	this->explosion.CreateBuffers(50, 50);
	this->explosion.LoadTexture("Assets\\explosion.png");

	this->bg.CreateBuffers(WINDOW_WIDTH, WINDOW_HEIGHT);
	this->bg.LoadTexture("Assets\\background.png");

	this->gun.CreateBuffers(280, 204.4);
	this->gun.LoadTexture("Assets\\gun.png");

	this->scoreSprite.CreateBuffers(100, 100);
	this->scoreSprite.LoadTexture("Assets\\score.png");

	this->lifeSprite.CreateBuffers(100, 100);
	this->lifeSprite.LoadTexture("Assets\\life.png");

	this->boomSprite.CreateBuffers(640 * 2, 480 * 2);
	this->boomSprite.LoadTexture("Assets\\boom.png");

	this->healthSprite.CreateBuffers(800, 800);
	this->healthSprite.LoadTexture("Assets\\health.png");
}
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	glfwSetCursorPos(window, xpos, ypos);
}
void CoreGame::CursorMovement(Window window) {
	glfwSetInputMode(window.gameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetMouseButtonCallback(window.gameWindow, GLFW_MOUSE_BUTTON_LEFT);
	glfwGetCursorPos(window.gameWindow, &this->xPos, &this->yPos);

	this->scopePos.x = this->xPos;
	this->scopePos.y = -this->yPos;

	/*if (xPos<0 || xPos>WINDOW_WIDTH || yPos<0 || yPos>WINDOW_HEIGHT) {
		glfwSetCursorPosCallback(window.gameWindow, cursor_position_callback);
	}*/

	//gun movement
	if (this->xPos >= 0 && this->xPos <= double(WINDOW_WIDTH - (gun.getSize().x))) {
		this->gunPos.x = this->xPos;
	}

	//gun flip
	if (this->xPos > (WINDOW_WIDTH - gun.getSize().x) / 2) {
		this->gun.setFlip() = true;
	}
	else {
		this->gun.setFlip() = false;
	}
}
void CoreGame::KeyboardMovement(Window window) {
	if (glfwGetKey(window.gameWindow, GLFW_KEY_D) == GLFW_PRESS) {
		this->scopePos.x += 5.0f;
	}
	else if (glfwGetKey(window.gameWindow, GLFW_KEY_A) == GLFW_PRESS) {
		this->scopePos.x -= 5.0f;
	}
	else if (glfwGetKey(window.gameWindow, GLFW_KEY_W) == GLFW_PRESS) {
		this->scopePos.y += 5.0f;
	}
	else if (glfwGetKey(window.gameWindow, GLFW_KEY_S) == GLFW_PRESS) {
		this->scopePos.y -= 5.0f;
	}
}
void CoreGame::SpawnTarget() {
	//spawning target's
	while (this->targets.size() < this->spawnCapacity)
	{
		int tempPhrase;
		int tempType;
		tempPhrase = this->RandomPhrase();
		tempType = this->RandomType();
		if (tempPhrase == TargetPhase::GREEN) {
			greenCount++;
		}
		else if (tempPhrase == TargetPhase::RED) {
			redCount++;
		}
		this->targets.push_back(Targets(tempPhrase, tempType));
	}
}
void CoreGame::SpawnTimer() {
	if (this->spawnTimer < this->spawnTimerMax) {
		this->spawnTimer += 1.0f;
	}
	else {
		this->spawnCapacity++;
		this->spawnTimer = 0;
	}
}
void CoreGame::ShootLifePickups(Window window, Shader shader, Sprite pickups) {
	static int oldState = GLFW_RELEASE;
	int newState = glfwGetMouseButton(window.gameWindow, GLFW_MOUSE_BUTTON_LEFT);
	if (newState == GLFW_RELEASE && oldState == GLFW_PRESS) {
		if (this->scope.CircleCollision(pickups)) {
			this->life++;
			cout << life << endl;

			this->healthSprite.setPosition()= vec2((WINDOW_WIDTH / 2) - (this->healthSprite.getSize().x / 2), (WINDOW_HEIGHT / 2) - (this->healthSprite.getSize().y / 2));

			this->healthSprite.Update(shader);
			this->healthSprite.Draw(shader);

			this->explosion.setPosition().x = this->scope.getCenter().x - this->explosion.getSize().x / 2;
			this->explosion.setPosition().y = this->scope.getCenter().y - this->explosion.getSize().y / 2;

			this->explosion.Update(shader);
			this->explosion.Draw(shader);
			this->pointSFX.InitAudio("Assets\\pickupSFX.wav");
			this->pointSFX.PlayAudio();
		}
	}
	oldState = newState;
}
int CoreGame::GetGreenTargetCount() {
	return this->greenCount;
}
void CoreGame::ShootTimeBoostPickups(Window window, Shader shader, Sprite pickups) {
	static int oldState = GLFW_RELEASE;
	int newState = glfwGetMouseButton(window.gameWindow, GLFW_MOUSE_BUTTON_LEFT);
	if (newState == GLFW_RELEASE && oldState == GLFW_PRESS) {
		if (this->scope.CircleCollision(pickups)) {
			this->explosion.setPosition().x = this->scope.getCenter().x - this->explosion.getSize().x / 2;
			this->explosion.setPosition().y = this->scope.getCenter().y - this->explosion.getSize().y / 2;

			this->explosion.Update(shader);
			this->explosion.Draw(shader);

			this->score += 5;

			this->isTimerGotShot = true;
			this->pointSFX.InitAudio("Assets\\pickupSFX.wav");
			this->pointSFX.PlayAudio();
		}
		else {
			this->shootSFX.InitAudio("Assets\\shoot.wav");
			this->shootSFX.PlayAudio();
		}
	}
	oldState = newState;
}
void CoreGame::ShootClearTargetsPickups(Window window, Shader shader, Sprite pickups) {
	static int oldState = GLFW_RELEASE;
	int newState = glfwGetMouseButton(window.gameWindow, GLFW_MOUSE_BUTTON_LEFT);
	if (newState == GLFW_RELEASE && oldState == GLFW_PRESS) {
		if (this->scope.CentreCollision(pickups)) {
			this->targets.clear();

			this->redCount = 0;
			this->greenCount = 0;
			this->RenderBoomSprite(shader);

			this->score += 10;

			this->isClearPickupGotShot = true;

			this->explosion.setPosition().x = this->scope.getCenter().x - this->explosion.getSize().x / 2;
			this->explosion.setPosition().y = this->scope.getCenter().y - this->explosion.getSize().y / 2;

			this->explosion.Update(shader);
			this->explosion.Draw(shader);
			this->pointSFX.InitAudio("Assets\\pickupSFX.wav");
			this->pointSFX.PlayAudio();
		}
	}
	oldState = newState;
}
bool& CoreGame::SetTimerBool() {
	return this->isTimerGotShot;
}
bool CoreGame::GetTimerBool() {
	return this->isTimerGotShot;
}
void CoreGame::RenderBoomSprite(Shader shader) {
	this->boomSprite.setPosition() = vec2((WINDOW_WIDTH / 2) - (this->boomSprite.getSize().x / 2), (WINDOW_HEIGHT / 2) - (this->boomSprite.getSize().y / 2));
	this->boomSprite.Update(shader);
	this->boomSprite.Draw(shader);
}
bool& CoreGame::SetClearBool() {
	return this->isClearPickupGotShot;
}
bool CoreGame::GetClearBool() {
	return this->isClearPickupGotShot;
}
void CoreGame::RenderTarget(Window window, Shader shader) {
	//update and draw target's
	for (size_t i = 0; i < this->targets.size(); i++)
	{
		this->targets[i].UpdatePosition(window);

		this->targets[i].getTarget().Update(shader);

		this->targets[i].getTarget().Draw(shader);
	}
}
void CoreGame::RenderBackground(Shader shader) {
	this->bg.setPosition() = this->bgPos;
	this->bg.Update(shader);
	this->bg.Draw(shader);
}
void CoreGame::ShootTarget(Window window, Shader shader) {
	static int oldState = GLFW_RELEASE;
	int newState = glfwGetMouseButton(window.gameWindow, GLFW_MOUSE_BUTTON_LEFT);
	if (newState == GLFW_RELEASE && oldState == GLFW_PRESS) {
		for (int i = 0; i < targets.size(); i++)
		{
			if (this->scope.CentreCollision(this->targets[i].getTarget())) {
				if (this->targets[i].getTargetPhrase() == TargetPhase::RED) {
					redCount--;
					this->score++;
					cout << "score: " << this->score << endl;

					if (this->targets[i].getTarget().getPosition().y > 600) {
						this->scoreSprite.setPosition().x = this->scope.getPosition().x - this->scope.getSize().x;
						this->scoreSprite.setPosition().y = this->scope.getPosition().y - this->scope.getSize().y;
					}
					else {
						this->scoreSprite.setPosition().x = this->scope.getCenter().x;
						this->scoreSprite.setPosition().y = this->scope.getCenter().y;
					}

					this->scoreSprite.Update(shader);
					this->scoreSprite.Draw(shader);
				}
				else if (this->targets[i].getTargetPhrase() == TargetPhase::GREEN) {
					greenCount--;
					this->life--;
					cout << "life: " << this->life << endl;

					if (this->targets[i].getTarget().getPosition().y > 600) {

						this->lifeSprite.setPosition().x = this->scope.getPosition().x - this->scope.getSize().x;
						this->lifeSprite.setPosition().y = this->scope.getPosition().y - this->scope.getSize().y;
					}
					else {
						this->lifeSprite.setPosition().x = this->scope.getCenter().x;
						this->lifeSprite.setPosition().y = this->scope.getCenter().y;
					}

					this->lifeSprite.Update(shader);
					this->lifeSprite.Draw(shader);
				}
				this->targets.erase(this->targets.begin() + i);

				this->explosion.setPosition().x = this->scope.getCenter().x - this->explosion.getSize().x / 2;
				this->explosion.setPosition().y = this->scope.getCenter().y - this->explosion.getSize().y / 2;

				this->explosion.Update(shader);
				this->explosion.Draw(shader);
				this->pointSFX.InitAudio("Assets\\pickupSFX.wav");
				this->pointSFX.PlayAudio();
			}
		}
	}
	oldState = newState;
	if (this->life <= 0) {
		//window.close();
	}
}
void CoreGame::RenderPlayer(Shader shader) {
	this->scope.setPosition() = this->scopePos;
	this->scope.Update(shader);
	this->scope.Draw(shader);

	this->gun.setPosition() = this->gunPos;
	this->gun.Update(shader);
	this->gun.Draw(shader);
}
int CoreGame::GetCapacity() {
	return this->spawnCapacity;
}
void CoreGame::UpdateGameplay(Window window, Shader shader) {
	cout << redCount << " | " << greenCount << endl;
	CursorMovement(window);
	KeyboardMovement(window);
	SpawnTimer();
	SpawnTarget();
	ShootTarget(window, shader);
	RenderTarget(window, shader);
}
