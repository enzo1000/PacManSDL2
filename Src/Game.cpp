#include "Game.hpp"
#include "TextureManager.hpp"	//Pour afficher des sprites 2D
#include "GameObject.hpp"		//Pour les différents objets en jeux
#include "Map.hpp"
#include "./ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

Map* gameMap;
Manager manager;

SDL_Texture* level;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

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

	level = TextureManager::LoadTexture("assets/level.png");
	gameMap = new Map();

	gameMap->LoadMap("assets/p23x21.map", 21, 23);

	player.addComponent<TransformComponent>(308, 525);
	player.addComponent<SpriteComponent>("assets/atlas.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& ghosts(manager.getGroup(Game:: groupGhosts));

void Game::handleEvents() {
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

	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	manager.refresh();
	manager.update();

	for (auto c : tiles) {
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol)) {
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	//map->LoadMap(array);   If we had an external map file
}

//Render pipeline
void Game::render() {
	SDL_RenderClear(renderer);

	for (auto& t : tiles) {
		t->draw();
	}
	for (auto& p : players) {
		p->draw();
	}
	for (auto& g : ghosts) {
		g->draw();
	}
	TextureManager::Draw(level, SDL_Rect{ 0, 0, 651, 713 }, SDL_Rect{ 0, 0, 651, 713 }, SDL_FLIP_NONE);

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}