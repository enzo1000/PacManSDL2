#pragma once

#include "../Game.hpp"
#include "ECS.hpp"
#include "Components.hpp"

class KeyboardController : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		//When a key is pressed
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_z:
			case SDLK_UP:
				transform->velocity.x = 0;
				transform->velocity.y = -1;
				sprite->Play("Walk");
				break;

			case SDLK_q:
			case SDLK_LEFT:
				transform->velocity.x = -1;
				transform->velocity.y = 0;
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;

			case SDLK_s:
			case SDLK_DOWN:
				transform->velocity.x = 0;
				transform->velocity.y = 1;
				sprite->Play("Walk");
				break;

			case SDLK_d:
			case SDLK_RIGHT:
				transform->velocity.x = 1;
				transform->velocity.y = 0;
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;

			default:
				break;
			}
		}
	}
};