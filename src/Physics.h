#pragma once
#include "tools.h"
#include<vector>


struct PhysicsObject {
	glm::vec3 m_Position;
    glm::vec3 m_Transform;
    glm::vec3 m_PrevTransform;
	glm::vec3 m_Velocity;
	glm::vec3 m_Acceleration;
    bool m_isKinematic = false;
};

class PhysicsWorld {
public:
	void Integrate();
	void AddObject(PhysicsObject& object);
private:
	std::vector<PhysicsObject*> m_Objects; // I refuse to use smart pointers for this.
};
