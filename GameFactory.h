#pragma once
#include "ISystem.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
using namespace DirectX;

class GameFactory : public ISystem {
public:
	void Initialize();
	void Update(float dt);
	void ShutDown();
	void getMessage(const Message* msg);

	GameObject* getGameObjectByIndex(int index);
	GameObject* CreateGameObject(XMVECTOR translation, float scaling, const std::string& name, PhysicsComponent::PhysicsType _type);
private:
	std::vector<GameObject*>  gameObjects;
	std::vector<GameObject*>  gameObjectsForDeletion;
};