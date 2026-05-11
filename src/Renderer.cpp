#include "Renderer.h"

bool Renderer::Init() {
	bool flag = true;

	this->m_ProjectionMatrix = glm::mat4(1.0f);
	this->m_fAspectRatio = (float)WindowHandler::Get().GetWidth() / WindowHandler::Get().GetHeight();
	this->m_iFar = 1000.0f;
	this->m_iNear = 0.1f;
	this->m_iFov = glm::radians(90.0f);
	this->m_bDebugMode = false;
	return flag;
}

void Renderer::Render(const std::vector<BaseEntity*> &entities, const glm::mat4 &viewMatrix) {
	// Use players fov instead
	this->m_ProjectionMatrix = glm::perspective((float)this->m_iFov, this->m_fAspectRatio, this->m_iNear, this->m_iFar);
	for (auto* ent : entities) {
		if (this->m_bDebugMode){
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		ent->Draw(m_ProjectionMatrix, viewMatrix);
		if (this->m_bDebugMode){
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}
void Renderer::SetDebugMode(const bool& val) {
	this->m_bDebugMode = val;
}
DebugRenderer::DebugRenderer() {
	
}
DebugRenderer::~DebugRenderer() {

}
bool DebugRenderer::Init() {
	m_iVAO = 0;
	m_iVBO = 0;
	glGenVertexArrays(1, &m_iVAO);
	glGenBuffers(1, &m_iVBO);
	glBindVertexArray(m_iVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_iVBO);
	//TODO: bind into EBO to add line width
	glBufferData(GL_ARRAY_BUFFER, this->m_iMaxVertices * sizeof(LineVert), nullptr, GL_DYNAMIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LineVert), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(LineVert), (void*)(1 * sizeof(glm::vec3)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	return true;
}
void DebugRenderer::AddLine(const glm::vec3& a, const glm::vec3& b, const glm::vec3& color) {
	this->m_Vertices.push_back({ a, color});
	this->m_Vertices.push_back({ b, color});
}	
void DebugRenderer::Clear() {
	this->m_Vertices.clear();
}
void DebugRenderer::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, Shader& shader) {
	if (m_Vertices.empty()) {
		return;
	}
	shader.use();
	shader.SetMat4("viewProj", projectionMatrix * viewMatrix);
	glBindVertexArray(m_iVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_iVBO);

	glBufferSubData(GL_ARRAY_BUFFER, 0, m_Vertices.size() * sizeof(LineVert), m_Vertices.data());

	glDrawArrays(GL_LINES, 0, (GLsizei)m_Vertices.size());
	glBindVertexArray(0);
}