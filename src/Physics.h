#pragma once
#include "tools.h"
#include<vector>

class PhysicsObject {
public:
	void Init(glm::vec3 initial_position);
	glm::vec3& GetVelocity() { return this->m_Velocity; }
	glm::vec3& GetPosition() { return this->m_Position; }
	glm::vec3& GetAccel() { return this->m_Acceleration; }
private:
	glm::vec3 m_Position;
	glm::vec3 m_Velocity;
	glm::vec3 m_Acceleration;
};

class PhysicsWorld {
public:
	void Integrate();
	void AddObject(PhysicsObject& object);
private:
	std::vector<PhysicsObject*> m_Objects; // I refuse to use smart pointers for this.
};
