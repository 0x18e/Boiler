#include "tools.h"
#include "BaseEntity.h"

class LevelEditor {

	// open 3d context window and only listen to mouse clicks
private:
	std::vector<BaseEntity*> m_pEntities; // walls, and everything in between counts
public:
	void PlaceObject();
	void Clean();

};

class LevelEditorContext {
private:
	LevelEditor m_Editor;
public:
	void Update();
	void Clean() { m_Editor.Clean(); }
};