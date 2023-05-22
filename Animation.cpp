#include "Animation.h"

Animation::Animation(GameObject* parent) : Sprite(parent) {
	registerComponent();
	frameIndex = 1;
	frameDuration = 1.0f;
	frameDelay = frameDuration;
	if (getName() == "spaceship") {
		frameCount = 8;
	}
	else if (getName() == "enemy") {
		frameCount = 1;
	}
	else if (getName() == "bullet") {
		frameCount = 1;
	}
}

const std::string& Animation::getName() {
	return "animation";
}

void Animation::frameUpdate(float dt) {
	frameDelay -= dt;
	if (frameDelay < 0) {
		frameIndex++;
		if (frameIndex > frameCount) {
			frameIndex = 1;
			frameDelay = frameDuration;
		}
	}

}