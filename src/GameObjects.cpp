#include "GameObjects.h"

void Skull::Spawn() {
	LOG("Spawned Skull entity");
	this->m_pModel = ResourceHandler::Get().GetModel("obj_skull");	
	if (this->m_pModel == nullptr) {
		LOG("Failed to get model for Skull entity");
	}
	this->m_pShader = ResourceHandler::Get().GetShader("base_shader");
	if (this->m_pShader == nullptr) {
		LOG("Failed to get shader for Skull entity");
	}
	this->m_fRotationSpeed = 20.0f; // degrees per second
	this->m_fScale = 0.5f; // scale down the skull
	this->m_ModelData = glm::mat4(1.0f);
}

void Skull::Update() {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // position at origin
	model = glm::scale(model, glm::vec3(m_fScale, m_fScale, m_fScale)); // scale down the skull
	float angle = (float)glfwGetTime() * glm::radians(m_fRotationSpeed);
	// skull is spawned looking downwards, so rotate it to face forward
	model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f)); // rotate around Y-axis
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // rotate to face forward
	this->m_ModelData = model;
}

void Skull::Destroy() {
	LOG("Destroyed Skull entity");
}