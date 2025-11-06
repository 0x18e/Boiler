#pragma once
#include "tools.h"
#include "Model.h"
#include "ResourceHandler.h"
class BaseEntity {
public:
	virtual void Spawn();
	//TODO add pre and post think functions
	virtual void Update();
	virtual void Destroy();
	virtual void Draw(glm::mat4 projection, glm::mat4 view);
protected:
	// Other member variables come and go
	Model* m_pModel;
	glm::mat4 m_ModelData;
	Shader* m_pShader;
};
