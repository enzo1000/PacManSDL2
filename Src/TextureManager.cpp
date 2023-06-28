#include "TextureManager.hpp"

//On déplace ce qu'il y avait dans l'initialisation de notre objet Game.cpp
//De cette manière, on pourra générer différents assets juste avec cette fonction
SDL_Texture* TextureManager::LoadTexture(const char* texture) {

	SDL_Surface* tempSurface = IMG_Load(texture);

	//On vient appliquer notre image sur notre SDL_Texture.
	//La player texture est utilisé dans le pipeline de rendu
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}