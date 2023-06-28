#pragma once
#include "Game.hpp"

class Map {
public:
	Map();
	~Map();

	void LoadMap(int arr[23][21]);
	void DrawMap();

private:
	SDL_Rect src, dest;
	SDL_Texture* path;
	SDL_Texture* wall;
	SDL_Texture* level;

	int map[23][21];
};