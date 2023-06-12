
#include "Sprite.h"
#include "Renderer.h"

extern Renderer* RENDERER;

Sprite::Sprite(GameObject* parent) : IComponent(parent) {
	registerComponent();
	componentName = "sprite";
}

void Sprite::registerComponent() {
	if (RENDERER != nullptr) {
		RENDERER->addSprite(this);
	}
}

const std::string& Sprite::getName() {
	return componentName;
}

Texture* Sprite::getSpriteSource() {
	return spriteSource;
}

void Sprite::setSpriteSource(Texture* source) {
	spriteSource = source;
}

void Sprite::setRows(int nRows) {
	numRows = nRows;
}

void Sprite::setCols(int nCols) {
	numCols = nCols;
}

int Sprite::getRows() {
	return numRows;
}

int Sprite::getCols() {
	return numCols;
}

int Sprite::getTotalFrames() {
	return totalFrames;
}

void Sprite::setTotalFrames(int frameCount) {
	totalFrames = frameCount;
}

int Sprite::getCurrFrame() {
	return currFrame;
}

void Sprite::setCurrFrame(int currentFrame) {
	currFrame = currentFrame;
}