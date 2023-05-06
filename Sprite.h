#pragma once

#include <string>
#include "IComponent.h"

class Sprite : public IComponent {
public:
	Sprite(GameObject* parent);
	void registerComponent();
	const std::string& getName();
	std::string textureName;
};