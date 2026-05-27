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
    this->m_PhysicsBody.m_Position = glm::vec3(0.0f);
    this->m_PhysicsBody.m_Velocity = glm::vec3(1.0f);
    this->m_PhysicsBody.m_Acceleration = glm::vec3(0.0f);

    this->m_fMoveSpeed = 5.0f;
}

void Skull::Update(const float& dt) { 
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, this->m_PhysicsBody.m_Position); // position at origin
	model = glm::scale(model, glm::vec3(m_fScale, m_fScale, m_fScale)); // scale down the skull
	//m_fAngle = (float)glfwGetTime() * glm::radians(m_fRotationSpeed);
	// skull is spawned looking downwards, so rotate it to face forward
	model = glm::rotate(model, m_fAngle, glm::vec3(0.0f, 1.0f, 0.0f)); // rotate around Y-axis
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // rotate to face forward
	this->m_ModelData = model;
}

void Skull::Move(const glm::vec3& moveTo, const float& dt) {
    glm::vec3 final_pos = glm::vec3(1.0f);
    final_pos = moveTo - this->m_PhysicsBody.m_Position;
    this->m_fAngle = atan2(final_pos.x, final_pos.z);
    if (glm::length(final_pos) > 0.0000001){
        m_PhysicsBody.m_Velocity = glm::normalize(final_pos) * m_fMoveSpeed;
    }
    else{
        m_PhysicsBody.m_Velocity = glm::vec3(0.0f);
    }
    //glm::vec3 unit_vec = glm::normalize(final_pos);
    //LOG("unit_vec: " << unit_vec.x << " " << unit_vec.z);
    //this->m_PhysicsBody.m_Velocity = unit_vec * 100.0f;
    //LOG("m_Velocity: " << m_PhysicsBody.m_Velocity.x << " z: " << m_PhysicsBody.m_Velocity.z);
    this->m_PhysicsBody.m_Position += m_PhysicsBody.m_Velocity * dt;
    //LOG("m_Position: " << m_PhysicsBody.m_Position.x << " z: " << m_PhysicsBody.m_Position.z);
//    m_Position += m_Velocity * dt;
}

void Skull::Destroy() {
	LOG("Destroyed Skull entity");
}
