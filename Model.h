#pragma once
#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <vector>

#include"ShaderApp.h"
#include "ShaderManager.h"
#include "Mesh.h"


class Model
{
private:
    std::vector<Mesh> meshes;

public:
    Model(const float* data, size_t dataSize);
    void draw(unsigned int id, ShaderApp& shader);
    ~Model();
};

