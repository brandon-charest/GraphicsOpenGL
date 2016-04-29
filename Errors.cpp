#include "Errors.h"
#include <iostream>
#include <SDL/SDL.h>


//error checking
void fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to quit..";
	int temp;
	std::cin >> temp;
	SDL_Quit();
}