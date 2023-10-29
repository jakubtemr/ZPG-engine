#pragma once
#include "Object.h"
#include "Camera.h"
#include "Light.h"
class Scene
{
private:
	Scene(std::vector<Object*> objects, Camera* camera, std::vector<Light*> lights);

public:
	std::vector<Object*> objects;
	Camera* camera;
	std::vector<Light*> lights;
	int objectIndex(GLuint id);

	class Builder {
	private:
		Camera* camera;
		std::vector<Object*> objects;
		std::vector<Light*> lights;

		void reset();

	public:
		Builder();
		void addCamera(glm::vec3 eye, glm::vec3 target, glm::vec3 up);
		void addObject(std::string modelName, std::string shaderName);
		void addPointLight(glm::vec3 lightPos, glm::vec3 lightColor);
		void addDirLight(glm::vec3 lightPos, glm::vec3 lightColor);
		void addSpotLight(glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 lightDir, float cutOff);
		Scene* build();
	};
};

