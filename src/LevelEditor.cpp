#include "LevelEditor.h"

//typedef short int SloozBerry; funny
void LevelEditor::PlaceObject(glm::vec3 position) {
	
	Box* box = new Box();
	
	// okay so the issue is that we dont have a physics world initialized within the editor. so setboxposition crashes because it expects
	// to own a physicsbody object.
	PhysObject = new PhysicsObject();
	PhysObject->m_Position = position;
	box->SetPhysObject(this->PhysObject);
	box->SetKinematic(true);
	box->SetScale(50.0f);
	box->Spawn(); // bug where spawn is called and it forces pos to be 0
	PhysObject->m_Position = position;
	
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
	
	static float move_pos = 0.0f;
	static int box_count = 0;	
	if (box_count >= 3 ) {}
	else {
		LOG("Placed " << box_count + 1 << " box(s)");
		this->m_Editor.PlaceObject(glm::vec3(0.0f, 0.0f, 0.0f));
		box_count++;
	}
	if (InputHandler::Get().IsPressed(GLFW_KEY_W)){
		move_pos += 0.1;
		LOG(move_pos);
	}
	if (InputHandler::Get().IsClicked(MouseButton::LEFT)) {
		LOG("Pressed left");
		glm::vec2 pos = InputHandler::Get().GetMousePosition();
		glm::vec2 adj = glm::vec2(WindowHandler::Get().GetWidth()/2,
		WindowHandler::Get().GetHeight()/2);
		glm::vec2 rel_pos = pos - adj;
		LOG(pos.x << ", y: " << pos.y);
		this->m_Editor.PlaceObject(glm::vec3(rel_pos.x, 0.0f, rel_pos.y));	
	}
	for (auto* ent : m_Editor.GetEntities()) {
		ent->Update(0.1f);
	}

}

void LevelEditorContext::BuildCamera() {

}
