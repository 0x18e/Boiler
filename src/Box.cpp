#include "Box.h"
#include "tools.h"

// TODO, make virtual constructor take argument for model and shader, and call that function with some init function in box.
void Box::Spawn() {
	// Give base entity a default model
	this->m_pModel = ResourceHandler::Get().GetModel("obj_crate");
	if (this->m_pModel == nullptr) {
		LOG("Failed to get model for obj_crate");
	}
	// For now give every entity their base shader, and render them as such.
	this->m_pShader = ResourceHandler::Get().GetShader("base_shader");
	if (this->m_pShader == nullptr) {
		LOG("Failed to get shader for obj_crate");
	}
	this->m_ModelData = glm::mat4(1.0f);
	this->m_PhysObject->m_Position = glm::vec3(0.0f);
	this->m_Transform.pos = m_PhysObject->m_Position;
	this->m_PhysObject->m_Acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_PhysObject->m_Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_PhysObject->m_isKinematic = false;
}

void Box::Update(const float& dt) {
	glm::mat4 model = glm::mat4(1.0f);

	this->m_Transform.pos = this->m_PhysObject->m_Position;
	model = glm::translate(model, this->m_Transform.pos); // position at origin
	model = glm::scale(model, this->m_Transform.scale);
	//model = glm::scale(model, glm::vec3(m_fScale, m_fScale, m_fScale)); // scale down the skull
	//m_fAngle = (float)glfwGetTime() * glm::radians(m_fRotationSpeed);
	// skull is spawned looking downwards, so rotate it to face forward
	//model = glm::rotate(model, m_fAngle, glm::vec3(0.0f, 1.0f, 0.0f)); // rotate around Y-axis
	//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // rotate to face forward
	this->m_ModelData = model;
}
void Box::SetPhysObject(PhysicsObject* pObject) {
	this->m_PhysObject = pObject;
}
void Box::Destroy() { 
	
	if (this->m_PhysObject) {
		m_PhysObject = nullptr;
	}
}

void Box::SetTransformPos(const glm::vec3& new_position) {
	this->m_PhysObject->m_Position = new_position;
}

