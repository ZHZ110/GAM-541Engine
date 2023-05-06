#pragma once
#include <vector>
#include "ISystem.h"
#include "Message.h"

class GameEngine {
public:
	GameEngine();
	~GameEngine();
	void AddSystem(ISystem * systems);
	void Initialize();
	void GameLoop();
	void ShutDown();
	void BroadcastMessage(const Message* msg); 
private:
	std::vector<ISystem*> m_systems;
	bool gameRunning = true;
};
