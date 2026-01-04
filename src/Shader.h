#pragma once
#include <glad/glad.h> // include glad to get the required OpenGL headers
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "tools.h"

class Shader {

public:
	Shader(const char* vertexPath, const char* fragmentPath);
	
	// Use this shader program
	void use(void);
	void SetBool(const char* name, bool value) const;
	void SetInt(const char* name, int value) const;
	void SetFloat(const char* name, float value) const;
	void SetMat4(const char* name, glm::mat4 matrix);
	void Die();
private:
	// Programs ID
	unsigned int ID;
};

