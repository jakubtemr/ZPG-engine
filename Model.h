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
#include <assimp/Importer.hpp>// C++ importerinterface
#include <assimp/scene.h>// aiSceneoutputdata structure
#include <assimp/postprocess.h>// Post processingflags

/*
class Model
{
private:
    std::vector<Mesh> meshes;

public:
    Model(const float* data, size_t dataSize,std::string texture);
    void draw(unsigned int id, ShaderApp& shader);
    ~Model();
};
*/




class Model
{
private:
	std::vector<Mesh> meshes;
	std::string directory;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
public:
	Model(std::string path);
	void draw(unsigned int id, ShaderApp& shader);
};
