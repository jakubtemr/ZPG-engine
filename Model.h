#pragma once
#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include "Application.h"
#include "ShaderApp.h"
#include "tree.h"
#include "suzi_smooth.h"
#include "sphere.h"

class Model
{
public:
	Model();
	GLuint LeftTriangle();
	GLuint RightTriangle();
	GLuint Square();
	GLuint Ball();
	GLuint Cube();
	GLuint Tree();
	GLuint Suzi();
	GLuint Sphere();
	struct Vertex {
		glm::vec4 position;
		glm::vec4 color;
	};
	size_t VertexCount();
	~Model();
private:
	GLuint CreateVao(Vertex* points, int size);
	GLuint CreateVao(const float* points, int size);



};

