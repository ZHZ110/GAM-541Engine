#include "pch.h"
#include "PhysicsSystem.h"
#include "GameEngine.h"
#include "GameObject.h"
#include "Message.h"
#include <iostream>

PhysicsSystem* PHYSICS_SYS = 0;
extern GameEngine* ENGINE;

static b2BodyType PhysicsTypeToBox2D(PhysicsComponent::PhysicsType physics_type) {
	switch (physics_type) {
	case PhysicsComponent::STATIC:    return b2_staticBody;
	case PhysicsComponent::DYNAMIC:   return b2_dynamicBody;
	case PhysicsComponent::KINEMATIC: return b2_kinematicBody;
	}
}

PhysicsSystem::PhysicsSystem() {
	PHYSICS_SYS = this;
}

void PhysicsSystem::Initialize() {
	// create box2D world
	m_physics_world = new b2World({0.0f, 0.0f});
	// go through each physics component and fill in the type,pos and angle for bodyDef
	for (int i = 0; i < physicsComponents.size(); ++i) {
		b2BodyDef bodyDef;
		bodyDef.type = PhysicsTypeToBox2D(physicsComponents[i]->getType());
		bodyDef.position.Set(physicsComponents[i]->getParent()->getTranslateX(), 
			physicsComponents[i]->getParent()->getTranslateY());
		bodyDef.angle = physicsComponents[i]->getParent()->getRotateZ();
		// create the body in the box2d world
		b2Body* body = m_physics_world->CreateBody(&bodyDef);
		body->SetFixedRotation(physicsComponents[i]->getFixedRotation());
		physicsComponents[i]->runtimeBody = body;
		// set the box collider
		b2PolygonShape boxShape;
		b2CircleShape circleShape;
		//circleShape.m_p = b2Vec2(physicsComponents[i].get)
		// use half width and half height
		boxShape.SetAsBox(physicsComponents[i]->size.x, physicsComponents[i]->size.y);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;
		fixtureDef.density = physicsComponents[i]->density;
		fixtureDef.friction = physicsComponents[i]->friction;
		fixtureDef.restitution = physicsComponents[i]->restitution;
		fixtureDef.restitutionThreshold = physicsComponents[i]->restitution_threshold;
		fixtureDef.obj_ptr = physicsComponents[i]->getParent();
		body->CreateFixture(&fixtureDef); //create the fixture
	}
}

void PhysicsSystem::Update(float dt) {
	// check if there's inactive components
	for (int i = 0; i < physicsComponents.size(); ++i) {
		if (physicsComponents[i] != NULL && !physicsComponents[i]->getParent()->getActive()) {
			physicsComponents[i] = nullptr;
		}
	}
	b2Body* body = (b2Body*)m_physics_world->GetBodyList();
	for (int i = 0; i < physicsComponents.size(); ++i) {
		if (physicsComponents[i] == NULL) {
			//m_physics_world->DestroyBody(body);
			break;
		}
		float posX = physicsComponents[i]->getParent()->getTranslateX();
		float posY = physicsComponents[i]->getParent()->getTranslateY();
		body->SetTransform(b2Vec2(posX, posY), 0.0f);
		//b2Transform position = body->GetTransform();
		bool isCollide = false;
		if (m_physics_world->GetContactManager().m_contactList != NULL) {
			isCollide = m_physics_world->GetContactManager().m_contactList->IsTouching();
			b2Fixture* b2f1 = m_physics_world->GetContactList()->GetFixtureA();
			b2Fixture* b2f2 = m_physics_world->GetContactList()->GetFixtureB();
			b2Fixture* b2fixture = body->GetFixtureList();
 			b2Contact* b2cont = m_physics_world->GetContactList();
			// send message
			if (isCollide ) {
				ObjectCollide collision_event = ObjectCollide(b2f1->obj_ptr, b2f2->obj_ptr);
				ENGINE->BroadcastMessage(&collision_event);
			}
		}
		body = body->GetNext();
	}
	m_physics_world->Step(0.0f, velocityIterations, positionIterations);
	// update the position in physics world
	//m_physics_world->Step(dt, velocityIterations, positionIterations);
	//b2Body* body = (b2Body*)m_physics_world->GetBodyList();
	// Retrieve transform from Box2D to set the value in my own physics component
	/*for (int i = 0; i < physicsComponents.size(); ++i) {
		const auto& position = body->GetPosition();
		physicsComponents[i]->getParent()->setTranslateX(position.x);
		physicsComponents[i]->getParent()->setTranslateY(position.y);
		physicsComponents[i]->getParent()->setRotationZ(body->GetAngle());
		body = body->GetNext();
	}*/
}

void PhysicsSystem::ShutDown() {
	// destroy box2D world
	delete m_physics_world;
	m_physics_world = nullptr;
	PHYSICS_SYS = nullptr;
}

void PhysicsSystem::getMessage(const Message* msg) {
	
}

void PhysicsSystem::addPhysicsComponent(PhysicsComponent* body) {
	for (int i = 0; i < physicsComponents.size(); ++i) {
		if (physicsComponents[i] == NULL) {
			physicsComponents[i] = body;
			return;
		}
	}
	physicsComponents.push_back(body);
}