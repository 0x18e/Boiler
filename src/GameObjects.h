#pragma once
#include "BaseEntity.h"
#include "GLFW/glfw3.h"
class Skull : public BaseEntity {
public:
	void Spawn() override;
	void Update() override;
	void Destroy() override;
	void AddSoul() { m_iSoulCount++; }
private:
	float m_fRotationSpeed;
	float m_fScale;
	int m_iSoulCount;
	// size of skull should be based on how many souls you have collected
	enum SkullSize {
		SMALL,	//0-100 souls
		MEDIUM, // 101-500 souls
		LARGE	// 501+ souls
	};
};