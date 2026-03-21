#pragma once
#include "Physics.h"
#include "BaseEntity.h"

class Box : public BaseEntity {
	private:
		PhysicsObject m_PhysObject;
	public:	
	void Spawn() override;
	void Update(const float& dt) override;
	void Destroy() override;
	PhysicsObject& GetPhysicsObject() { return this->m_PhysObject; }
};
