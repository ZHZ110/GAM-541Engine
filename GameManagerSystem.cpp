#include "GameManagerSystem.h"
#include "GameEngine.h"
#include "GameFactory.h"
#include "Renderer.h"
#include "PhysicsComponent.h"

extern GameFactory* FACTORY;
extern GameEngine* ENGINE;
extern Renderer* RENDERER;

void GameManagerSystem::Initialize()
{
	player1 = FACTORY->CreateGameObject(XMVectorSet(0, -0.5, 0, 0), 0.3f, "spaceship", PhysicsComponent::DYNAMIC);
	player2 = FACTORY->CreateGameObject(XMVectorSet(0, 1.5, 0, 0), 0.3f, "enemy", PhysicsComponent::DYNAMIC);
	for (int i = 10; i < 20; ++i) {
		GameObject* new_bullet = FACTORY->CreateGameObject(XMVectorSet(60 * i, 60 * i, 0, 0), 0.1f, "bullet", PhysicsComponent::DYNAMIC);
		new_bullet->setRender(false);
	}
	RENDERER->LoadTextures();
	currentGameState = GameState::loading;
}

void GameManagerSystem::Update(float dt) 
{
	if (currentGameState == GameState::loading) {
		playerController = new PlayerController();
		playerController->HandleKeyPressed('A', new LeftCommand());
		playerController->HandleKeyPressed('D', new RightCommand());
		playerController->HandleKeyPressed('S', new DownCommand());
		playerController->HandleKeyPressed('W', new UpCommand());
		playerController->HandleKeyTriggered('A', new LeftCommand());
		playerController->HandleKeyTriggered('D', new RightCommand());
		playerController->HandleKeyTriggered('S', new DownCommand());
		playerController->HandleKeyTriggered('W', new UpCommand());
		playerController->HandleKeyPressed('N', new CameraZplusCommand());
		playerController->HandleKeyPressed('M', new CameraZminusCommand());
		playerController->HandleKeyPressed('X', new CameraYplusCommand());
		playerController->HandleKeyPressed('Z', new CameraYminusCommand());
		playerController->HandleKeyTriggered('N', new CameraZplusCommand());
		playerController->HandleKeyTriggered('M', new CameraZminusCommand());
		playerController->HandleKeyTriggered('X', new CameraYplusCommand());
		playerController->HandleKeyTriggered('Z', new CameraYminusCommand());
		playerController->HandleKeyPressed(' ', new FireCommand());
		nextGameState = GameState::start;
	}
	else if(currentGameState == GameState::start) {
		// update gameobject state
		// create player: create gameobject here
		playerController->setActor(player1);
		nextGameState = GameState::update;
	}
	else if (currentGameState == GameState::update) {
		playerController->Update(dt);

		for (int i = 0; i < 10; ++i) {
			if (FACTORY->getGameObjectByIndex(i + 2) != nullptr
				&& FACTORY->getGameObjectByIndex(i+2)->getRender() == true) {
				float y = FACTORY->getGameObjectByIndex(i + 2)->getTranslateY();
				y += 0.01f;
				FACTORY->getGameObjectByIndex(i + 2)->setTranslateY(y);
			}
		}
		// Do update rendering here

		if (currentGameState != nextGameState) {
			// Start exiting
		}
	}
	else if (currentGameState == GameState::exit) {
		// FACTORY->DeleteAllGameObjects();
	}
	currentGameState = nextGameState;
}

void GameManagerSystem::getMessage(const Message* msg) {
	switch (msg->getType()) {
	case MessageType::COLLIDE:
		//if(dynamic_cast<Sprite*>(player1->getComponent("sprite"))->textureName == "bullet")
		//if( obj1->name == "bullet"){ obj->MarkForDeletion() }
		// if(obj2->name == "asteroid") { obj2->MarkForDeletion() }
		GameObject* obj1 = reinterpret_cast<const ObjectCollide*>(msg)->obj1;
		GameObject* obj2 = reinterpret_cast<const ObjectCollide*>(msg)->obj2;
		/*if (obj1->name == "bullet" || obj2->name == "bullet")
		{
			auto bullet = obj1;
			auto other = obj2;
			if (obj1->name != "bullet") {
				bullet = obj2;
				other = obj1;
			}
			obj1->MarkForDeletion();
			obj2->MarkForDeletion();

		}*/
		/*if (dynamic_cast<Sprite*>(obj1->getComponent("sprite"))->textureName == "bullet") {
			obj1->MarkForDeletion();
		}
		if (dynamic_cast<Sprite*>(obj2->getComponent("sprite"))->textureName == "bullet") {
			obj2->MarkForDeletion();
		}*/
		if(FACTORY->getGameObjectByIndex(2) != nullptr)
			FACTORY->getGameObjectByIndex(2)->MarkForDeletion();
		if(FACTORY->getGameObjectByIndex(1) != nullptr) 
			FACTORY->getGameObjectByIndex(1)->MarkForDeletion();
		printf("Two objects collide!\n");
		break;
	}

}

void GameManagerSystem::ShutDown() {

}