#pragma once
#include "BaseEntity.h"
class Pistol : public BaseEntity {

	// basic stand still shoot straight. not hitscan, or wont be for now.
public:
	void Spawn() override;
	void SetPhysObject(PhysicsObject* pObject) { this->m_PhysObject = pObject; }
	void AdjustPistol(const glm::vec3& forward, const glm::vec3& player_position) {
		glm::vec3 fin = player_position + (forward * 5.0f);
		this->m_PhysObject->m_Position = fin;
	}
};