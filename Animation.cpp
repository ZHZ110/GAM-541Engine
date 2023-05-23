#include "Animation.h"

Animation::Animation(GameObject* parent) : Sprite(parent) {
	setCurrFrame(0);
	frameDuration = 1.0f;
	frameDelay = frameDuration;
}

const std::string& Animation::getName() {
	return "animation";
}

void Animation::frameUpdate(float dt) {
	frameDelay -= dt;
	if (frameDelay < 0) {
		// move on to the next frame
		int currentFrame = getCurrFrame() + 1;
		setCurrFrame(currentFrame);
		if (currentFrame >= getTotalFrames()) {
			setCurrFrame(0);
		}
		frameDelay = frameDuration;
	}

}