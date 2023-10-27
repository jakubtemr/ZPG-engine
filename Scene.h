#pragma once
#define _USE_MATH_DEFINES
#include "Model.h"
#include "ShaderApp.h"
#include "Camera.h"
#include <vector>
#include <cmath>
#include <iostream>

class Scene {
public:
    Scene();
    void AddModel(GLuint model, ShaderApp* shader, GLsizei vertexCount);
    void Render();
    ~Scene();

private:
    struct ModelShaderPair {
       GLuint model;
        ShaderApp* shader;
        GLsizei vertexCount;
    };

    std::vector<ModelShaderPair> modelShaderPairs;
    GLFWwindow* window;
    Application app;
};
