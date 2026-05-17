#pragma once
#include "BaseEntity.h"
#include "WindowHandler.h"
#include <vector>
#include "Shader.h"
#include "tools.h"

struct LineVert {
	glm::vec3 position;
	glm::vec3 color;
};

class Renderer {
private:
	float m_fAspectRatio;
	float m_iFar, m_iNear;
	int m_iFov;
	glm::mat4 m_ProjectionMatrix;
	bool m_bDebugMode;
	bool m_EditorMode;
public:
	void Render(const std::vector<BaseEntity*> &entities, const glm::mat4 &viewMatrix);
	bool Init();
	void SetDebugMode(const bool& val);
	void SetEditorFlag(bool flag) { this->m_EditorMode = flag; }
	glm::mat4& GetProjectionMatrix() { return this->m_ProjectionMatrix; }
};

class DebugRenderer {
private:
	unsigned int m_iMaxVertices = 100;
	unsigned int m_iVBO = 0;
	unsigned int m_iVAO = 0;
	std::vector<LineVert> m_Vertices;
	
public:
	DebugRenderer();
	~DebugRenderer();
	bool Init();
	void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix,Shader& shader);
	void AddLine(const glm::vec3& a, const glm::vec3& b, const glm::vec3& color);
	void Shutdown();
	void Clear();
	
};