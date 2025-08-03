#pragma once
#include "tools.h"
#include "Model.h"
class BaseEntity {
public:
	virtual void Spawn();
	//TODO add pre and post think functions
	virtual void Update();
	virtual void Destroy();
private:
	// Other member variables come and go
	Model* m_pModel;
	Shader* m_pShader;
};