#include "Game.hpp"
#include <SDL.h>

Game* game = nullptr;

int main(int argc, char* args[]) {

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;	//Delta time de Unity

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	//651 = 31pixel (tile) * 23 Row
	//672 = 31pixel (tile) * 21 collumn
	game->init("PacMan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 651, 713, false);

	//Tant que le jeu est en route, on actualise notre boucle / renderer / handlingEvents
	while (game->running()) {

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;	//How long it as been to go throught all the process

		if (frameDelay > frameTime) {				//On a un delay approx de 70 frame par secondes ???
			SDL_Delay(frameDelay - frameTime);
		}
	}

	//Si le jeu vient à être fermé, on clean tout
	game->clean();

	return 0;
}