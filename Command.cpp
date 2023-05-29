#include "Command.h"
#include "GameObject.h"
#include "GameFactory.h"
#include "Renderer.h"

extern GameFactory* FACTORY;
extern Renderer* RENDERER;

void LeftCommand::execute(GameObject* GO) {
	float x = GO->getTranslateX();
	x -= 0.1f;
	GO->setTranslateX(x);
}

void UpCommand::execute(GameObject* GO) {
	float y = GO->getTranslateY();
	y += 0.1f;
	GO->setTranslateY(y);
}

void DownCommand::execute(GameObject* GO) {
	float y = GO->getTranslateY();
	y -= 0.1f;
	GO->setTranslateY(y);
}

void RightCommand::execute(GameObject* GO) {
	float x = GO->getTranslateX(); 
	x += 0.1f; 
	GO->setTranslateX(x);
}

void FireCommand::execute(GameObject* GO) {
	// need to spawn the bullet
	for (int i = 0; i < 10; ++i) {
		if (FACTORY->getGameObjectByIndex(2 + i) != nullptr
			&& FACTORY->getGameObjectByIndex(2 + i)->getRender() == false) {
			float y = GO->getTranslateY();
			y += 0.35;
			XMVECTOR bullet_pos = XMVectorSet(GO->getTranslateX(), y, 0, 0);
			FACTORY->getGameObjectByIndex(2 + i)->setTranslate(bullet_pos);
			FACTORY->getGameObjectByIndex(2 + i)->setRender(true);
			break;
		}
	}
}

void CameraZplusCommand::execute(GameObject* GO) {
	auto position = RENDERER->getCamera()->GetPosition();
	RENDERER->getCamera()->SetPosition(position.x, position.y, position.z + 0.05);
}

void CameraZminusCommand::execute(GameObject* GO) {
	auto position = RENDERER->getCamera()->GetPosition();
	RENDERER->getCamera()->SetPosition(position.x, position.y, position.z - 0.05);
}

void CameraYplusCommand::execute(GameObject* GO) {
	auto position = RENDERER->getCamera()->GetPosition();
	RENDERER->getCamera()->SetPosition(position.x, position.y + 0.05, position.z);
}

void CameraYminusCommand::execute(GameObject* GO) {
	auto position = RENDERER->getCamera()->GetPosition();
	RENDERER->getCamera()->SetPosition(position.x, position.y - 0.05, position.z);
}