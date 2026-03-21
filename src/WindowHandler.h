#pragma once
#include "GLFW/glfw3.h"
#include "tools.h"

class WindowHandler {

public:
	bool Init(int width = 1920, int height = 1080, std::string name = "Lorem Ipsum");
	static WindowHandler& Get() {
		return m_WindowInstance;
	}
	int GetWidth() const { return m_nWindowWidth; }
	int GetHeight() const { return m_nWindowHeight; }
	bool ChangeResolution(int x, int y);  // opengl function needed to change resolutions, just wrapped here.
	std::string GetName() { return m_Name; }
	GLFWwindow* GetWindow() { return m_pWindow; }
	void ShowCursor(bool show);
	bool CursorStatus();
	void Exit();

	~WindowHandler();
private:

	bool m_bShowCursor;
	static WindowHandler m_WindowInstance;
	WindowHandler() : m_nWindowHeight(1080), m_nWindowWidth(1920), m_pWindow(nullptr), m_bShowCursor(true) {
		
	}

	GLFWwindow* m_pWindow;
	int m_nWindowWidth;
	int m_nWindowHeight;
	std::string m_Name;
	
	bool CreateWindow(int width, int height, std::string name="Lorem Ipsum");
};

void FrameBufferSizeCallback(GLFWwindow* window, int x, int y);
