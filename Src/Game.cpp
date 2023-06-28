#include "Game.hpp"
#include "TextureManager.hpp"	//Pour afficher des sprites 2D
#include "GameObject.hpp"		//Pour les différents objets en jeux
#include "Map.hpp"
#include "./ECS/Components.hpp"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;

auto& player(manager.addEntity());

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;	//1
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //Red, Green, Blue, Transparancy (0 = invisible)
		}
		isRunning = true;
	}

	map = new Map();

	player.addComponent<PositionComponent>(0, 0);
	player.addComponent<SpriteComponent>("assets/player.png");
}

void Game::handleEvents() {

	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

//Like in Unity
void Game::update() {
	manager.refresh();
	manager.update();

	if (player.getComponent<PositionComponent>().x() > 100)
	{
		player.getComponent<SpriteComponent>().setTex("assets/enemy.png");
	}

	//map->LoadMap(array);   If we had an external map file
}

//Render pipeline
void Game::render() {
	SDL_RenderClear(renderer);

	map->DrawMap();		//We draw our map behind player / other entities
	manager.draw();

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}