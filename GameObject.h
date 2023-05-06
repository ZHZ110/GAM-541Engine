#pragma once
#include "pch.h"
#include "IComponent.h"
#include <vector>
#include <string>
using namespace std;
using namespace DirectX;

class GameObject {
public:
	IComponent* getComponent(const std::string& name);
	void MarkForDeletion();
	bool getActive();
	bool getRender();
	void setRender(bool isRendering);

	void setPosition(XMVECTOR position);
	float getTranslateX();
	float getTranslateY();
	XMVECTOR getTranslate();
	void setTranslateX(float x);
	void setTranslateY(float y);
	void setTranslate(XMVECTOR _translate);
	float getRotateZ();
	void setRotationZ(float rotate_z);
	XMVECTOR getScale();
	void setScale(float scaling);
private:
	GameObject();
	~GameObject();
	void addComponent(IComponent* component);
	std::vector<IComponent*> components; 
	XMVECTOR translate;
	float rotateZ;
	XMVECTOR scale = XMVectorSet(0.1, 0.1, 0.1, 1);
	bool active = true;
	bool render = true;

	friend class GameFactory;
};