#include "CircleCollider.h"

CircleCollider::CircleCollider(PhysicsType _type, XMVECTOR _pos, float _rad) :
	PhysicsEntity(_type, _pos)
{
	colliderName = "circle collider";
	position = _pos;
	radius = _rad;
}

float CircleCollider::getRadius() {
	return radius;
}

void CircleCollider::setRadius(float rad) {
	radius = rad;
}

const std::string& CircleCollider::getColliderName() {
	return colliderName;
}

void CircleCollider::move(XMVECTOR offset) {
	position += offset;
}

bool CircleCollider::isCollided(CircleCollider* colA, CircleCollider* colB) {
	float distance = XMVectorGetX(XMVector3Length(colA->position - colB->position));
	if (distance > colA->getRadius() + colB->getRadius()) {
		return false;
	}
	else return true;
}