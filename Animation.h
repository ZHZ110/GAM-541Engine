#pragma once
#include <string>
#include "Sprite.h"

class Animation : public Sprite {
public:
	Animation(GameObject* parent);
	const std::string& getName();
	void frameUpdate(float dt);
private:
	unsigned int frameIndex; // the current frame being displayed
	unsigned int frameCount; // the maximum number of frames in the sequence
	float frameDelay; // time remaining for the current frame
	float frameDuration; //  the amount of time to display each frame
};