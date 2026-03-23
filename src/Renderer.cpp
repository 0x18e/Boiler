#include "Renderer.h"

bool Renderer::Init() {
	bool flag = true;

	this->m_ProjectionMatrix = glm::mat4(1.0f);
	this->m_fAspectRatio = (float)WindowHandler::Get().GetWidth() / WindowHandler::Get().GetHeight();
	this->m_iFar = 1000.0f;
	this->m_iNear = 0.1f;
	this->m_iFov = glm::radians(90.0f);

	return flag;
}

void Renderer::Render(const std::vector<BaseEntity*> &entities, const glm::mat4 &viewMatrix) {
	// Use players fov instead
	this->m_ProjectionMatrix = glm::perspective((float)this->m_iFov, this->m_fAspectRatio, this->m_iNear, this->m_iFar);
	for (auto* ent : entities) {
		ent->Draw(m_ProjectionMatrix, viewMatrix);
	}
}