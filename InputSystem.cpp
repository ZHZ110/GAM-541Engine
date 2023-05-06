#pragma once
#include "InputSystem.h"
#include "GameEngine.h"
#include <string>

InputSystem* INPUTSYS = 0;
extern GameEngine* ENGINE;

void InputSystem::Initialize() {
	INPUTSYS = this;
	keyboard = Keyboard();
	mouse = Mouse();
	keyboard.EnableAutoRepeatChars();
}

// Here after processing the message, broadcast the message
void InputSystem::Update(float dt) {
	while (!keyboard.CharBufferIsEmpty()) {
		unsigned char ch = keyboard.ReadChar();
		std::string outmsg = "Char:  ";
		outmsg += ch;
		outmsg += "\n";
		printf(outmsg.c_str());
	}
	/*while (!keyboard.KeyBufferIsEmpty()) {
		KeyboardEvent kbe = keyboard.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
		std::string outmsg = "";
		if (kbe.IsPress()) {
			outmsg += "Key press: ";
		}
		if (kbe.IsRelease()) {
			outmsg += "Key release: ";
		}
		outmsg += keycode;
		outmsg += "\n";
		printf(outmsg.c_str());
	}*/
	keyboard.update();
	while (!mouse.EventBufferIsEmpty()) {
		MouseEvent me = mouse.ReadEvent();
		std::string outmsg = "x: ";
		outmsg += std::to_string(me.GetPosX());
		outmsg += ", y: ";
		outmsg += std::to_string(me.GetPosY());
		outmsg += "\n";
		printf(outmsg.c_str());
		// here call the engine's broadcast message function so that renderer can get the message
		//CameraStrafing cameraStrafe = CameraStrafing(me.GetPosX(), me.GetPosY());
		//ENGINE->BroadcastMessage(&cameraStrafe); // this works
	}
	while (!mouse.EventBufferIsEmpty()) {
		MouseEvent me = mouse.ReadEvent();
		if (me.GetType() == MouseEvent::EventType::WheelUp) {
			printf("MouseWheelUp\n");
		}
		if (me.GetType() == MouseEvent::EventType::WheelDown) {
			printf("MouseWheelDown\n");
		}
	}

}

// more like get message(get message from the engine and process it)?
void InputSystem::getMessage(const Message* msg) {
	int x, y;
	unsigned char keycode, ch;
	switch (msg->getType()) {
	case MessageType::KEYBOARD_PRESS:
		keycode = reinterpret_cast<const KeyboardPress*>(msg)->key;
		//if (keyboard.IsKeysAutoRepeat()) {
			keyboard.OnKeyPressed(keycode);
		//}
		break;
	case MessageType::KEYBOARD_UP:
		keycode = reinterpret_cast<const KeyboardUp*>(msg)->key;
		keyboard.OnKeyReleased(keycode);
		break;
	case MessageType::MOUSE_LEFT_CLICK:
		x = reinterpret_cast<const MouseLeftClick*>(msg)->posX;
		y = reinterpret_cast<const MouseLeftClick*>(msg)->posY;
		mouse.OnLeftPressed(x, y);
		break;
	case MessageType::MOUSE_RIGHT_CLICK:
		x = reinterpret_cast<const MouseRightClick*>(msg)->posX;
		y = reinterpret_cast<const MouseRightClick*>(msg)->posY;
		mouse.OnRightPressed(x, y);
		break;
	case MessageType::MOUSE_LEFT_UP:
		x = reinterpret_cast<const MouseLeftUp*>(msg)->posX;
		y = reinterpret_cast<const MouseLeftUp*>(msg)->posY;
		mouse.OnLeftReleased(x, y);
		break;
	case MessageType::MOUSE_RIGHT_UP:
		x = reinterpret_cast<const MouseRightUp*>(msg)->posX;
		y = reinterpret_cast<const MouseLeftUp*>(msg)->posY;
		mouse.OnRightReleased(x, y);
		break;
	case MessageType::MOUSE_MOVE:
		x = reinterpret_cast<const MouseMove*>(msg)->posX;
		y = reinterpret_cast<const MouseMove*>(msg)->posY;
		mouse.OnMouseMove(x, y);
		break;
	case MessageType::MOUSE_WHEEL:
		x = reinterpret_cast<const MouseWheel*>(msg)->posX;
		y = reinterpret_cast<const MouseWheel*>(msg)->posY;
		if (reinterpret_cast<const MouseWheel*>(msg)->UpOrDown == 0) {
			mouse.OnWheelUp(x, y);
		}
		else if (reinterpret_cast<const MouseWheel*>(msg)->UpOrDown == 1) {
			mouse.OnWheelDown(x, y);
		}
		break;
	}
}

void InputSystem::ShutDown() {
	INPUTSYS = nullptr;
}

bool InputSystem::KeyIsPressed(const unsigned char keycode) {
	return keyboard.KeyIsPressed(keycode);
}

bool InputSystem::KeyIsTriggered(const unsigned char keycode) {
	return keyboard.IsKeyTriggered(keycode);
}