#pragma once
#include "ISystem.h"
#include "GameObject.h"
#include "PlayerController.h"

class GameManagerSystem : public ISystem{

	enum GameState {
		loading,
		start,
		update,
		exit,
		unload
	};

public:
	void Initialize();
	void Update(float dt);
	void ShutDown();
	void getMessage(const Message* msg);

private:
	//GameObject* player;
	GameState currentGameState;
	GameState nextGameState;
	GameObject* player1;
	PlayerController* playerController;
	GameObject* player2;
	//GameObject* player3;
	//std::vector<GameObject*> bullets;
};