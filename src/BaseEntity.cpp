#include "BaseEntity.h"
#include <GLFW/glfw3.h>

void BaseEntity::Spawn() {
	LOG("Spawned base entity");
	// Give base entity a default model
	this->m_pModel = ResourceHandler::Get().GetModel("obj_debug");
	if (this->m_pModel == nullptr) {
		LOG("Failed to get model for base entity");
	}
	// For now give every entity their base shader, and render them as such.
	this->m_pShader = ResourceHandler::Get().GetShader("base_shader");
	if (this->m_pShader == nullptr) {
		LOG("Failed to get shader for base entity");
	}
	this->m_ModelData = glm::mat4(1.0f);
}

void BaseEntity::Draw(glm::mat4 projection, glm::mat4 view) {
	this->m_pShader->use();
	this->m_pShader->SetMat4("model", this->m_ModelData);
	this->m_pShader->SetMat4("projection", projection);
	this->m_pShader->SetMat4("view", view);

	this->m_pModel->Draw(*this->m_pShader);
}

void BaseEntity::Update(const float& dt) {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	this->m_ModelData = model;
}

void BaseEntity::Destroy() {
	LOG("Base entity destroyed");
}
