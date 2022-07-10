#include "Common.h"
MainMenu::MainMenu() {

}
MainMenu::~MainMenu() {

}
int MainMenu::GetButtonIndex() {
	return this->buttonIndex;
}
bool MainMenu::GetBool() {
	return this->isButtonPressed;
}
void MainMenu::SetBool(bool setBool) {
	this->isButtonPressed = setBool;
}
void MainMenu::InitSprite() {
	this->title.CreateBuffers(800, 150);
	this->title.LoadTexture("Assets\\title.png");

	this->play.CreateBuffers(310, 150);
	this->play.LoadTexture("Assets\\play.png");

	this->instruction.CreateBuffers(800, 120);
	this->instruction.LoadTexture("Assets\\instruction.png");

	this->exit.CreateBuffers(290, 120);
	this->exit.LoadTexture("Assets\\exit.png");

	this->bg.CreateBuffers(WINDOW_WIDTH, WINDOW_HEIGHT);
	this->bg.LoadTexture("Assets\\bgTemp.png");

	this->scope.CreateBuffers(100, 100);
	this->scope.LoadTexture("Assets\\tempScope.png");

	this->gun.CreateBuffers(280, 204.4);
	this->gun.LoadTexture("Assets\\gun.png");
}
void MainMenu::ShootButton(Window window) {
	static int oldState = GLFW_RELEASE;
	int newState = glfwGetMouseButton(window.gameWindow, GLFW_MOUSE_BUTTON_LEFT);
	if (newState == GLFW_RELEASE && oldState == GLFW_PRESS) {
		if (this->scope.CentreCollision(this->play)) {
			cout << "play" << endl;
			this->isButtonPressed = true;
			this->buttonIndex = 0;
		}
		else if (this->scope.CentreCollision(this->instruction)) {
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
void MainMenu::RenderSprite(Shader shader) {
	this->bg.Update(shader);
	this->bg.Draw(shader);

	this->title.setPosition() = vec2((WINDOW_WIDTH / 2) - (this->title.getSize().x / 2), 800);

	this->title.Update(shader);
	this->title.Draw(shader);

	this->play.setPosition() = vec2(150, 400);

	this->play.Update(shader);
	this->play.Draw(shader);

	this->instruction.setPosition() = vec2(150, 200);

	this->instruction.Update(shader);
	this->instruction.Draw(shader);

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
void MainMenu::CursorMovement(Window window) {
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
