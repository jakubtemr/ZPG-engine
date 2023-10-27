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
#include <iostream>

class ShaderApp {
public:
	ShaderApp();
	void UseShader();
	void SetTransformationMatrix(const glm::mat4& matrix);
	void SetViewMatrix(const glm::mat4& matrix);
	void SetProjectionMatrix(const glm::mat4& matrix);
	~ShaderApp();

private:
	GLuint shaderProgram;
	GLuint CreateShader(GLenum shaderType, const char* source);
};


