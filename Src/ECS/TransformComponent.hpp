#pragma once

#include "Components.hpp"
#include "Vector2D.hpp"

struct TransformComponent : public Component {

	Vector2D position;
	Vector2D velocity;

	//64 is the dimensions of Pac-Man in SpriteComponent.hpp scaled down to 40
	int height = 16;
	int width = 16;
	float scale = 2.5;

	int speed = 3;

	TransformComponent() {
		position.Zero();
	}

	TransformComponent(float sc) {
		position.Zero();
		scale = sc;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, float sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override {
		velocity.Zero();
	}

	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};