#include "GameFactory.h"
#include "Sprite.h"
#include "Animation.h"

GameFactory* FACTORY = 0;

void GameFactory::Initialize() {
	FACTORY = this;
	gameObjects.resize(1000);
}

void GameFactory::Update(float dt) {
	for (int index = 0; index < gameObjectsForDeletion.size(); ++index) {
		GameObject* go = gameObjectsForDeletion[index];
		for (int componentIndex = 0; componentIndex < go->components.size(); ++componentIndex) {
			delete go->components[componentIndex];
		}
		delete go;
	}
	gameObjectsForDeletion.resize(0);

	// go through each element
	std::vector<GameObject*>::iterator iter;
	for (iter = gameObjects.begin(); iter != gameObjects.end(); ++iter) {
		if (*iter == nullptr) {
			continue;
		}
		if ((*iter)->active == false) {
			gameObjectsForDeletion.push_back(*iter);
			(* iter) = nullptr;
		}
	}
}

void GameFactory::ShutDown() {
	FACTORY = NULL;
}

void GameFactory::getMessage(const Message* msg) {

}

// deal with game objects and its components
GameObject* GameFactory::CreateGameObject(XMVECTOR translation, float scaling, const std::string& name, PhysicsComponent::PhysicsType _type) {
	GameObject* GO = new GameObject(); // only set the scale
	GO->setTranslate(translation);
	//GO->setRotationZ(rotate_angle);
	GO->setScale(scaling);

	for (int index = 0; index < gameObjects.size(); ++index) {
		if (gameObjects[index] == nullptr) {
			gameObjects[index] = GO;
			break;
		}
	}
	Sprite* new_sprite = new Sprite((GO));
	Animation* new_animation = new Animation(GO);
	new_sprite->textureName = name;
	new_animation->textureName = name;
	GO->components.push_back(new_sprite);
	GO->components.push_back(new_animation);
	GO->components.push_back(new PhysicsComponent(GO,_type));
	return GO;
}