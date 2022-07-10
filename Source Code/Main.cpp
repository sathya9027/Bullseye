#include "Common.h" //it has all include syntax

Window window;		//window class
Shader shader;		//shader class
Camera camera;		//camera class

CoreGame coreGame;
SpawnPickups spawnPickups;
MainMenu mainMenu;
GameOver gameOver;

Timer gameplayTimer;

enum GameState
{
	START,
	PLAY,
	END
};

int gameState = GameState::START;
//double lasttime = glfwGetTime();
//user define function

void Create() {
	srand(time(NULL));

	window.CreateGameWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, WINDOW_FULLSCREEN_ON);

	shader.ShaderInit();
	shader.ProcessShaderFile("FragmentShader.glsl", GL_FRAGMENT_SHADER);
	shader.ProcessShaderFile("VertexShader.glsl", GL_VERTEX_SHADER);

	mainMenu.InitSprite();

	coreGame.InitSprite();

	spawnPickups.InitPickupSprite();

	gameOver.InitSprite();
	
	gameplayTimer.SetTimer(300);

	//Transparent Blend
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CoreGameFunc() {
	gameplayTimer.RunTimer();

	coreGame.RenderBackground(shader);
	coreGame.UpdateGameplay(window, shader);

	if (coreGame.GetPlayerLife() <= 2) {
		spawnPickups.LifePickupMovement();
		spawnPickups.RenderLifePickups(shader);
	}

	if (gameplayTimer.GetTimer() % 35 == 0) {
		spawnPickups.TimeBoostPickupMovement();
		spawnPickups.RenderTimeBoostPickups(shader);
	}

	if (coreGame.GetGreenTargetCount() > coreGame.GetCapacity() / 2) {
		spawnPickups.ClearTargetsPickupMovement();
		spawnPickups.RenderClearTargetsPickups(shader);
	}
	else {
		spawnPickups.ResetClearTargetsPickup();
	}

	if (coreGame.GetClearBool() == true) {
		spawnPickups.ResetClearTargetsPickup();
		coreGame.SetClearBool() = false;
	}

	coreGame.ShootLifePickups(window, shader, spawnPickups.getLifePickup());
	coreGame.ShootTimeBoostPickups(window, shader, spawnPickups.getTimeBoostPickup());
	coreGame.ShootClearTargetsPickups(window, shader, spawnPickups.getClearTargetsPickup());

	if (coreGame.GetTimerBool()) {
		if (gameplayTimer.GetTimer() + 20 >= gameplayTimer.GetMaxTimeLimit()) {

			gameplayTimer.SetCurrentTime() = 300;
		}
		else {
			gameplayTimer.SetCurrentTime() += 20;
		}
		cout << "Adding Timer: " << gameplayTimer.GetTimer() << endl;
		coreGame.SetTimerBool() = false;
	}

	coreGame.RenderPlayer(shader);
}

void MainMenuFunc() {
	mainMenu.CursorMovement(window);

	mainMenu.ShootButton(window);

	mainMenu.RenderSprite(shader);
}

void GameOverFunc() {
	gameOver.CursorMovement(window);

	gameOver.ShootButton(window);

	gameOver.RenderSprite(shader);
}

void Render() {
	window.SetBGColor(0, 0, 0, 0);
	switch (gameState)
	{
	case GameState::START:
		if (mainMenu.GetButtonIndex() == 0 && mainMenu.GetBool() == true) {
			CoreGameFunc();
			gameState = GameState::PLAY;
			coreGame.Reset();
			mainMenu.SetBool(false);
		}
		else {
			MainMenuFunc();
		}
		break;
	case GameState::PLAY:
		if (coreGame.GetPlayerLife() <= 0) {
			gameState = GameState::START;
		}
		else {
			CoreGameFunc();
		}
		break;
	case GameState::END:
		if (gameOver.GetButtonIndex() == 0 && gameOver.GetBool() == true) {
			gameState = GameState::START;
			gameOver.SetBool(false);
		}
		else {
			GameOverFunc();
		}
		break;
	}

	shader.ApplyShader();

	camera.Update(window, shader);

	window.UpdateWindow();
}
//main function
int main() {

	//Do stuff

	
	Create();
	do {
		Render();
		//while (glfwGetTime() < lasttime + 1.0 / 144) {
		//	// TODO: Put the thread to sleep, yield, or simply do nothing
		//}
		//lasttime += 1.0 / 144;
	} while (window.IsWindowNotClosed());

	return 0;
}