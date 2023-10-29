#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>  
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Camera.h"
#include "CameraObserver.h"
#include "LightObserver.h"

class Camera;
class ShaderApp: public CameraObserver, public LightObserver {
private:
    GLuint shaderProgramId;
    GLuint vertexShaderId;
    GLuint fragmentShaderId;
    Camera* m_camera;
    std::string parseShader(const std::string& filePath);
    GLuint compileShader(const std::string& shader, GLuint type);
    bool checkShaderCompileStatus(GLint id);
    void checkLinkStatus();
    void createShader(const std::string& vertexShader, const std::string& fragmentShader);

public:
    ShaderApp(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    ShaderApp();

    void useProgram();
    void cancelProgram();
    void sendUniform(const GLchar* name, glm::mat4 data);
    void sendUniform(const GLchar* name, glm::vec3 data);
    void sendUniform(const GLchar* name, int data);
    void sendUniform(const GLchar* name, float data);
    void update(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 camPos);
    void update(int id, int type, glm::vec3 lightPos, glm::vec3 lightColor, int lightCount);
    void update(int id, int type, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 lightDir, float cutOff, int lightCount);
};
