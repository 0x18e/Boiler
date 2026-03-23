#pragma once
#include "tools.h"
#include<vector>
#include<memory>


struct PhysicsObject {
	glm::vec3 m_Position;
    glm::vec3 m_Transform;
    glm::vec3 m_PrevTransform;
	glm::vec3 m_Velocity;
	glm::vec3 m_Acceleration;
    bool m_isKinematic = false;
};

class PhysicsEngine {
public:
	void Integrate(const float& dt);
	void ApplyGravity(PhysicsObject& object);
	PhysicsObject* AddObject(const glm::vec3 &pos);
	void Clean();
private:
	std::vector<std::unique_ptr<PhysicsObject>> m_Objects; // I refuse to use smart pointers for this.
};
