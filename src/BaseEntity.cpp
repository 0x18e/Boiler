#include "BaseEntity.h"

void BaseEntity::Spawn() {
	LOG("Spawned base entity");
	// Give base entity a default model
	this->m_pModel = ResourceHandler::Get().GetModel("obj_debug");
	// For now give every entity their base shader, and render them as such.
	this->m_pShader = ResourceHandler::Get().GetShader("base_shader");
	this->m_ModelData = glm::mat4(1.0f);
}

void BaseEntity::Draw() {
	this->m_pShader->SetMat4("model", this->m_ModelData);
}
void BaseEntity::Update() {
	this->m_ModelData = glm::mat4(1.0f);
	this->m_ModelData = glm::translate(m_ModelData, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	this->m_ModelData = glm::scale(m_ModelData, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
	//this->m_ModelData = glm::rotate(model, (float)glfwGetTime() * glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

}

void BaseEntity::Destroy() {

}
