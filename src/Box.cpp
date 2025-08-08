#include "Box.h"
#include "tools.h"

void Box::Spawn() {
	LOG("Box spawn called");
	this->m_PhysObject.Init(glm::vec3(0.0f, 0.0f, 5.0f));
}

void Box::Update() {
	LOG("Box update");
}
void Box::Destroy() {
	LOG("Box Destroy called");
}

