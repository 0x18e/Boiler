#pragma once
#include "BaseEntity.h"
#include "GLFW/glfw3.h"
#include "Physics.h"
class Skull : public BaseEntity {
public:
	void Spawn() override;
	void Update(const float& dt) override;
	void Destroy() override;
	void AddSoul() { m_iSoulCount++; }
    void Move(const glm::vec3& moveTo, const float& dt); // Move to this position. 

private:
	float m_fRotationSpeed;
    float m_fAngle;
	float m_fScale;
	int m_iSoulCount;
    float m_fMoveSpeed;
    PhysicsObject m_PhysicsBody; 
	// size of skull should be based on how many souls you have collected
	enum SkullSize {
		SMALL,	//0-100 souls
		MEDIUM, // 101-500 souls
		LARGE	// 501+ souls
	};
};
