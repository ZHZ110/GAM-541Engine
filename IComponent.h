#pragma once
#include "pch.h"
#include <string>
class GameObject;

using namespace DirectX;

class IComponent {
public:
	IComponent(GameObject* go) { 
		parent = go; 
	}
	GameObject* getParent() { return parent; } // no need to rewrite
	virtual void registerComponent() = 0;
	virtual const std::string& getName() = 0;
private:
	GameObject* parent;
};