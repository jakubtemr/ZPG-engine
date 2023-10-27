#include "Model.h"
Model::Model()
{
	
}
GLuint Model::CreateVao(Vertex* points, int size)
{
	//vertex buffer object (VBO)
	GLuint VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	GLuint VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0); // Position
	glEnableVertexAttribArray(1); // Color
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	return VBO;
}

GLuint Model::CreateVao(const float* points, int size)
{
	//vertex buffer object (VBO)
	GLuint VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	GLuint VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0); // Position
	glEnableVertexAttribArray(1); // Color
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 6*sizeof(float), (GLvoid*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6*sizeof(float), (GLvoid*)offsetof(Vertex, color));
	return VBO;
}
GLuint Model::RightTriangle() {
	/*float points[] = {
		0.1f, -0.5f, 0.0f,
		0.1f, 0.5f, 0.0f,
		0.9f, -0.5f, 0.0f
	};*/
	Vertex vertices[] = {
		{ {-0.9f, -0.5f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f} },
		{ {0.0f, 0.5f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f} },
		{ {0.0f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f} }
	};
	return CreateVao(vertices, sizeof(vertices));

}

GLuint Model::Tree() {
	/*float points[] = {
		0.1f, -0.5f, 0.0f,
		0.1f, 0.5f, 0.0f,
		0.9f, -0.5f, 0.0f
	};*/
	return CreateVao(tree, sizeof(tree));

}

GLuint Model::Sphere() {
	/*float points[] = {
		0.1f, -0.5f, 0.0f,
		0.1f, 0.5f, 0.0f,
		0.9f, -0.5f, 0.0f
	};*/
	return CreateVao(sphere, sizeof(sphere));

}

GLuint Model::Suzi() {
	/*float points[] = {
		0.1f, -0.5f, 0.0f,
		0.1f, 0.5f, 0.0f,
		0.9f, -0.5f, 0.0f
	};*/
	return CreateVao(suziSmooth, sizeof(suziSmooth));

}

GLuint Model::LeftTriangle() {

	/*
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::rotate(glm::mat4(1.0f), 0.2f, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::rotate(M, 0.2f, glm::vec3(1.0f, 0.0f, 0.0f));
	M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, window));
	M = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	*/
	Vertex vertices[] = {
		{ {0.1f, -0.5f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0f} },
		{ {0.1f, 0.5f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f} },
		{ {0.9f, -0.5f, 0.0f, 1.0f}, {1.0f, 0.0f, 1.0f, 1.0f} }
	};
	return CreateVao(vertices, sizeof(vertices));
	
}

GLuint Model::Square() {

	Vertex vertices[] = {
		{ {-0.5f, -0.5f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f} },
		{ {-0.5f, 0.5f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f} },
		{ {0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f} },
		{ {0.5f, 0.5f, 0.0f, 1.0f}, {1.0f, 0.0f, 1.0f, 1.0f} },
	};
	return CreateVao(vertices, sizeof(vertices));
}

GLuint Model::Ball() {

	Vertex vertices[] = {
		{ {-0.5f, -0.5f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f} },
		{ {-0.5f, 0.5f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f} },
		{ {0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f} },
		{ {0.5f, 0.5f, 0.0f, 1.0f}, {1.0f, 0.0f, 1.0f, 1.0f} },
	};
	return CreateVao(vertices, sizeof(vertices));
}

GLuint Model::Cube() {

	Vertex vertices[] = {
		{ {-0.5f, -0.5f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f} },
		{ {-0.5f, 0.5f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f} },
		{ {0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f} },
		{ {0.5f, 0.5f, 0.0f, 1.0f}, {1.0f, 0.0f, 1.0f, 1.0f} },
	};
		Vertex verticles[] = {
			{{ -1.0f,-1.0f,-1.0f,1.0f},{1.0f, 0.0f, 0.0f, 1.0f}},
			{{ -1.0f,-1.0f, 1.0f,1.0f},{0.0f, 1.0f, 0.0f, 1.0f}},
			{{ -1.0f, 1.0f, 1.0f,1.0f},{1.0f, 0.0f, 0.0f, 1.0f}},
			{{ 1.0f, 1.0f,-1.0f,1.0f},{1.0f, 0.0f, 0.0f, 1.0f}},
			{ {-1.0f,-1.0f,-1.0f,1.0f}, {1.0f, 0.0f, 1.0f, 1.0f} },
			{ {-1.0f, 1.0f,-1.0f,1.0f}, {1.0f, 0.0f, 1.0f, 1.0f} },
			{ {1.0f,-1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f, 1.0f} },
			/*-1.0f,-1.0f,-1.0f,
			1.0f,-1.0f,-1.0f,
			1.0f, 1.0f,-1.0f,
			1.0f,-1.0f,-1.0f,
			-1.0f,-1.0f,-1.0f,
			-1.0f,-1.0f,-1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f,-1.0f,
			1.0f,-1.0f, 1.0f,
			-1.0f,-1.0f, 1.0f,
			-1.0f,-1.0f,-1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f,-1.0f, 1.0f,
			1.0f,-1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f,-1.0f,-1.0f,
			1.0f, 1.0f,-1.0f,
			1.0f,-1.0f,-1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f,-1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f,-1.0f,
			-1.0f, 1.0f,-1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f,-1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f,-1.0f, 1.0f*/
		};



	return CreateVao(verticles, sizeof(vertices));
}

Model::~Model()
{
}
