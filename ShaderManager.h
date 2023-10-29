#pragma once
#include "ShaderApp.h"

#include <unordered_map>
#include <string>
#include <iostream>

class ShaderManager
{
public:
	static ShaderManager* getInstance();

	ShaderApp& getShader(std::string shaderName);
private:
	std::unordered_map <std::string, ShaderApp> shaders;

	void initShaders();

	static ShaderManager* instance;
	ShaderManager();
};

