#include "Model.h"

Model::Model(const float* data, size_t dataSize) {
    const size_t floatsPerVertex = 6;
    const size_t numVertices = dataSize / floatsPerVertex;

    std::vector<Vertex> vertices;
    vertices.reserve(numVertices);

    for (size_t i = 0; i < numVertices; ++i) {
        Vertex vertex;
        vertex.Position = glm::vec3(data[i * floatsPerVertex], data[i * floatsPerVertex + 1], data[i * floatsPerVertex + 2]);
        vertex.Normal = glm::vec3(data[i * floatsPerVertex + 3], data[i * floatsPerVertex + 4], data[i * floatsPerVertex + 5]);
        vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        vertices.push_back(vertex);
    }

    std::vector<GLuint> indices;
    for (GLuint i = 0; i < numVertices; i += 3) {
        indices.push_back(i);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
    }
    Material emptyMaterial;

    meshes.push_back(Mesh(vertices, indices, emptyMaterial));
}


void Model:: draw(unsigned int id, ShaderApp& shader) {
    for (Mesh mesh : meshes) {
        mesh.draw(id, shader);
    }
}

Model::~Model()
{
}
