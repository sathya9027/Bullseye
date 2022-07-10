#include "Common.h"
Targets::Targets(int targetPhrase, int targetType) {
	this->targetPhrase = targetPhrase;
	this->targetType = targetType;
	this->leftOrRight = 0;
	this->targetSpeed = 5.0f;
	this->timerMax = 200;
	this->spawnMinX = 0;
	this->spawnMinY = 200;
	this->InitTarget();
}
Targets::~Targets() {

}
int Targets::getTargetPhrase() {
	return this->targetPhrase;
}
Sprite &Targets::getTarget() {
	return this->target;
}
void Targets::UpdatePosition(Window window) {
	switch (this->targetType)
	{
	case LeftToRight:
		if (this->target.getPosition().x <= spawnMinX) {
			this->leftOrRight = 0;
		}
		else if (this->target.getPosition().x >= spawnMaxX) {
			this->leftOrRight = 1;
		}

		if (this->leftOrRight == 0) {
			this->target.setPosition().x += this->targetSpeed;
		}
		else if (this->leftOrRight == 1) {
			this->target.setPosition().x -= this->targetSpeed;
		}
		break;
	case UpToDown:
		if (this->target.getPosition().y <= spawnMinY) {
			this->leftOrRight = 0;
		}
		else if (this->target.getPosition().y >= spawnMaxY) {
			this->leftOrRight = 1;
		}

		if (this->leftOrRight == 0) {
			this->target.setPosition().y += this->targetSpeed;
		}
		else if (leftOrRight == 1) {
			this->target.setPosition().y -= this->targetSpeed;
		}
		break;
	case RandomTeleport:
		if (this->timer < this->timerMax) {
			this->timer += 1.0f;
		}
		else {
			float randXPos, randYPos;
			randXPos = spawnMinX + (rand() % (spawnMaxX - spawnMinX + 1));
			randYPos = spawnMinY + (rand() % (spawnMaxY - spawnMinY + 1));
			this->targetPosition = vec2(randXPos, randYPos);
			this->target.setPosition() = this->targetPosition;
			this->timer = 0;
		}
		break;
	case Diagonal:
		if (this->target.WindowCollision(window)) {
			this->leftOrRight = 0;
			cout << "window collision" << endl;
		}
		else {
			this->leftOrRight = 1;
			cout << "window no collision" << endl;
		}

		if (this->leftOrRight == 0) {
			this->target.setPosition().x += this->targetSpeed;
			this->target.setPosition().y += this->targetSpeed;
		}
		else if (this->leftOrRight == 1) {
			this->target.setPosition().x -= this->targetSpeed;
			this->target.setPosition().y -= this->targetSpeed;
		}
		break;
	}
	
}
void Targets::Shoot(Sprite scope, Window window) {
	static int oldState = GLFW_RELEASE;
	int newState = glfwGetMouseButton(window.gameWindow, GLFW_MOUSE_BUTTON_LEFT);
	if (newState == GLFW_RELEASE && oldState == GLFW_PRESS) {
		if (target.CircleCollision(scope)) {
			cout << "shooting" << endl;
		}
	}
	oldState = newState;
}
void Targets::InitTarget() {
	int size;
	int min = 75;
	int max = 125;
	size = min + (rand() % (max - min + 1));
	switch (this->targetPhrase)
	{
	case GREEN:
		this->target.CreateBuffers(size, size);
		this->target.LoadTexture("Assets\\dart-2.png");
		break;
	case RED:
		this->target.CreateBuffers(size, size);
		this->target.LoadTexture("Assets\\dart-1.png");
		break;
	}
	this->spawnMaxX = (WINDOW_WIDTH - this->target.getSize().x);
	this->spawnMaxY = (WINDOW_HEIGHT - this->target.getSize().y);
	float randXPos, randYPos;
	randXPos = spawnMinX + (rand() % (spawnMaxX - spawnMinX + 1));
	randYPos = spawnMinY + (rand() % (spawnMaxY - spawnMinY + 1));
	this->targetPosition = vec2(randXPos, randYPos);
	this->target.setPosition() = this->targetPosition;
}