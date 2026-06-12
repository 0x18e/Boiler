#include "Weapons.h"

void Pistol::Spawn() {
	this->m_pModel = ResourceHandler::Get().GetModel("weapon_pistol");
	if (this->m_pModel == nullptr) {
		LOG("Failed to get model for weapon_pistol");
	}
	// For now give every entity their base shader, and render them as such.
	this->m_pShader = ResourceHandler::Get().GetShader("base_shader");
	if (this->m_pShader == nullptr) {
		LOG("Failed to get shader for weapon_pistol");
	}
	this->m_ModelData = glm::mat4(1.0f);

	this->m_Transform.pos = this->m_Transform.pos;

	//this->m_PhysObject->m_isKinematic = true;
}


