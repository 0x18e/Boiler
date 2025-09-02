#include "WindowHandler.h"
#include "GLFW/glfw3.h"


WindowHandler WindowHandler::m_WindowInstance;
void FrameBufferSizeCallback(GLFWwindow* window, int x, int y) {
	
	glViewport(0, 0, x, y);
}

void WindowHandler::ShowCursor(bool showval) {
	this->m_bShowCursor = showval;
	if (m_bShowCursor)
		glfwSetInputMode(this->m_pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else
		glfwSetInputMode(this->m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

bool WindowHandler::CursorStatus() {
	return this->m_bShowCursor;
}

bool WindowHandler::CreateWindow(int width, int height, std::string name) {
	LOG("Creating Window");
	glfwWindowHint(GLFW_RESIZABLE, true);

	this->m_pWindow = glfwCreateWindow(width, height,
		name.c_str(),
		nullptr,
		nullptr);
	if (!m_pWindow) {
		LOG("Could not create window");
		return false;
	}
	glfwMakeContextCurrent(this->m_pWindow);
	glfwSetFramebufferSizeCallback(this->m_pWindow, FrameBufferSizeCallback);	
	/*
	glfwSetWindowSizeLimits(this->m_pWindow, this->m_nWindowWidth,
		this->m_nWindowHeight,
		this->m_nWindowWidth,
		this->m_nWindowHeight
	);

	*/
	//glfwSetInputMode(this->m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return true;
}

bool WindowHandler::Init(int width, int height, std::string name) {
	// no need for error checking here this should be managed by whoever is using this
	this->m_nWindowWidth = width;
	this->m_nWindowHeight = height;
	return this->CreateWindow(this->m_nWindowWidth, m_nWindowHeight);
}

bool WindowHandler::ChangeResolution(int x, int y) {
	return false;
}


WindowHandler::~WindowHandler() {
    LOG("Cleaning up window");
    if (this->m_pWindow != nullptr) {
        glfwDestroyWindow(this->m_pWindow);
		this->m_pWindow = nullptr;
		this->m_Name.clear();
        LOG("Window destroyed");
    }
}
