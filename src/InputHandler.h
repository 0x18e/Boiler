#pragma once
#include<unordered_map>
#include<string>
#include<GLFW/glfw3.h>
#include "tools.h"
#include "WindowHandler.h"


class InputHandler {
public:
	static InputHandler& Get() {
		return m_sInstance;
	}
	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
	bool Init(GLFWwindow &window);
	
	double GetPitch();
	double GetYaw();

	void Update();
	// Minimal approach to input, later on will add previously held keys, vs current keys, etc.
	bool IsHeld(const int& key);
	bool IsPressed(const int& key);
	bool IsReleased(const int& key);
	void Cleanup();
	~InputHandler();

private:

	double m_dXrel, m_dYrel; // relative x and y for mouse input
	static double m_dYaw;
	static double m_dPitch;
	static double lastX, lastY;
	static bool m_bFirstMouse;

	static InputHandler m_sInstance;
	GLFWwindow* m_pWindow;
	InputHandler();
};