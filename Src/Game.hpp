#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;

class Game
{
public :
	Game();		//Constructor
	~Game();	//DeConstructor

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }//To know if the game is running
	void render();
	void clean();

	static SDL_Renderer* renderer;

private :
	int cnt = 0;			//Counter for Frame per Seconds
	bool isRunning = false;
	SDL_Window* window;
};

