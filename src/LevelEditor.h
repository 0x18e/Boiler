#pragma once
#include "tools.h"
#include "BaseEntity.h"
#include "Camera.h"
#include "GameObjects.h"
#include "Box.h"

//Temp include
#include "Physics.h"

class LevelEditor {

	// open 3d context window and only listen to mouse clicks
private:
	std::vector<BaseEntity*> m_pEntities; // walls, and everything in between counts
public:
	void PlaceObject(glm::vec3 position);
	void Clean();
	std::vector<BaseEntity*>& GetEntities() { return this->m_pEntities; }
	PhysicsObject *PhysObject;
};

class LevelEditorContext {

private:
	LevelEditor m_Editor;
	Camera m_Camera;
	
public:
	void Update();
	void BuildCamera();
	void Clean() { m_Editor.Clean(); }
	std::vector<BaseEntity*>& GetEditorEntities() {
		return m_Editor.GetEntities();
	}


};
