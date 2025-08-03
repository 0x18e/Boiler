#include "Physics.h"

// PhysicsObject
void PhysicsObject::Init(glm::vec3 initial_position) {
	this->m_Acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_Position = initial_position;
	this->m_Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

// PhysicsWorld
void PhysicsWorld::Integrate() {
	/*for (auto& object : this->m_Objects) {	  // temporary dt
		object.GetVelocity() += object.GetAccel() * (1.0f / 60.0f);
		object.GetPosition() += object.GetVelocity() * (1.0f / 60.0f);
	}*/
}


