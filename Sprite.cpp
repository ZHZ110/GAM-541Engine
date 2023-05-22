
#include "Sprite.h"
#include "Renderer.h"

extern Renderer* RENDERER;

Sprite::Sprite(GameObject* parent) : IComponent(parent) {
	registerComponent();
	currFrameIndex = 1;
}

void Sprite::registerComponent() {
	if (RENDERER != nullptr) {
		RENDERER->addSprite(this);
	}
}

const std::string& Sprite::getName() {
	return "sprite";
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
