#pragma once

#include "ISystem.h"

class WindowsConsole : public ISystem {
public:
	void Initialize() {
		AllocConsole();
	}
	void Update(float dt) {}
	void ShutDown() {}
	void getMessage(const Message* msg) {}
};