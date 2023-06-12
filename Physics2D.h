#pragma once
#include "CircleCollider.h"
#include "BoxCollider.h"
#include <vector>


class Physics2D {
public:
	Physics2D() {}
	std::vector<PhysicsEntity*> physics_entities;
	std::pair<GameObject*, GameObject*> collision_pair;
	bool CollisionDetection();
private:
	bool box_circle_collision(BoxCollider* box, CircleCollider* circle);
	bool box_box_collision(BoxCollider* box1, BoxCollider* box2);
	bool circle_circle_collision(CircleCollider* circle1, CircleCollider* circle2);
};
