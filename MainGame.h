#pragma once
#include "Sprite.h"
#include <GL/glew.h> //handles extensions for OpenGL
#include <SDL/SDL.h>

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();


private:
	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();


	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	Sprite _sprite;
};

