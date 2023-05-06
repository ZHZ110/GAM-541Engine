#pragma once
#include "pch.h"
#include "IComponent.h"

using namespace DirectX;

class PhysicsComponent : public IComponent {
public:
	enum PhysicsType {
		STATIC = 0,
		DYNAMIC = 1,
		KINEMATIC = 2
	};
	PhysicsComponent(GameObject* parent, PhysicsType _type);
	void registerComponent();
	const std::string& getName();
	PhysicsType getType();
	bool getFixedRotation();
	void* runtimeBody = nullptr; // storage for runtime
	void* runtimefixture = nullptr; // storage for runtime
	XMFLOAT2 offset = { 0.0f, 0.0f };
	XMFLOAT2 size = { 0.05f, 0.05f };
	XMVECTOR position;
	float density = 1.0f;
	float friction = 0.5f;
	float restitution = 0.0f;
	float restitution_threshold = 0.5f;
private:
	PhysicsType type;
	bool fixedRotation = false;
};  