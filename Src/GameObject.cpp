#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* texturesheet, int x, int y) {
	
	objTexture = TextureManager::LoadTexture(texturesheet);
	xpos = x;
	ypos = y;
}

//All the movement and behavior stuff
void GameObject::Update() {
	xpos++;
	ypos++;

	srcRect.h = 48;
	srcRect.w = 48;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}

//We are simplifying render pipeline and other stuff in a class to create 
// similar games objects
void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}