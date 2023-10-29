#pragma once
#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <type_traits>

#include "ShaderApp.h"
#include "ShaderManager.h"
#include "Model.h"
#include "ModelManager.h"
#include "Material.h"
#include "Movement.h"

class Object
{
private:
	ShaderApp shader;
	Model& model;
	glm::mat4 M = glm::mat4(1.0f);
	unsigned int id;
	glm::vec3 objectColor = glm::vec3(0.385, 0.647, 0.812);
	glm::vec3 ambientColor = glm::vec3(0.1, 0.1, 0.1);
	Movement* move;

	static unsigned int objectCount;

public:
	Object(std::string shaderName, std::string modelName);
	unsigned int getId();

	void addLineMove(glm::vec3 start, glm::vec3 end);
	void addCircleMove(glm::vec3 start, int radius);
	void update();
	void draw();
	void setColor(glm::vec3 color);
	void scale(glm::vec3 scale);
	void rotate(float angle, glm::vec3 axis);
	void translate(glm::vec3 delta);
	void setPos(glm::vec3 pos);
};

