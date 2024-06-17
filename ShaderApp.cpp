#include "ShaderApp.h"

ShaderApp::ShaderApp(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
	createShader(parseShader(vertexShaderPath), parseShader(fragmentShaderPath));
}

std::string ShaderApp::parseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);
	std::stringstream ss;

	while (stream)
	{
		std::string line;
		std::getline(stream, line);
		ss << line << "\n";
	}

	return ss.str();
}

GLuint ShaderApp::compileShader(const std::string& shader, GLuint type)
{
	GLuint id = glCreateShader(type);
	const char* src = shader.c_str();
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	if (checkShaderCompileStatus(id) == false) {
		glDeleteShader(id);
		return 0;
	}

	return id;
}
bool ShaderApp::checkShaderCompileStatus(GLint id)
{
	GLint status;

	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		GLchar* message = new GLchar[length + 1];
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << message << std::endl;
		return false;
	}
	return true;
}

void ShaderApp::checkLinkStatus() {
	GLint status;
	glGetProgramiv(this->shaderProgramId, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(this->shaderProgramId, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->shaderProgramId, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}


void ShaderApp::useProgram() {
	glUseProgram(this->shaderProgramId);
}

void ShaderApp::cancelProgram() {
	glUseProgram(0);
	glDeleteProgram(this->shaderProgramId);
}

void ShaderApp::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	this->shaderProgramId = glCreateProgram();
	this->vertexShaderId = compileShader(vertexShader, GL_VERTEX_SHADER);
	this->fragmentShaderId = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(this->shaderProgramId, this->fragmentShaderId);
	glAttachShader(this->shaderProgramId, this->vertexShaderId);
	glLinkProgram(this->shaderProgramId);

	checkLinkStatus();
}

void ShaderApp::sendUniform(const GLchar* name, glm::mat4 data) {
	GLint uniformID = glGetUniformLocation(this->shaderProgramId, name);
	if (uniformID >= 0) {
		glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(data));
	}
	else {
		//printf("In shader doesnt exist uniform variable %s!", name);
	}
}

void ShaderApp::sendUniform(const GLchar* name, glm::vec3 data)
{
	GLint myLoc = glGetUniformLocation(this->shaderProgramId, name);
	if (myLoc >= 0) {
		glProgramUniform3f(this->shaderProgramId, myLoc, data.x, data.y, data.z); 
	}
	else {
		//printf("In shader doesnt exist uniform variable %s!", name);
	}
}

void ShaderApp::sendUniform(const GLchar* name, int data)
{
	GLint myLoc = glGetUniformLocation(this->shaderProgramId, name);
	if (myLoc >= 0) {
		glProgramUniform1i(this->shaderProgramId, myLoc, data);
	}
	else {
		//printf("In shader doesnt exist uniform variable %s!", name);
	}
}

void ShaderApp::sendUniform(const GLchar* name, float data)
{
	GLint myLoc = glGetUniformLocation(this->shaderProgramId, name);
	if (myLoc >= 0) {
		glProgramUniform1f(this->shaderProgramId, myLoc, data);
	}
	else {
		//printf("In shader doesnt exist uniform variable %s!", name);

	}
}

void ShaderApp::update(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 camPos) {
	useProgram();
	sendUniform("projectionMatrix", projectionMatrix);
	sendUniform("viewMatrix", viewMatrix);
	sendUniform("cameraPos", camPos);
}

void ShaderApp::update(int id, int type, glm::vec3 lightPos, glm::vec3 lightColor, int lightCount)
{
	useProgram();
	sendUniform(("lights[" + std::to_string(id) + "].type").c_str(), type);
	sendUniform(("lights[" + std::to_string(id) + "].position").c_str(), lightPos);
	sendUniform(("lights[" + std::to_string(id) + "].barva").c_str(), lightColor);
	sendUniform("lightsCount", lightCount);
}

void ShaderApp::update(int id, int type, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 lightDir, float cutOff, int lightCount)
{
	useProgram();
	sendUniform(("lights[" + std::to_string(id) + "].type").c_str(), type);
	sendUniform(("lights[" + std::to_string(id) + "].position").c_str(), lightPos);
	sendUniform(("lights[" + std::to_string(id) + "].barva").c_str(), lightColor);
	sendUniform(("lights[" + std::to_string(id) + "].lightDir").c_str(), lightDir);
	sendUniform(("lights[" + std::to_string(id) + "].cutOff").c_str(), cutOff);
	sendUniform("lightsCount", lightCount);
}

ShaderApp::ShaderApp(){}