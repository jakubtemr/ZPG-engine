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
#include "Scene.h"
#include "Model.h"
#include "ShaderApp.h"



int main(void)
{
	Scene scene;
	Model model;
	
	//scene.AddModel(model.LeftTriangle(), new ShaderApp(),3);
	//scene.AddModel(model.RightTriangle(), new ShaderApp(),3);
	//scene.AddModel(model.Square(), new ShaderApp(),4);
	//scene.AddModel(model.Cube(), new ShaderApp(), 7);
	//scene.AddModel(model.Suzi(), new ShaderApp(), 2904);
	//scene.AddModel(model.Tree(), new ShaderApp(), 92814);
	scene.AddModel(model.Sphere(), new ShaderApp(), 2880);
	scene.Render();
	return 0;
}