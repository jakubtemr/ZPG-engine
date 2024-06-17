#pragma once
#include <vector>
#include <iostream>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec2.hpp>
#include <GL/glew.h>
#include "Material.h"
#include "ShaderApp.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    //glm::vec3 Color;
};

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    Material material;

    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, Material material);
    void draw(unsigned int id, ShaderApp& shader);
private:
    GLuint VAO, VBO, EBO;

    void createMesh();
};

