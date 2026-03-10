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
	glm::mat4 projection;
	// Use players fov instead
	projection = glm::perspective(glm::radians(player->GetFov()), (float)WindowHandler::Get().GetWidth() / WindowHandler::Get().GetHeight(), 0.1f, 1000.0f);
	this->soul_orb.Draw(projection, player->GetViewMatrix());
}

void Logic::Update(const float& dt) {
	// update on set tick	
	player->Move(dt);
    player->PlayerBoundaryCheck();
    bool chase_player = false;
    if (chase_player){
        this->soul_orb.Move(player->GetPlayerPos(), dt);
        this->soul_orb.Update(dt);
    }
	player->UpdateCamera();
}
