#include "tools.h"
#include "Logic.h"

Logic::Logic() {
}

Logic::~Logic() {
}

bool Logic::Init() {
	this->m_fDeltaTime = .0f;
	LOG("Logic constructor went off");
	this->player = std::make_unique<Player>();
	this->ent.Spawn();
	this->soul_orb.Spawn();
	return true;
}

void Logic::Render() {
	
	//Model* ourModel = ResourceHandler::Get().GetModel("obj_debug");
	//Shader* ourShader = ResourceHandler::Get().GetShader("base_shader");
	//ourShader->use();
	glm::mat4 projection;
	// Use players fov instead
	projection = glm::perspective(glm::radians(player->GetFov()), (float)WindowHandler::Get().GetWidth() / WindowHandler::Get().GetHeight(), 0.1f, 100.0f);

	//ourShader->SetMat4("projection", projection);
	//ourShader->SetMat4("view", player->GetViewMatrix());


	//glm::mat4 model = glm::mat4(1.0f);
	//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
	//model = glm::rotate(model, (0) * (float)glfwGetTime() * glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//ourShader->SetMat4("model", model);
	//ourModel->Draw(*ourShader);
	
	//this->ent.Draw(projection, player->GetViewMatrix());
	this->soul_orb.Draw(projection, player->GetViewMatrix());
}

void Logic::Update() {
	// update on set tick	
	player->Move();
	
	//this->ent.Update();
	this->soul_orb.Update();
	player->UpdateCamera();
}
