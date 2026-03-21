#include "Physics.h"

// PhysicsObject
/*
void PhysicsObject::Init(glm::vec3 initial_position) {
	this->m_Acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_Position = initial_position;
	this->m_Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}
*/
void PhysicsEngine::AddObject(PhysicsObject& object) {
	this->m_Objects.push_back(&object);
}

// PhysicsWorld
void PhysicsEngine::Integrate(const float& dt) {
	for (auto& object : this->m_Objects) {
        if (object->m_isKinematic){
            continue;
        }
		object->m_Velocity += object->m_Acceleration * dt;
		object->m_Position += object->m_Velocity * dt;
	}
}
void PhysicsEngine::ApplyGravity(PhysicsObject &object) {
	object.m_Acceleration.y -= 0.98f;
}
void PhysicsEngine::Clean() {
	for (auto* obj : this->m_Objects) {
		if (obj) {
			LOG("Deleted physics object");
			delete obj;
		}
	}
}


