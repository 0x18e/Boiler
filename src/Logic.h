#pragma once
#include<iostream>
#include "Model.h"
#include "glad/glad.h"
#include "WindowHandler.h"
#include "stb_image.h"
#include "Shader.h"
#include "tools.h"
#include "Camera.h"
#include<vector>
#include "InputHandler.h"
#include "Player.h"
#include "ResourceHandler.h"
#include "BaseEntity.h"
#include "GameObjects.h"
#include "Physics.h"
#include "Box.h"
#include <memory>
/// <summary>
/// All videogame logic should be handled here
/// As a way to separate the engine from the logic
/// </summary>
class Logic {

	// Game logic will have a delta time that is given to it via reference from main engine.
	// Game logic is separate from engine and other modules such as physics, audio, window handling, etc
	// This will have its main Init, Update, & Render function.
	// Engine calls these functions in run.
public:
	Logic(PhysicsEngine& physics) : PhysWorld(physics) {} 
	~Logic();
	
	bool Init();
	void Update(const float& dt);
	void Shutdown();
	
	std::vector<BaseEntity*> GetEntities() { return this->Entities; }
	glm::mat4 GetPlayerViewMatrix() { return this->player.get()->GetViewMatrix(); }
	
private:
	BaseEntity ent;
	Skull soul_orb;
	PhysicsEngine &PhysWorld; // reference to our physics engine
	Box* box;
	float m_fDeltaTime; // Might be static in order to track everywhere else or global...
	std::unique_ptr<Player> player;
	std::vector<BaseEntity*> Entities;
};

