#include "Shader.h"



Shader::Shader(const char* vertexPath, const char* fragmentPath) {

	// Create ifstream objects to read file path
	std::string vertex_code;
	std::string fragment_code;
	std::ifstream vertex_shader_file;
	std::ifstream frag_shader_file;


	vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	frag_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);


	try {
		vertex_shader_file.open(vertexPath);
		frag_shader_file.open(fragmentPath);

		std::stringstream vertex_stream, frag_stream;
		vertex_stream << vertex_shader_file.rdbuf();
		frag_stream << frag_shader_file.rdbuf();
		vertex_shader_file.close();
		frag_shader_file.close();

		vertex_code = vertex_stream.str();
		fragment_code = frag_stream.str();
	}
	catch (std::ifstream::failure e) {
		LOG("Could not read shader path : " << e.what());
	}
	const char* vert_code_c = vertex_code.c_str();
	const char* frag_code_c = fragment_code.c_str();

	// now to compile the shaders
	unsigned vertex, fragment;

	int success = 0;
	char infoLog[512];


	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vert_code_c, nullptr);
	
	glCompileShader(vertex);
	
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::cout << "cant compile vertex shader " << infoLog << '\n';
	}
	
	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, &frag_code_c, nullptr);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		std::cout << "cant compile fragment shader " << infoLog << std::endl;
	}

	// create shader program
	ID = glCreateProgram();

	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	glGetProgramInfoLog(ID, 512, nullptr, infoLog);

	if (!success) {
		LOG("Failed linking shader program: \n" << infoLog);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}
void Shader::use(void) {
	glUseProgram(this->ID);
}

void Shader::SetBool(const char* name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name), (int)value);
}
void Shader::SetInt(const char* name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::SetFloat(const char* name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name), value);
}

void Shader::SetMat4(const char* name, glm::mat4 matrix) {
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::Die() {
	if (ID != 0) {
		LOG("Shader killing");
		glDeleteShader(ID);
		LOG("Killed shader");
	}
}