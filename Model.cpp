#include "Model.h"
/*
Model::Model(const float* data, size_t dataSize,std::string texture) {
    const size_t floatsPerVertex = 6;
    const size_t numVertices = dataSize / floatsPerVertex;

    std::vector<Vertex> vertices;
    vertices.reserve(numVertices);

    for (size_t i = 0; i < numVertices; ++i) {
        Vertex vertex;
        vertex.Position = glm::vec3(data[i * floatsPerVertex], data[i * floatsPerVertex + 1], data[i * floatsPerVertex + 2]);
        vertex.Normal = glm::vec3(data[i * floatsPerVertex + 3], data[i * floatsPerVertex + 4], data[i * floatsPerVertex + 5]);
        vertex.TexCoords = glm::vec2(vertex.Position.x, vertex.Position.y);
        vertices.push_back(vertex);
    }

    std::vector<GLuint> indices;
    for (GLuint i = 0; i < numVertices; i += 3) {
        indices.push_back(i);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
    }
    Material mat(texture);

    meshes.push_back(Mesh(vertices, indices, mat));
}


void Model:: draw(unsigned int id, ShaderApp& shader) {
    for (Mesh mesh : meshes) {
        mesh.draw(id, shader);
    }
}

Model::~Model()
{
}
*/
void Model::loadModel(std::string path)
{
    Assimp::Importer import;

    unsigned int importOptions = aiProcess_Triangulate
        | aiProcess_OptimizeMeshes             
        | aiProcess_JoinIdenticalVertices       
        | aiProcess_Triangulate                 
        | aiProcess_CalcTangentSpace;


    const aiScene* scene = import.ReadFile(path, importOptions);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Model::Model(std::string path)
{
    loadModel(path);
}

void Model::draw(unsigned int id, ShaderApp& shader)
{
    for (Mesh mesh : meshes) {
        mesh.draw(id, shader);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Material texture;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        vertex.Position.x = mesh->mVertices[i].x;
        vertex.Position.y = mesh->mVertices[i].y;
        vertex.Position.z = mesh->mVertices[i].z;

        vertex.Normal.x = mesh->mNormals[i].x;
        vertex.Normal.y = mesh->mNormals[i].y;
        vertex.Normal.z = mesh->mNormals[i].z;

        if (mesh->mTextureCoords[0]) {
            vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
            vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
        }
        else
        {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        for (int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++) {
            std::cout << "textures: " << material->GetTextureCount(aiTextureType_DIFFUSE) << std::endl;
            aiString str;
            material->GetTexture(aiTextureType_DIFFUSE, i, &str);
            texture = Material(directory + "/" + str.data);
            std::cout << directory + "/" + str.data << std::endl;
        }
    }

    return Mesh(vertices, indices, texture);
}