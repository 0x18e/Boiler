#include "Engine.h"
#include "GLFW/glfw3.h"
#include "Model.h"

Engine::Engine(int argc, char* argv[]) : m_Logic(this->m_PhysicsEngine) {
	if (argc == 2 && _stricmp(argv[1], "editor")) {
		this->mode = GlobalVars::EDITOR;
	}
	else {
		this->mode = GlobalVars::GAME;
	}
	// FORCE INTO EDITOR FOR DEBUG
#if FORCE_EDITOR
	this->mode = GlobalVars::EDITOR;
#endif
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
	if (!m_Renderer.Init()) {
		LOG("Failed to initialize renderer");
		return false;
	}

	if (!AudioEngine::Get().Init()) {
		LOG("Failed to initialize audio handler");
		return false;
	}
	

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
	if (!m_DebugRenderer.Init()) {
		LOG("Failed to initialize debug renderer");
		return false;
	}


#ifdef VSYNC
	glfwSwapInterval(1); // vsync, use in fullscreen if possible
	// glfw uses DwmFlush when vsync is on in windowed mode. Might lead to less than the refresh rate of monitor
#endif //  VSYNC
#if LOCKCURSOR
LOG("Locking cursor to screen");
glfwSetInputMode(WindowHandler::Get().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#endif
	ResourceHandler::Get().Precache();
	//this->m_Logic.AttachPhysEngine(m_PhysicsEngine);
	LOG("Finished initializing engine");

	if (this->mode == GlobalVars::GAME) {
		if (!this->m_Logic.Init()){
			LOG("Failed to initialize game logic");
			return false;
		}
	}
	if (this->mode == GlobalVars::EDITOR) {
		/*	hack for getting skull to just show on screen
		if (!this->m_Logic.Init()) {
			LOG("Failed to initialize game logic");
			return false;
		}
		*/
		// whatever bullshit initialization is needed
		
		this->m_Renderer.SetEditorFlag(true);
		LOG("Starting in editor mode");
	}

	return true;
}


// TODO: USE camelCase
void Engine::Run() {
	Shader m_DebugShader("C:\\Users\\hazel\\source\\repos\\0x18e\\Boiler\\assets\\shaders\\line.vs", 
		"C:\\Users\\hazel\\source\\repos\\0x18e\\Boiler\\assets\\shaders\\line.fs"); // change to relative path instead of this garb
		// or find somewhere else to use this shit
	while (!glfwWindowShouldClose(WindowHandler::Get().GetWindow())) { // make this look nicer, put it into a function in the handler
		// input first!
		float new_Time = glfwGetTime();
		float frame_Time = new_Time - current_Time;
		current_Time = new_Time;

		accumulator += frame_Time;
		InputHandler::Get().Update();
		if (InputHandler::Get().IsPressed(GLFW_KEY_R)){
			this->m_Renderer.SetDebugMode(true);
		}
		if (InputHandler::Get().IsPressed(GLFW_KEY_T)){
			this->m_Renderer.SetDebugMode(false);
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_DebugRenderer.Clear();
		// per frame

		// add debug stuff
		m_DebugRenderer.AddLine({ 0,0,0 }, { 1,0,0 }, { 1,0,0 }); // X axis
		m_DebugRenderer.AddLine({ 0,0,0 }, { 0,1,0 }, { 0,1,0 }); // Y axis
		m_DebugRenderer.AddLine({ 0,0,0 }, { 0,0,1 }, { 0,0,1 }); // Z axis

		// after normal rendering

		glClearColor(1.0, 1.0f, 1.0f, 1.0f);
		// freeing the physics
		while (accumulator >= fdt) {
			if (this->mode == GlobalVars::GAME) {
				this->m_Logic.Update(fdt); // does this affect performance
			}
			else if (this->mode == GlobalVars::EDITOR) {
				this->m_EditorContext.Update();
			}
			this->m_PhysicsEngine.Integrate(fdt);
			accumulator -= fdt;
			t += fdt;
		}
		if (this->mode == GlobalVars::GAME) {
			this->m_Renderer.Render(m_Logic.GetEntities(), m_Logic.GetPlayerViewMatrix());
			this->m_DebugRenderer.Render(m_Logic.GetPlayerViewMatrix(), m_Renderer.GetProjectionMatrix(), m_DebugShader);
		}
		else if (this->mode == GlobalVars::EDITOR) {
			// build level editor view matrix and render with level editor entities
			// TODO: check first param instead of being logic entity but something for editors.
			// TODO: change second param for a different view matrix, unsure which matrix to use or how to change it
			// another idea is to make it so that theres one main view matrix for the entirety of the engine, and swap matrices
			// sounds a lot better to do than this shitshow of multiple view matrices
			
			glm::mat4 viewmat = glm::lookAt(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f));

			this->m_Renderer.Render(m_EditorContext.GetEditorEntities(), viewmat);
		}
		glfwSwapBuffers(WindowHandler::Get().GetWindow());
	}
}

void Engine::Exit() {
	// Do all cleanup here
	LOG("Cleaning up engine");
	// temp switch case till i figure out a better idea for the global vars
	switch (this->mode) {
	case GlobalVars::EDITOR:
		this->m_EditorContext.Clean();
		break;
	case GlobalVars::GAME:
		this->m_Logic.Shutdown();
		break;
	default:
		break;
	}
	AudioEngine::Get().Shutdown();
	ResourceHandler::Get().Cleanup();
	WindowHandler::Get().Exit();
	InputHandler::Get().Cleanup();
	m_PhysicsEngine.Clean();
}
