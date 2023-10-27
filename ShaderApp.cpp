#include "ShaderApp.h"


ShaderApp::ShaderApp() {
	const char* vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"
		"layout(location=1) in vec4 vertexColor;"
		"out vec4 fragColor;"
		"void main () {"
		"     gl_Position = projectionMatrix *  viewMatrix * modelMatrix * vec4(vp, 1.0) ;"//
		"     fragColor = vertexColor;"
		"}";

	const char* fragment_shader =
		"#version 330\n"
		"in vec4 fragColor;"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = fragColor;"
		"}";
	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertex_shader);
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

}

GLuint ShaderApp::CreateShader(GLenum shaderType, const char* source) {
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	return shader;
}
void ShaderApp::SetTransformationMatrix(const glm::mat4& matrix) {
	GLint modelMatrixLocation = glGetUniformLocation(shaderProgram, "modelMatrix");
	if (modelMatrixLocation != -1) {
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	else {
		std::cerr << "Warning: modelMatrix uniform not found in shader!" << std::endl;
	}
}

void ShaderApp::SetViewMatrix(const glm::mat4& matrix) {
	GLint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
	if (viewMatrixLocation != -1) {
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	else {
		std::cerr << "Warning: viewMatrix uniform not found in shader!" << std::endl;
	}
}
void ShaderApp::SetProjectionMatrix(const glm::mat4& matrix) {
	GLint viewMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
	if (viewMatrixLocation != -1) {
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	else {
		std::cerr << "Warning: viewMatrix uniform not found in shader!" << std::endl;
	}
}

void ShaderApp::UseShader() {
	glUseProgram(shaderProgram);
}

ShaderApp::~ShaderApp() {
	glDeleteProgram(shaderProgram);
}
