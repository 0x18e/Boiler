#include "LevelEditor.h"

void LevelEditor::PlaceObject() {
	BaseEntity* ent = new BaseEntity();
	this->m_pEntities.push_back(ent);
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

	if (count == 3) return;
	
	
	m_Editor.PlaceObject();
	count++;
}

void LevelEditorContext::BuildCamera() {

}
