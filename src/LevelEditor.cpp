#include "LevelEditor.h"

//typedef short int SloozBerry; funny
void LevelEditor::PlaceObject() {
	
	Box* box = new Box();
	
	// okay so the issue is that we dont have a physics world initialized within the editor. so setboxposition crashes because it expects
	// to own a physicsbody object.
	PhysObject = new PhysicsObject();
	PhysObject->m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	box->SetPhysObject(this->PhysObject);
	box->SetKinematic(true);
	box->SetScale(50.0f);
	box->Spawn();
	
	//SloozBerry berry; funny
	
	this->m_pEntities.push_back(box);
	LOG("Placed object");
}

void LevelEditor::Clean() {
	for (auto* ent : this->m_pEntities) {
		if (ent) {
			delete ent;
			LOG("Deleted editor entity");
		}
	}
}

void LevelEditorContext::Update() {
	static int count = 0;
	static float move_pos = 0.0f;

	if (InputHandler::Get().IsClicked(MouseButton::LEFT)) {
		LOG("Pressed left");
	}
	for (auto* ent : m_Editor.GetEntities()) {
		ent->Update(0.1f);
	}

	if (count == 3) return;
	
	
	m_Editor.PlaceObject();

	
	m_Editor.GetEntities()[count];
	count++;
}

void LevelEditorContext::BuildCamera() {

}
