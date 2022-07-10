#include "Common.h"
GameOver::GameOver() {

}
GameOver::~GameOver() {

}
int GameOver::GetButtonIndex() {
	return this->buttonIndex;
}
bool GameOver::GetBool() {
	return this->isButtonPressed;
}
void GameOver::SetBool(bool setBoll) {
	this->isButtonPressed = setBoll;
}
void GameOver::InitSprite() {
	this->gameOver.CreateBuffers(800, 150);
	this->gameOver.LoadTexture("Assets\\gameOver.png");

	this->playAgain.CreateBuffers(310, 150);
	this->playAgain.LoadTexture("Assets\\playAgain.png");

	this->mainMenu.CreateBuffers(800, 120);
	this->mainMenu.LoadTexture("Assets\\mainMenu.png");

	this->exit.CreateBuffers(290, 120);
	this->exit.LoadTexture("Assets\\exit.png");

	this->bg.CreateBuffers(WINDOW_WIDTH, WINDOW_HEIGHT);
	this->bg.LoadTexture("Assets\\bgTemp.png");

	this->scope.CreateBuffers(100, 100);
	this->scope.LoadTexture("Assets\\tempScope.png");

	this->gun.CreateBuffers(280, 204.4);
	this->gun.LoadTexture("Assets\\gun.png");
}
void GameOver::ShootButton(Window window) {
	static int oldState = GLFW_RELEASE;
	int newState = glfwGetMouseButton(window.gameWindow, GLFW_MOUSE_BUTTON_LEFT);
	if (newState == GLFW_RELEASE && oldState == GLFW_PRESS) {
		if (this->scope.CentreCollision(this->playAgain)) {
			cout << "play" << endl;
			this->isButtonPressed = true;
			this->buttonIndex = 0;
		}
		else if (this->scope.CentreCollision(this->mainMenu)) {
			cout << "instruction" << endl;
			this->isButtonPressed = true;
			this->buttonIndex = 1;
		}
		else if (this->scope.CentreCollision(this->exit)) {
			cout << "exit" << endl;
			glfwSetWindowShouldClose(window.gameWindow, 1);
			this->buttonIndex = 2;
		}
	}
	oldState = newState;
}
void GameOver::RenderSprite(Shader shader) {
	this->bg.Update(shader);
	this->bg.Draw(shader);

	this->gameOver.setPosition() = vec2((WINDOW_WIDTH / 2) - (this->gameOver.getSize().x / 2), 800);

	this->gameOver.Update(shader);
	this->gameOver.Draw(shader);

	this->playAgain.setPosition() = vec2(150, 400);

	this->playAgain.Update(shader);
	this->playAgain.Draw(shader);

	this->mainMenu.setPosition() = vec2(150, 200);

	this->mainMenu.Update(shader);
	this->mainMenu.Draw(shader);

	this->exit.setPosition() = vec2(1550, 200);

	this->exit.Update(shader);
	this->exit.Draw(shader);

	this->scope.setPosition() = this->scopePos;
	this->scope.Update(shader);
	this->scope.Draw(shader);

	this->gun.setPosition() = this->gunPos;
	this->gun.Update(shader);
	this->gun.Draw(shader);
}
void GameOver::CursorMovement(Window window) {
	glfwSetInputMode(window.gameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetMouseButtonCallback(window.gameWindow, GLFW_MOUSE_BUTTON_LEFT);
	glfwGetCursorPos(window.gameWindow, &this->xPos, &this->yPos);

	this->scopePos.x = this->xPos;
	this->scopePos.y = -this->yPos;

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
