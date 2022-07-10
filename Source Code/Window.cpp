#include "Common.h"
Window::Window() {
	this->gameWindow = NULL;
	this->windowWidth = NULL;
	this->windowHeight = NULL;
	this->X = 0;
	this->Y = 0;
	this->R = 0 + windowWidth;
	this->B = 0 + windowHeight;
	glfwInit();
}
Window::~Window() {

}
void ReSizeWindow(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void Window::CreateGameWindow(int screenWidth, int screenHeight, const char* windowName, bool isFullScreen) {
	if (isFullScreen) {
		this->gameWindow = glfwCreateWindow(screenWidth, screenHeight, windowName, glfwGetPrimaryMonitor(), NULL);
	}
	else {
		this->gameWindow = glfwCreateWindow(screenWidth, screenHeight, windowName, NULL, NULL);
	}

	this->windowWidth = screenWidth;
	this->windowHeight = screenHeight;

	if (this->gameWindow == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
	}
	else {
		glfwMakeContextCurrent(this->gameWindow);
		glfwSetInputMode(this->gameWindow, GLFW_STICKY_KEYS, GL_TRUE);
		glfwSetFramebufferSizeCallback(this->gameWindow, ReSizeWindow);
	}
}
void Window::SetBGColor(float r, float g, float b, float a) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(r, g, b, a);
}
void Window::UpdateWindow() {
	this->X = 0;
	this->Y = 0;
	this->R = 0 + this->windowWidth;
	this->B = 0 + this->windowHeight;
	glfwPollEvents();
	glfwSwapBuffers(this->gameWindow);
}
bool Window::IsWindowNotClosed() {
	if ((glfwGetKey(this->gameWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS) &&
		(glfwWindowShouldClose(this->gameWindow) == 0)) {
		return true;
	}
	else {
		return false;
	}
}
void Window::close() {
	glfwSetWindowShouldClose(this->gameWindow, 1);
}
