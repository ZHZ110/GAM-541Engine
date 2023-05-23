#pragma once
#include <string>
#include "Sprite.h"

class Animation : public Sprite {
public:
	Animation(GameObject* parent);
	const std::string& getName();
	void frameUpdate(float dt);
private:
	float frameDelay; // time remaining for the current frame
	float frameDuration; //  the amount of time to display each frame
};