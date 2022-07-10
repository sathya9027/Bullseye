#pragma once
class Window
{
private:
public:
	Window();
	~Window();
	GLFWwindow* gameWindow;
	float windowWidth, windowHeight;
	float X, Y, R, B;
	void CreateGameWindow(int screenWidth, int screenHeight, const char* windowName, bool isFullScreen);
	void SetBGColor(float r, float g, float b, float a);
	void UpdateWindow();
	bool IsWindowNotClosed();
	void close();
};

