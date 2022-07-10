#pragma once
class GameOver
{
private:
	Sprite gameOver;
	Sprite playAgain;
	Sprite mainMenu;
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
	GameOver();
	~GameOver();
	int GetButtonIndex();
	bool GetBool();
	void SetBool(bool setBoll);
	void InitSprite();
	void ShootButton(Window window);
	void RenderSprite(Shader shader);
	void CursorMovement(Window window);
};

