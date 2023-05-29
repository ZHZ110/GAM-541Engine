#pragma once

class GameObject;
class Command {
public:
	virtual ~Command() {}
	virtual void execute(GameObject* GO) = 0;
};

class UpCommand : public Command {
public:
	void execute(GameObject* GO);
};

class DownCommand : public Command {
public:
	void execute(GameObject* GO);
};

class LeftCommand : public Command {
public:
	void execute(GameObject* GO);
};

class RightCommand : public Command {
public:
	void execute(GameObject* GO);
};

class FireCommand : public Command {
public:
	void execute(GameObject* GO);
};

class CameraZplusCommand : public Command {
public:
	void execute(GameObject* GO);
};

class CameraZminusCommand : public Command {
public:
	void execute(GameObject* GO);
};

class CameraYplusCommand : public Command {
public:
	void execute(GameObject* GO);
};

class CameraYminusCommand : public Command {
public:
	void execute(GameObject* GO);
};