#include "ShaderManager.h"

ShaderManager* ShaderManager::instance = nullptr;

ShaderManager* ShaderManager::getInstance() {
	if (!instance) {
		instance = new ShaderManager();
	}
	return instance;
}

void ShaderManager::initShaders() {
	shaders.emplace("lambert", ShaderApp("../final/Shaders/Shader.vert", "../final/Shaders/Lambert.frag"));
	shaders.emplace("phong", ShaderApp("../final/Shaders/Shader.vert", "../final/Shaders/Phong.frag"));
	shaders.emplace("blinn", ShaderApp("../final/Shaders/Shader.vert", "../final/Shaders/Blinn.frag"));
	shaders.emplace("phongControl", ShaderApp("../final/Shaders/Shader.vert", "../final/Shaders/PhongControl.frag"));
	shaders.emplace("skybox", ShaderApp("../final/Shaders/SkyBox.vert", "../final/Shaders/SkyBox.frag"));
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
