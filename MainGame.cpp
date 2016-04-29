#include "MainGame.h"
#include <iostream>
#include <string>


//error checking
//move this to error file
void fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to quit..";
	int temp;
	std::cin >> temp;
	SDL_Quit();
}

MainGame::MainGame()
{
	_window = nullptr;
	_screenWidth = 1024;
	_screenHeight = 768;
	_gameState = GameState::PLAY;
}


MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems();

	_sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);

	gameLoop();
	
}

void MainGame::initSystems()
{
	//Initalize SDL
	SDL_Init(SDL_INIT_EVERYTHING);



	//Creates game window*
	_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (_window == nullptr) {
		fatalError("SDL window could not be created!");
	}


	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		fatalError("SDL_GL Context could not be created!");
	}

	//handles extentions
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Could not initialize glew!");
	}


	//Tells SDL to double buffer, one window drawn and one window cleared
	//helps with screen flicker, double buffer might be on by default
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	//sets clear color
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}
//Process input with SDL
void MainGame::processInput()
{
	SDL_Event evnt;

	//SDL function that takes in a event.
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT :
			//gamewindow can be closed with exit button on window
			_gameState = GameState::EXIT;
			break;

			//screen checks for mouse movement
		case SDL_MOUSEMOTION:
			//print out mouse position to console
			std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;
		}
	}
}
//draws game using OpenGL
void MainGame::drawGame() 
{
	//tells gl what depth to clear to
	glClearDepth(1.0);

	/* glClear to clear game screen
	** single | is bitwise operator for OR */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_sprite.draw();

	//swap buffer and draw to screen
	SDL_GL_SwapWindow(_window);
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT) {
		processInput();
		drawGame();
	}
}
