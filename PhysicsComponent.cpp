#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "GameObject.h"

extern PhysicsSystem* PHYSICS_SYS;

PhysicsComponent::PhysicsComponent(GameObject* parent, PhysicsType _type, const std::string& _objectName) 
	: IComponent(parent), objectName(_objectName) {
	type = _type;
	registerComponent();
	if (XMVectorGetX(parent->getScale()) == 0.1) {
		this->size = XMFLOAT2{ 0.05f, 0.05f };
	}
	if (parent->getTranslateY() == 1.5) {
		this->size = XMFLOAT2{ 0.25f, 0.25f };
	}
}

void PhysicsComponent::registerComponent() {
	if (PHYSICS_SYS != nullptr) {
		PHYSICS_SYS->addPhysicsComponent(this);
	}
}

const std::string& PhysicsComponent::getName() {
	return "PhysicsComponent";
}

const std::string& PhysicsComponent::getObjectName() {
	return objectName;
}

PhysicsComponent::PhysicsType PhysicsComponent::getType() {
	return type;
}

bool PhysicsComponent::getFixedRotation() {
	return fixedRotation;
}
