#pragma once
class MainMenu
{
private:
	Sprite title;
	Sprite play;
	Sprite instruction;
	Sprite exit;
	Sprite bg;
	Sprite scope;
	Sprite gun;
	double xPos, yPos;
	vec2 scopePos;
	vec2 gunPos;
	int buttonIndex;
	bool isButtonPressed;
public:
	MainMenu();
	~MainMenu();
	int GetButtonIndex();
	bool GetBool();
	void SetBool(bool setBool);
	void InitSprite();
	void ShootButton(Window window);
	void RenderSprite(Shader shader);
	void CursorMovement(Window window);
};

