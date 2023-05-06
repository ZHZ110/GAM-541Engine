#include "GameEngine.h"
#include "GameTimer.h"
#include <iostream>
GameEngine* ENGINE = 0;

GameEngine::GameEngine() 
{
	ENGINE = this;
}

GameEngine::~GameEngine() 
{
	ENGINE = nullptr;
}

void GameEngine::AddSystem(ISystem* system) {
	m_systems.push_back(system);
}

void GameEngine::Initialize() {
	for (auto it = std::begin(m_systems); it != std::end(m_systems); ++it) {
		(*it)->Initialize();
	}
	gameRunning = true;
}

void GameEngine::GameLoop() {
	GameTimer* m_timer = new GameTimer();
	m_timer->Reset();
	m_timer->Tick();
	while (gameRunning) {
		for (auto it = std::begin(m_systems); it != std::end(m_systems); ++it) {
			(*it)->Update(m_timer->DeltaTime());
		}
		m_timer->Tick();
		//std::sleep(1.0f);
	}
}

void GameEngine::ShutDown() {
	for (auto it = std::begin(m_systems); it != std::end(m_systems); ++it) {
		(*it)->ShutDown();
	}
}

void GameEngine::BroadcastMessage(const Message* msg) {
	if (msg->getType() == MessageType::MESSAGE_QUIT) {
		gameRunning = false;
		return;
	}
	// loop through all the systems and call each of their getMessage() function
	for (auto it = std::begin(m_systems); it != std::end(m_systems); ++it) {
		(* it)->getMessage(msg);
	}
}