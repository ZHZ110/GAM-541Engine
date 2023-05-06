
#include "Sprite.h"
#include "Renderer.h"

extern Renderer* RENDERER;

Sprite::Sprite(GameObject* parent) : IComponent(parent) {
	registerComponent();
}

void Sprite::registerComponent() {
	if (RENDERER != nullptr) {
		RENDERER->addSprite(this);
	}
}

const std::string& Sprite::getName() {
	return "sprite";
}