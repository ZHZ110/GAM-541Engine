#pragma once
#include "PhysicsEntity.h"
#include <string>

class CircleCollider : public PhysicsEntity {
public:
	CircleCollider(PhysicsType _type, XMVECTOR _pos, float rad);
	float getRadius();
	void setRadius(float rad);
	void move(XMVECTOR offset) override;
	static bool isCollided(CircleCollider* colA, CircleCollider* colB);
	const std::string& getColliderName();
private:
	float radius;
	std::string colliderName;
};