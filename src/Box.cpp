#include "Box.h"
#include "tools.h"

// TODO, make virtual constructor take argument for model and shader, and call that function with some init function in box.
void Box::Spawn() {
	LOG("Box spawn called");
    //this->m_PhysObject.Init(glm::vec3(0.0f, 0.0f, 5.0f));
	LOG("Spawned base entity");
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
}

void Box::Update(const float& dt) {
	LOG("Box update");
}
void Box::Destroy() {
	LOG("Box Destroy called");
}

