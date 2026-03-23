#pragma once
#include<iostream>
#include "Logic.h"
#include "openal/al.h"
#include "openal/alc.h"
#include "AudioEngine.h"
#include "Physics.h"

/*TODO
* REWRITE THE ENTIRE Model.h class, this has a lot of weird code copied from opengl
*/
class GlobalVars {
	
};

class Engine {

	// Main functions will be here
	// Initializing all subsystems
	// Run entire simulation, will also include update and frame independent rendering
	// Exit and cleanup everything USING THE RESOURCE MANAGER
public:
	Engine();
	~Engine();
	bool Initialize();
	void Run();
	void Exit();
	PhysicsEngine m_PhysicsEngine;
private:
	Logic m_Logic;
	
	float current_Time;
	float t; // engine time
	// change from 0.01 to diff amount later on because this might be too fast
	const float fdt = 0.01; // fixed delta_time;
	float accumulator;
};
