#include "Physics.h"

// PhysicsObject
/*
void PhysicsObject::Init(glm::vec3 initial_position) {
	this->m_Acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_Position = initial_position;
	this->m_Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}
*/
PhysicsObject* PhysicsEngine::AddObject(const glm::vec3& position) {
	m_Objects.push_back(std::make_unique<PhysicsObject>());
	return m_Objects.back().get();
}

// PhysicsWorld
void PhysicsEngine::Integrate(const float& dt) {
	for (auto& object : this->m_Objects) {
        if (object->m_isKinematic){
            continue;
        }
		this->ApplyGravity(*object);
		this->CheckBounds(*object);
		//LOG(object->m_Velocity.y);
		object->m_Velocity += object->m_Acceleration * dt;
		object->m_Position += object->m_Velocity * dt;
	}
}
void PhysicsEngine::CheckBounds(PhysicsObject& object) {
	if (object.m_Position.y <= 0.0f) {
		object.m_Position.y = 0.0f;
		object.m_Acceleration.y = 0.0f;
		object.m_Velocity.y = 0.0f;
	}
}
void PhysicsEngine::ApplyGravity(PhysicsObject &object) {
	object.m_Acceleration.y = -9.81;
	//object.m_Velocity.y -= 0.98;
}
void PhysicsEngine::Clean() {
	m_Objects.clear();
}


