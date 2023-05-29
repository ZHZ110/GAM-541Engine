#pragma once
//#include "ISystem.h"
//#include "InputSystem.h"
//#include "GameManagerSystem.h"
//#include "Command.h"

class GameObject;

class IController {
public:
	//void Initialize();
	virtual void Update(float dt) = 0;
	//void ShutDown();
	//void getMessage(const Message* msg);

	void setActor(GameObject* GO);
	//void playController(GameObject* GO);
protected:
	GameObject* actor;
	//void HandleKeyPressed(const unsigned char keycode, Command* command);
	//void HandleKeyTriggered(const unsigned char keycode, Command* command);
	//std::vector<std::pair<const unsigned char, Command*>> key_command_map;
};