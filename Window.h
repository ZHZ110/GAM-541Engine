#pragma once
#include <Windows.h>
#include "ISystem.h"

class Window : public ISystem {
public:
	Window(HINSTANCE instanceHandle, int show, float width, float height);
	void Initialize();
	void Update(float dt);
	void ShutDown();
	void getMessage(const Message* msg);
	HWND getHandle();
private:
	HWND m_handle;
	int show;
	float width;
	float height;
};