#pragma once
#include "Physics.h"
#include "BaseEntity.h"

class Box : public BaseEntity {
	private:
		PhysicsObject m_PhysObject; // what defines it as the object.
	public:	
	void Spawn() override;
	void Update() override;
	void Destroy() override;
	PhysicsObject& GetPhysicsObject() { return this->m_PhysObject; }
};
