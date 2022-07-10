#include "Common.h"
DeltaTime::DeltaTime() {
	lastFrame = 0;
	currentFrame = 0;
	deltaTime = 0;
}
DeltaTime::~DeltaTime() {

}
void DeltaTime::Update() {
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}
double DeltaTime::getDeltaTime() {
	return deltaTime;
}