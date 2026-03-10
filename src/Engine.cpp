#include "Engine.h"
#include "Model.h"

Engine::Engine() {
	this->Initialize();
}

Engine::~Engine() {
	
}

bool Engine::Initialize() {

	t = 0.0f;

	accumulator = 0.0f;
	current_Time = glfwGetTime();
	if (!glfwInit()) {
		LOG("Could not init glfw");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Do window stuff here
	if (!WindowHandler::Get().Init(1280, 720)) {
		LOG("Failed to initialize window");
		return false;
	}

	if (!InputHandler::Get().Init(*WindowHandler::Get().GetWindow())) {
		LOG("Failed to initialize input handler");
		return false;
	}
	
	if (!AudioEngine::Get().Init()) {
		LOG("Failed to initialize audio handler");
		return false;
	}
	// dont load audio here, this is kinda stupid, load it in a level handler..
	// temp code.
	
	

	// Load opengl functions from glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		// GLAD initialization failed
		LOG("Failed to initialize glad functions");
		return false;
	}
	// Initial window resolution change cause linux is weird
	#ifdef linux
	// This issue happens because i have my monitor scaled up by 130%, so it multiplies by 1.30%
	glViewport(0, 0, WindowHandler::Get().GetWidth() * 1.30, WindowHandler::Get().GetHeight() * 1.30);
	#endif
	// Certain textures seem to not be happy with this enabled, the base backpack from ogl
	// works fine and it doesnt even complain about it when this is enabled.
	// Any other texture seems to really disagree and it really wants this off in order to work. 
	//stbi_set_flip_vertically_on_load(true);	
	glfwSetCursorPosCallback(WindowHandler::Get().GetWindow(), InputHandler::Get().MouseCallback);
	
	glEnable(GL_DEPTH_TEST);


#ifdef VSYNC
	glfwSwapInterval(1); // vsync, use in fullscreen if possible
	// glfw uses DwmFlush when vsync is on in windowed mode. Might lead to less than the refresh rate of monitor
#endif //  VSYNC
#if LOCKCURSOR
LOG("Locking cursor to screen");
glfwSetInputMode(WindowHandler::Get().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#endif
	ResourceHandler::Get().Precache();
	LOG("Finished initializing engine");
	if (!this->m_Logic.Init()){
		LOG("Failed to initialize game logic");
		return false;
	}

	return true;
}


// TODO: USE camelCase
void Engine::Run() {	
	while (!glfwWindowShouldClose(WindowHandler::Get().GetWindow())) { // make this look nicer, put it into a function in the handler
		// input first!
		float new_Time = glfwGetTime();
		float frame_Time = new_Time - current_Time;
		current_Time = new_Time;

		accumulator += frame_Time;
		InputHandler::Get().Update();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0, 1.0f, 1.0f, 1.0f);
		// freeing the physics
		while (accumulator >= fdt) {
			this->m_Logic.Update(fdt);
			
			accumulator -= fdt;
			t += fdt;
		}

		// a m_Logic.Integrate() function should exist based on time accumulation for fixed
		// Physics timesteps

		this->m_Logic.Render();
		glfwSwapBuffers(WindowHandler::Get().GetWindow());
	}
}

void Engine::Exit() {
	// Do all cleanup here
	LOG("Cleaning up engine");
	AudioEngine::Get().Shutdown();
	ResourceHandler::Get().Cleanup();
}
