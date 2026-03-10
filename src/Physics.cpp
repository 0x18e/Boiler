#include "Physics.h"

// PhysicsObject
/*
void PhysicsObject::Init(glm::vec3 initial_position) {
	this->m_Acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_Position = initial_position;
	this->m_Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}
*/
void PhysicsWorld::AddObject(PhysicsObject& object) {
	this->m_Objects.push_back(&object);
}

// PhysicsWorld
void PhysicsWorld::Integrate() {
	for (auto& object : this->m_Objects) {	  // temporary dt
        if (object->m_isKinematic){
            continue;
        }
		//object.get()->GetVelocity() += object.get()->GetAccel() * (1.0f / 60.0f);
		//object.get()->GetPosition() += object.get()->GetVelocity() * (1.0f / 60.0f);
		object->m_Velocity += object->m_Acceleration * 0.1f;
		object->m_Position += object->m_Velocity * 0.1f;		
	}
}


