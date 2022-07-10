#include "Common.h"
SpawnPickups::SpawnPickups() {
	this->lifePickupPos = vec2(0, 0);
	this->timeBoostPickupPos = vec2(0, 0);
	this->spawnMinX = 0;
	this->spawnMinY = 200;
	this->lifeTimerMax = 100;
	this->timeBoostTimerMax = 100;
	this->topOrBottom = 0;
}
SpawnPickups::~SpawnPickups() {

}
Sprite& SpawnPickups::getLifePickup() {
	return this->lifePickup;
}
Sprite& SpawnPickups::getTimeBoostPickup() {
	return this->timeBoostPickup;
}
Sprite& SpawnPickups::getClearTargetsPickup() {
	return this->clearTargetsPickup;
}
void SpawnPickups::LifePickupMovement() {
	if (this->lifeTimer < this->lifeTimerMax) {
		this->lifeTimer += 1.0f;
	}
	else {
		float randXPos, randYPos;
		this->spawnMaxX = (WINDOW_WIDTH - this->lifePickup.getSize().x);
		this->spawnMaxY = (WINDOW_HEIGHT - this->lifePickup.getSize().y);
		randXPos = spawnMinX + (rand() % (spawnMaxX - spawnMinX + 1));
		randYPos = spawnMinY + (rand() % (spawnMaxY - spawnMinY + 1));
		this->lifePickupPos = vec2(randXPos, randYPos);
		this->lifePickup.setPosition() = this->lifePickupPos;
		this->lifeTimer = 0;
	}
}
void SpawnPickups::ResetClearTargetsPickup() {
	float randXPos;
	this->spawnMaxX = (WINDOW_WIDTH - this->clearTargetsPickup.getSize().x);
	randXPos = spawnMinX + (rand() % (spawnMaxX - spawnMinX + 1));
	this->clearTargetsPickupPos = vec2(randXPos, 0);
	this->clearTargetsPickup.setPosition() = this->clearTargetsPickupPos;
	this->topOrBottom = 0;
}
void SpawnPickups::TimeBoostPickupMovement() {
	if (this->timeBoostTimer < this->timeBoostTimerMax) {
		this->timeBoostTimer += 1.0f;
	}
	else {
		float randXPos, randYPos;
		this->spawnMaxX = (WINDOW_WIDTH - this->timeBoostPickup.getSize().x);
		this->spawnMaxY = (WINDOW_HEIGHT - this->timeBoostPickup.getSize().y);
		randXPos = spawnMinX + (rand() % (spawnMaxX - spawnMinX + 1));
		randYPos = spawnMinY + (rand() % (spawnMaxY - spawnMinY + 1));
		this->timeBoostPickupPos = vec2(randXPos, randYPos);
		this->timeBoostPickup.setPosition() = this->timeBoostPickupPos;
		this->timeBoostTimer = 0;
	}
}
void SpawnPickups::ClearTargetsPickupMovement() {
	if (this->clearTargetsPickup.getPosition().y >= (WINDOW_WIDTH - this->clearTargetsPickup.getSize().y)) {
		this->topOrBottom = 1;
	}
	else if (this->clearTargetsPickup.getPosition().y < -10) {
		this->ResetClearTargetsPickup();
	}

	if (this->topOrBottom == 0) {

		this->clearTargetsPickup.setPosition().y += 7.5;
	}
	else if (this->topOrBottom == 1) {

		this->clearTargetsPickup.setPosition().y -= 7.5;
	}
}
void SpawnPickups::InitPickupSprite() {
	this->lifePickup.CreateBuffers(75, 75);
	this->lifePickup.LoadTexture("Assets\\heart.png");

	this->timeBoostPickup.CreateBuffers(125, 125);
	this->timeBoostPickup.LoadTexture("Assets\\clock.png");

	this->clearTargetsPickup.CreateBuffers(100, 100);
	this->clearTargetsPickup.LoadTexture("Assets\\bomb.png");

	float randXPos, randYPos;
	this->spawnMaxX = (WINDOW_WIDTH - this->lifePickup.getSize().x);
	this->spawnMaxY = (WINDOW_HEIGHT - this->lifePickup.getSize().y);
	randXPos = spawnMinX + (rand() % (spawnMaxX - spawnMinX + 1));
	randYPos = spawnMinY + (rand() % (spawnMaxY - spawnMinY + 1));
	this->lifePickupPos = vec2(randXPos, randYPos);
	this->lifePickup.setPosition() = this->lifePickupPos;

	this->spawnMaxX = (WINDOW_WIDTH - this->timeBoostPickup.getSize().x);
	this->spawnMaxY = (WINDOW_HEIGHT - this->timeBoostPickup.getSize().y);
	randXPos = spawnMinX + (rand() % (spawnMaxX - spawnMinX + 1));
	randYPos = spawnMinY + (rand() % (spawnMaxY - spawnMinY + 1));
	this->timeBoostPickupPos = vec2(randXPos, randYPos);
	this->timeBoostPickup.setPosition() = this->timeBoostPickupPos;
	
	this->spawnMaxX = (WINDOW_WIDTH - this->clearTargetsPickup.getSize().x);
	randXPos = spawnMinX + (rand() % (spawnMaxX - spawnMinX + 1));
	this->clearTargetsPickupPos = vec2(randXPos, 0);
	this->clearTargetsPickup.setPosition() = this->clearTargetsPickupPos;
}
void SpawnPickups::RenderLifePickups(Shader shader) {
	this->lifePickup.Update(shader);
	this->lifePickup.Draw(shader);
}
void SpawnPickups::RenderTimeBoostPickups(Shader shader) {
	this->timeBoostPickup.Update(shader);
	this->timeBoostPickup.Draw(shader);
}
void SpawnPickups::RenderClearTargetsPickups(Shader shader) {
	this->clearTargetsPickup.Update(shader);
	this->clearTargetsPickup.Draw(shader);
}
