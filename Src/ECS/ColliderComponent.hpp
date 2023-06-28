#pragma once

#include <string>
#include "SDL.h"
#include "Components.hpp"

class ColliderComponent : public Component {
public:

	SDL_Rect collider;
	std::string tag;	//When we detect the colision, if we want to know what we are coliding with

	TransformComponent* transform;

	ColliderComponent(std::string t) {
		tag = t;
	}

	ColliderComponent(std::string t, int xpos, int ypos, int size)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}

	void init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		//ame::colliders.push_back(this);

	}

	void update() override {
		if (tag != "wall")
		{
			collider.x = static_cast<int> (transform->position.x);
			collider.y = static_cast<int> (transform->position.y);
			collider.w = static_cast<int> (transform->width * transform->scale);
			collider.h = static_cast<int> (transform->height * transform->scale);
		}
	}
};