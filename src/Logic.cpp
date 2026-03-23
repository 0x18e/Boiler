#include "tools.h"
#include "Logic.h"

//TODO: separate the rendering from the logic class
//TODO: design and create a debug renderer that way we can debug physics and how things are rendered.
// basic gist Renderer.Render(world, camera); whether it should be a singleton or something i am unsure. it shouldnt.

Logic::~Logic() {
	// keep in destructor for now
	if (&PhysWorld) {
		LOG("Physicsworld still exists in game logic");
	}
	LOG("Logic destructor called");
}

bool Logic::Init() {
	this->m_fDeltaTime = .0f;
	LOG("Logic constructor went off");
	this->player = std::make_unique<Player>();
	this->ent.Spawn();
	this->soul_orb.Spawn();
	box = new Box();
	this->box->SetPhysObject(this->PhysWorld.AddObject(glm::vec3(0.0, 0.0, 0.0)));
	this->box->Spawn();
	this->Entities.push_back(box);
	return true;

}
void Logic::Shutdown() {
	for (auto* ent : Entities) {
		ent->Destroy();
		delete ent;
	}
}

void Logic::Render() {
	glm::mat4 projection;
	// Use players fov instead
	projection = glm::perspective(glm::radians(player->GetFov()), (float)WindowHandler::Get().GetWidth() / WindowHandler::Get().GetHeight(), 0.1f, 1000.0f);
	this->soul_orb.Draw(projection, player->GetViewMatrix());
	for (auto *ent : Entities) {
		ent->Draw(projection, player->GetViewMatrix());
	}
	
}

void Logic::Update(const float& dt) {
	// update on set tick
	if (InputHandler::Get().IsPressed(GLFW_KEY_E)) {
		Box* b = new Box();
		b->SetPhysObject(this->PhysWorld.AddObject(glm::vec3(0.0, 0.0, 0.0)));
		b->Spawn();
		b->SetBoxPos(player->GetForwardVector(), player->GetPlayerPos());
		Entities.push_back(b);

	}
	player->Move(dt);
    player->PlayerBoundaryCheck();
	//box->Update(dt);
    bool chase_player = false;
    if (chase_player){
        //this->soul_orb.Move(player->GetPlayerPos(), dt);
        //this->soul_orb.Update(dt);
    }

	for (auto* ent : Entities) {
		ent->Update(dt);
	}
	player->UpdateCamera();
}
