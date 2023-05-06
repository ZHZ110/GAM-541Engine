#pragma once
#include "Message.h"

class ISystem
{
	public:
		virtual void Initialize() = 0;
		virtual void Update(float dt) {}
		virtual void ShutDown() = 0;
		virtual void getMessage(const Message* msg) = 0;
};