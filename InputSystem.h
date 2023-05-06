#pragma once
#include "ISystem.h"
#include "Message.h"
#include "Keyboard.h"
#include "Mouse.h"

class InputSystem : public ISystem{
public:
	void Initialize();
	void Update(float dt);
	void ShutDown();
	void getMessage(const Message* msg);

	bool KeyIsPressed(const unsigned char keycode);
	bool KeyIsTriggered(const unsigned char keycode);
protected:
	Keyboard keyboard;
	Mouse mouse;
};