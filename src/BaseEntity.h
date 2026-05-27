#pragma once
#include "tools.h"
#include "Model.h"
#include "ResourceHandler.h"
#include "Physics.h"

struct Transform {
	glm::vec3 pos{ 0.0f };
	glm::vec3 rot{ 0.0f };
	glm::vec3 scale{ 1.0f };
};
class BaseEntity {
public:
	virtual void Spawn();
	//TODO add pre and post think functions
	virtual void Update(const float& dt);
	virtual void Destroy();
	virtual void Draw(glm::mat4 projection, glm::mat4 view);
	virtual void SetTransformPos(const glm::vec3& new_position);
	virtual void SetScale(const float& new_scale) { this->m_Transform.scale = glm::vec3(new_scale); }
	virtual void SetKinematic(const bool& val) { this->m_PhysObject->m_isKinematic = val; }
protected:
	// Other member variables come and go
	
	Model* m_pModel;
	glm::mat4 m_ModelData;
	Shader* m_pShader;
	Transform m_Transform;
	//PhysicsObject* m_PhysObject; // make every object have a physicscomponent
	PhysicsObject* m_PhysObject = nullptr;
	// Notes
	/*
	Going through the design of this base entity and using it, ive realized that I'd really like to have a base transform.
	An indication of their position, scale etc. I'd rather apply it directly to every entity
	rather than separate every entity's individual parts, I believe physics components can exist separately though.
	*/
};
