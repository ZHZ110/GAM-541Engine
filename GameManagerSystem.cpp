#include "GameManagerSystem.h"
#include "GameEngine.h"
#include "GameObject.h"
#include "GameFactory.h"
#include "InputSystem.h"
#include "Renderer.h"
#include "PhysicsComponent.h"

extern GameFactory* FACTORY;
extern InputSystem* INPUTSYS;
extern GameEngine* ENGINE;
extern Renderer* RENDERER;

void GameManagerSystem::Initialize()
{
	currentGameState = GameState::start;
	XMVECTOR position;
	player1 = FACTORY->CreateGameObject(XMVectorSet(0, -0.5, 0, 0), 0.3f, "spaceship", PhysicsComponent::DYNAMIC);
	player2 = FACTORY->CreateGameObject(XMVectorSet(0, 1.5, 0, 0),0.3f, "enemy", PhysicsComponent::DYNAMIC);
	//GameObject* new_bullet = FACTORY->CreateGameObject(XMVectorSet(0, 0.25, 0, 0), 0.1f, "bullet", PhysicsComponent::DYNAMIC);
	//new_bullet->setRender(false);
	for (int i = 10; i < 20; ++i) {
		GameObject* new_bullet = FACTORY->CreateGameObject(XMVectorSet(60*i, 60*i, 0, 0), 0.1f, "bullet", PhysicsComponent::DYNAMIC);
		new_bullet->setRender(false);
		bullets.push_back(new_bullet);
	}
	//player3 = FACTORY->CreateGameObject(XMVectorSet(0, -0.25, 0, 0), 0.1f, "bullet", PhysicsComponent::DYNAMIC);
	//player3->setRender(false);
	RENDERER->LoadTextures();
}

void GameManagerSystem::Update(float dt) 
{

	if (currentGameState == GameState::loading) {
		// GRAPHICS->LoadTextures("Level1Textures");
		nextGameState = GameState::start;
	}
	else if(currentGameState == GameState::start) {
		// update gameobject state
		//ChangeTransform changeTransform = ChangeTransform(player1->getTranslate());
		//ENGINE->BroadcastMessage(&changeTransform);
		nextGameState = GameState::update;
	}
	else if (currentGameState == GameState::update) {
		for (int i = 0; i < 10; ++i) {
			if (bullets.at(i)->getRender() == true) {
				float y = bullets.at(i)->getTranslateY();
				y += 0.01f;
				bullets.at(i)->setTranslateY(y);
			}
		}
		// do update rendering here
		if (INPUTSYS->KeyIsTriggered('A')) {
			// player1: x - 1;
			float x = player1->getTranslateX();
			x -= 0.1f;
			player1->setTranslateX(x);
		}
		else if (INPUTSYS->KeyIsPressed('W')) {
			// player1: y + 1;
			float y = player1->getTranslateY();
			y += 0.1f;
			player1->setTranslateY(y);
		}
		else if (INPUTSYS->KeyIsPressed('S')) {
			// player1: y - 1;
			float y = player1->getTranslateY();
			y -= 0.1f;
			player1->setTranslateY(y);
		}
		else if (INPUTSYS->KeyIsPressed('D')) {
			//player1: x + 1;
			float x = player1->getTranslateX();
			x += 0.1f;
			player1->setTranslateX(x);
		}
		else if (INPUTSYS->KeyIsPressed('J')) {
			// player2: x - 1;
			float x = player2->getTranslateX();
			x -= 0.1;
			player2->setTranslateX(x);
		}
		else if (INPUTSYS->KeyIsPressed('I')) {
			// player2: y + 1;
			float y = player2->getTranslateY();
			y += 0.1;
			player2->setTranslateY(y);
		}
		else if (INPUTSYS->KeyIsPressed('K')) {
			// player2: y - 1;
			float y = player2->getTranslateY();
			y -= 0.1;
			player2->setTranslateY(y);
		}
		else if (INPUTSYS->KeyIsPressed('L')) {
			// player2: x + 1;
			float x = player2->getTranslateX();
			x += 0.1;
			player2->setTranslateX(x);
		}
		if (INPUTSYS->KeyIsPressed('Z')) {
			RENDERER->getCamera()->Strafe(0.03f);
		}

		if (INPUTSYS->KeyIsPressed('M')) {
			RENDERER->getCamera()->Walk(0.1f);
		}

		if (INPUTSYS->KeyIsPressed('X')) {
			RENDERER->getCamera()->Strafe(-0.03f);
		}

		if (INPUTSYS->KeyIsPressed('N')) {
			RENDERER->getCamera()->Walk(-0.1f);
		}
		if (INPUTSYS->KeyIsTriggered(' ')) {
			// need to spawn something
			for (int i = 0; i < 10; ++i) {
				if (bullets.at(i)->getActive() == true && bullets.at(i)->getRender() == false) {
					float y = player1->getTranslateY();
					y += 0.35;
					XMVECTOR bullet_pos = XMVectorSet(player1->getTranslateX(), y, 0, 0);
					bullets.at(i)->setTranslate(bullet_pos);
					bullets.at(i)->setRender(true);
					break;
				}
			}
			nextGameState = GameState::loading;
		}
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
		bullets[0]->MarkForDeletion();
		player2->MarkForDeletion();
		printf("Two objects collide!\n");
		break;
	}

}

void GameManagerSystem::ShutDown() {

}