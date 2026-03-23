#pragma once
#include "Physics.h"
#include "BaseEntity.h"

class Box : public BaseEntity {
	private:
		PhysicsObject* m_PhysObject = nullptr;
	public:	
	void Spawn() override;
	void SetPhysObject(PhysicsObject* pObject);
	void Update(const float& dt) override;
	void Destroy() override;
	void SetBoxPos(glm::vec3 forward, glm::vec3 player_pos) {
		
		glm::vec3 fin = player_pos + (forward * 5.0f);
		this->m_PhysObject->m_Position = fin;
	}
};
