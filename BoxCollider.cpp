#include "BoxCollider.h"

BoxCollider::BoxCollider(PhysicsType _type, XMVECTOR _position, float _half_length) :
	PhysicsEntity(_type, _position) {
	colliderName = "box collider";
	half_length = _half_length;
}

void BoxCollider::move(XMVECTOR offset) {
	position += offset;
}

const std::string& BoxCollider::getColliderName() {
	return colliderName;
}

float BoxCollider::getHalfLength() {
	return half_length;
}

bool BoxCollider::isCollided(BoxCollider* boxA, BoxCollider* boxB) {
	float x_distance = abs(XMVectorGetX(boxA->position - boxB->position));
	float y_distance = abs(XMVectorGetY(boxA->position - boxB->position));
	if (x_distance < boxA->getHalfLength() + boxB->getHalfLength()
		|| y_distance < boxA->getHalfLength() + boxB->getHalfLength()) {
		return true;
	}
	return false;
}