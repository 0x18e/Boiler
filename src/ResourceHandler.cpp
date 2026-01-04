#include "ResourceHandler.h"

ResourceHandler ResourceHandler::m_Instance;

void ResourceHandler::Precache() {
	// load all resources here.
	// Models
	this->m_Models["obj_debug"] = std::make_unique<Model>("assets/models/kiwi/kiwi.obj");
	this->m_Models["obj_skull"] = std::make_unique<Model>("assets/models/skull/12140_Skull_v3_L2.obj");
	// Shaders
	this->m_Shaders["base_shader"] = std::make_unique<Shader>("assets/shaders/model_loading.vs", "assets/shaders/model_loading.fs");
}

void ResourceHandler::ClearModel(const std::string& name) {
	// Used when changing levels to remove unneeded models. Small optimizations
	this->m_Models.erase(name);
}

void ResourceHandler::ClearShader(const std::string& name) {
	this->m_Shaders.erase(name);
}

Model* ResourceHandler::GetModel(const std::string& name) {
	for (auto& pair : this->m_Models) {
		if (pair.first == name) {
			return pair.second.get(); // get returns non ownable pointer, the raw pointer
		}
	}
	LOG("Missing model: " << name);
	return nullptr;
}

Shader* ResourceHandler::GetShader(const std::string& name){
	
	for (auto& pair : this->m_Shaders) {
		if (pair.first == name) {

			return pair.second.get();
		}
	}
	LOG("Missing shader: " << name);
	return nullptr;
}

void ResourceHandler::Cleanup() {
	for (auto& pair : this->m_Shaders) {
		pair.second.get()->Die(); // clean all shaders
	}
}
ResourceHandler::~ResourceHandler() {
	// RAII from unique_ptr resources
}

ResourceHandler::ResourceHandler() {

}
