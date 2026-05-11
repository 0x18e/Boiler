#pragma once
#include<iostream>
#include "Logic.h"
#include "openal/al.h"
#include "openal/alc.h"
#include "AudioEngine.h"
#include "Physics.h"
#include "Renderer.h"
#include "LevelEditor.h"

/*TODO
* REWRITE THE ENTIRE Model.h class, this has a lot of weird code copied from opengl
*/

class GlobalVars {
public:
	// temp code, still deciding whether globalvars make sense or not. console or no console
	enum modes {
		GAME,
		EDITOR
	};
	// maybe use imgui?, imgui builds failing check later https://github.com/ocornut/imgui
};

class Engine {

	// Main functions will be here
	// Initializing all subsystems
	// Run entire simulation, will also include update and frame independent rendering
	// Exit and cleanup everything USING THE RESOURCE MANAGER
public:
	Engine(int argc, char* argv[]);
	~Engine();
	bool Initialize();
	void Run();
	void Exit();
	PhysicsEngine m_PhysicsEngine;
	Renderer m_Renderer;
	DebugRenderer m_DebugRenderer;
private:
	Logic m_Logic;
	
	
	GlobalVars::modes mode; // temp
	LevelEditorContext m_EditorContext;

	float current_Time;
	float t; // engine time
	// change from 0.01 to diff amount later on because this might be too fast
	const float fdt = 0.01; // fixed delta_time;
	float accumulator;
};
