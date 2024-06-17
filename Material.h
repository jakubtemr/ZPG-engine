#pragma once


#include <iostream> 
#include <GL/glew.h>
#include "ShaderApp.h"


class Material
{
public:
	Material();
	Material(const std::string& path);
	void bind(ShaderApp& shader);
private:
	GLuint textureId;
	GLuint loadTexture(const std::string& path);
};

