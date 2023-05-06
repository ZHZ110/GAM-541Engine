#include "pch.h"
#include "GameObject.h" 
using namespace DirectX;

// place where we can add multiple cubes(players)

GameObject::GameObject() {
	//scale = XMVectorSet(0.1, 0.1, 0.1, 1);
}

GameObject::~GameObject() {

}

void GameObject::MarkForDeletion() {
	active = false;
}

bool GameObject::getActive() {
	return active;
}

bool GameObject::getRender() {
	return render;
}
void GameObject::setRender(bool isRendering) {
	render = isRendering;
}

IComponent* GameObject::getComponent(const std::string& name) {
	for (int i = 0; i < components.size(); ++i) {
		int x = components.at(i)->getName().compare(name);
		if (x == 0) {
			return components[i];
		}
	}
	return nullptr;
}

void GameObject::addComponent(IComponent* component) {
	components.push_back(component);
}

float GameObject::getTranslateX() {
	return XMVectorGetX(translate);
}

float GameObject::getTranslateY() {
	return XMVectorGetY(translate);
}

XMVECTOR GameObject::getTranslate() {
	return translate;
}

float GameObject::getRotateZ() {
	return rotateZ;
}

void GameObject::setTranslateX(float x) {
	translate = XMVectorSetX(translate, x);
}

void GameObject::setTranslateY(float y) {
	translate = XMVectorSetY(translate, y);
}

void GameObject::setTranslate(XMVECTOR _translate) {
	translate = _translate;
}

void GameObject::setRotationZ(float rotate_z) {
	rotateZ = rotate_z;
}

XMVECTOR GameObject::getScale() {
	return scale;
}

void GameObject::setScale(float scaling) {
	scale = XMVectorSetX(scale, scaling);
	scale = XMVectorSetY(scale, scaling);
	scale = XMVectorSetZ(scale, scaling);
}