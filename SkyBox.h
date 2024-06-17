#pragma once
#include <GL/glew.h>
#include <iostream>
#include <vector>

#include "ShaderApp.h"
//#include "Material.h"
#include "ShaderManager.h"

class SkyBox
{
private:
	GLuint textureId;
	GLuint VBO = 0;
	GLuint VAO = 0;
	ShaderApp shaderApp;
	static const std::vector<float> points;

	void initializeVao();
	void initializeVbo();

public:
	SkyBox();
	SkyBox(std::vector<std::string> paths);
	void draw();
};

