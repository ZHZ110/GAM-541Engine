#pragma once
#include "pch.h"
#include <string>
using namespace DirectX;

enum PhysicsType {
	STATIC = 0,
	DYNAMIC = 1
};

class PhysicsEntity {
public:
	PhysicsEntity(PhysicsType _type, XMVECTOR _position)
		:type(_type), position(_position) {}
	PhysicsType type;
	XMVECTOR position;
	bool isCollided = false;
	bool active = true;
	GameObject* parent;
	virtual void move(XMVECTOR offset) {}
	virtual const std::string& getColliderName() { return ""; }
};