#pragma once
#include "PhysicsEntity.h"
#include <string>

class BoxCollider : public PhysicsEntity{
public:
	BoxCollider(PhysicsType _type, XMVECTOR _position, float _half_length);
	float getHalfLength();
	void move(XMVECTOR offset) override;
	static bool isCollided(BoxCollider* boxA, BoxCollider* boxB);
	const std::string& getColliderName();
private:
	float half_length;
	std::string colliderName;
};