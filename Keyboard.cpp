#include "Keyboard.h"

Keyboard::Keyboard() {
	for (int i = 0; i < 256; ++i) {
		this->keyStates_now[i] = false;
		this->keyStates_prev[i] = false;
	}
}

bool Keyboard::KeyIsPressed(const unsigned char keycode) {
	return this->keyStates_now[keycode];
}

bool Keyboard::KeyBufferIsEmpty() {
	return this->keyBuffer.empty();
}

bool Keyboard::CharBufferIsEmpty() {
	return this->charBuffer.empty();
}

KeyboardEvent Keyboard::ReadKey() {
	if (this->keyBuffer.empty()) {
		return KeyboardEvent();
	}
	else {
		KeyboardEvent e = this->keyBuffer.front();
		this->keyBuffer.pop();
		return e;
	}
}

unsigned char Keyboard::ReadChar() {
	if (this->charBuffer.empty()) {
		return 0;
	}
	else {
		unsigned char e = this->charBuffer.front();
		this->charBuffer.pop();
		return e;
	}
}

void Keyboard::OnKeyPressed(const unsigned char key) {
	//keyStates_prev[key] = keyStates_now[key];
	this->keyStates_now[key] = true;
	//this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, key));
}

void Keyboard::OnKeyReleased(const unsigned char key) {
	//keyStates_prev[key] = keyStates_now[key];
	this->keyStates_now[key] = false;
	//this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, key));
}

bool Keyboard::update() {
	for (int i = 0; i < 256; ++i) {
		keyStates_prev[i] = keyStates_now[i];
	}
	return true;
}

void Keyboard::OnChar(const unsigned char key) {
	this->charBuffer.push(key);
}

void Keyboard::EnableAutoRepeatKeys()
{
	this->autoRepeatKeys = true;
}

void Keyboard::DisableAutoRepeatKeys() {
	this->autoRepeatKeys = false;
}

void Keyboard::EnableAutoRepeatChars() {
	this->autoRepeatChars = true;
}

void Keyboard::DisableAutoRepeatChars() {
	this->autoRepeatChars = false;
}

bool Keyboard::IsKeysAutoRepeat() {
	return this->autoRepeatKeys;
}

bool Keyboard::IsCharAutoRepeat() {
	return this->autoRepeatChars;
}

bool Keyboard::IsKeyTriggered(const unsigned char key) {
	if (this->keyStates_now[key] == true && this->keyStates_prev[key] == false) {
		printf("Triggered!\n");
		return true; // triggered
	}
	else {
		return false;
	}
}