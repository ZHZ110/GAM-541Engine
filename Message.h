#pragma once
#include "pch.h"
#include "ISystem.h"
namespace dx = DirectX;

enum MessageType {
	KEYBOARD_PRESS = 0,
	KEYBOARD_UP = 3,
	MOUSE_LEFT_CLICK = 1,
	MESSAGE_QUIT = 2,
	MOUSE_MOVE = 4,
	MOUSE_UP = 5,
	MOUSE_WHEEL = 6,
	MESSAGE_CHAR = 7,
	MOUSE_RIGHT_CLICK = 8,
	MOUSE_LEFT_UP = 9,
	MOUSE_RIGHT_UP = 10,
	CAMERA_STRAFE = 11,
	CAMERA_MOVE_FRONT_BACK = 12,
	CAMERA_LOOK_LEFT_RIGHT = 13,
	CHANGE_TRANSFORM = 14,
	COLLIDE = 15,
};


class Message 
{
public:
	Message() {};
	Message(MessageType msg) 
	{
		setType(msg);
	}
	MessageType getType () const{
		return msg_type;
	}
	void setType(MessageType msg) 
	{
		msg_type = msg;
	}
protected:
	MessageType msg_type;
};


class MessageQuit : public Message {
	public:
	MessageQuit()
	{
		msg_type = MessageType::MESSAGE_QUIT;
	};
};

class KeyboardPress : public Message {
public:
	KeyboardPress() {
		msg_type = MessageType::KEYBOARD_PRESS;
	};
	unsigned char key;
};

class KeyboardUp : public Message {
public:
	KeyboardUp() {
		msg_type = MessageType::KEYBOARD_UP;
	};
	unsigned char key;
};

class MouseLeftClick : public Message {
public:
	MouseLeftClick(float x, float y) 
	{
		msg_type = MessageType::MOUSE_LEFT_CLICK;
		posX = x;
		posY = y;
	}
	float posX;
	float posY;
};

class MouseRightClick : public Message {
public:
	MouseRightClick(float x, float y)
	{
		msg_type = MessageType::MOUSE_RIGHT_CLICK;
		posX = x;
		posY = y;
	}
	float posX;
	float posY;
};

class MouseMove:public Message {
public:
	MouseMove(float x, float y) {
		msg_type = MessageType::MOUSE_MOVE;
		posX = x;
		posY = y;
	}
	float posX;
	float posY;
};

class MouseLeftUp :public Message {
public:
	MouseLeftUp(float x, float y) {
		msg_type = MessageType::MOUSE_LEFT_UP;
		posX = x;
		posY = y;
	}
	float posX;
	float posY;
};

class MouseRightUp :public Message {
public:
	MouseRightUp(float x, float y) {
		msg_type = MessageType::MOUSE_RIGHT_UP;
		posX = x;
		posY = y;
	}
	float posX;
	float posY;
};

class MouseWheel :public Message {
public:
	MouseWheel(float x, float y) {
		msg_type = MessageType::MOUSE_WHEEL;
		posX = x;
		posY = y;
	}
	float posX;
	float posY;
	int UpOrDown; // up is 0, down is 1
};

class CameraStrafing :public Message {
public:
	CameraStrafing(float x, float y) {
		msg_type = MessageType::CAMERA_STRAFE;
		move_xy.x = x;
		move_xy.y = y;
	}
	dx::XMFLOAT2 move_xy;
};

class CameraMoveFrontBack : public Message {
public:
	CameraMoveFrontBack(float mouse_roll) {
		msg_type = MessageType::CAMERA_MOVE_FRONT_BACK;
		front_back_move = mouse_roll;
	}
	float front_back_move;
};

class ChangeTransform :public Message {
public:
	ChangeTransform(dx::XMVECTOR _addition) {
		msg_type = MessageType::CHANGE_TRANSFORM;
		 addition = _addition;
	}
	dx::XMVECTOR addition;
};

class ObjectCollide : public Message {
public:
	ObjectCollide(GameObject* obj_ptr1, GameObject* obj_ptr2) {
		msg_type = MessageType::COLLIDE;
		collide = true;
		obj1 = obj_ptr1;
		obj2 = obj_ptr2;
	}
	bool collide;
	GameObject* obj1;
	GameObject* obj2;
};


