#pragma once
#include <SDL.h>

class ColliderComponent;

class Collision {
public: 
	//Access Allign Binding Box (Méthode de collision que l'on va utiliser)
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};