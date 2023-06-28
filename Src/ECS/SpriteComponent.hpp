#pragma once

#include "Components.hpp"
#include "SDL.h"
#include "TextureManager.hpp"
#include "Animation.hpp"
#include <map>

class SpriteComponent : public Component {
private :
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;	//Delay between frames

public:

	int animIndex = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTex(path);
	}

	SpriteComponent(const char* path, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 3, 125);
		Animation walk = Animation(0, 3, 125);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		Play("Idle");

		setTex(path);
	}

	void setTex(const char* path) {
		//I don't know why, I can use TextureManager hear without including it
		texture = TextureManager::LoadTexture(path);
	}

	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}

	void init() override {

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override {

		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);

		destRect.w = static_cast<int>(transform->width * transform->scale);
		destRect.h = static_cast<int>(transform->width * transform->scale);
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void Play(const char* animName) {
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};