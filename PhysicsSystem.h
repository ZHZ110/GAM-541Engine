#pragma once
#include "pch.h"
#include "Isystem.h"
#include <vector>
#include "PhysicsComponent.h"
using namespace std;
//namespace dx = DirectX;

class PhysicsSystem : public ISystem {
public:
	PhysicsSystem();
	void Initialize();
	void Update(float dt);
	void ShutDown();
	void getMessage(const Message* msg);
	void addPhysicsComponent(PhysicsComponent* body);
private:
	std::vector<PhysicsComponent*> physicsComponents;
	b2World* m_physics_world = nullptr;
	const int32_t velocityIterations = 6;
	const int32_t positionIterations = 2;
};