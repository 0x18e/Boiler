#pragma once
#include "BaseEntity.h"
#include "WindowHandler.h"
#include <vector>

#include "tools.h"
class Renderer {
private:
	float m_fAspectRatio;
	float m_iFar, m_iNear;
	int m_iFov;
	glm::mat4 m_ProjectionMatrix;
	bool m_bDebugMode;
public:
	void Render(const std::vector<BaseEntity*> &entities, const glm::mat4 &viewMatrix);
	bool Init();
	void SetDebugMode(const bool& val);
};

