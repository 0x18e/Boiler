#pragma once
#include<iostream>
#include<unordered_map>
#include "Model.h"


// Cache resources, call wherever, singleton.
class ResourceHandler {
public:
	static ResourceHandler& Get() {
		return m_Instance;
	}
	void Precache();
	void ClearModel(const std::string& name);
	void ClearShader(const std::string& name);

	Model* GetModel(const std::string& name);
	Shader* GetShader(const std::string& name);
	
	void Cleanup();
	~ResourceHandler();
	
protected:
private:
	ResourceHandler();
	static ResourceHandler m_Instance;

	// all resource containers
	std::unordered_map<std::string, std::unique_ptr<Model>> m_Models;
	std::unordered_map<std::string, std::unique_ptr<Shader>> m_Shaders;
};