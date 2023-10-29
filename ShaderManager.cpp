#include "ShaderManager.h"

ShaderManager* ShaderManager::instance = nullptr;

ShaderManager* ShaderManager::getInstance() {
	if (!instance) {
		instance = new ShaderManager();
	}
	return instance;
}

void ShaderManager::initShaders() {
	shaders.emplace("lambert", ShaderApp("Shaders/Shader.vert", "Shaders/Lambert.frag"));
	shaders.emplace("phong", ShaderApp("Shaders/Shader.vert", "Shaders/Phong.frag"));
	shaders.emplace("blinn", ShaderApp("Shaders/Shader.vert", "Shaders/Blinn.frag"));
}

ShaderApp& ShaderManager::getShader(std::string shaderName)
{
	auto shader = shaders.find(shaderName);
	if (shader != shaders.end()) {
		return shader->second;
	}
	throw std::runtime_error("Bad observer shader!");
}

ShaderManager::ShaderManager() {
	initShaders();
}
