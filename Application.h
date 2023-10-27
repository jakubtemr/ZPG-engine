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
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
/*
#include "Shader.h"
#include "Object.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "ModelManager.h"
*/
#include "CallbackHandler.h"
#include "Scene.h"

class Application
{
public:
	static Application* getInstance();
	void run();

private:
	static Application* instance;
	Application();

	int width;
	int height;

	Camera* cam;
	float mouseX = 0.f;
	float mouseY = 0.f;
	GLuint selectedObjectIndex;

	Scene* mainScene;
	//void identifyObject();
	void pushObject();
};
