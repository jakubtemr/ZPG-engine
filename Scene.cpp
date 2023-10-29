#include "Scene.h"

Scene::Scene(std::vector<Object*> objects, Camera* camera, std::vector<Light*> lights) {
	this->objects = objects;
	this->camera = camera;
	this->lights = lights;
}

int Scene::objectIndex(GLuint id)
{
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id)
			return i;
	}
	return -1;
}

void Scene::Builder::reset()
{
	this->objects = {};
	this->lights = {};
	this->camera = new Camera(glm::vec3(0.f, 0.f, 8.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.0f, 0.0f));
}

Scene::Builder::Builder()
{
	this->reset();
}

void Scene::Builder::addCamera(glm::vec3 eye, glm::vec3 target, glm::vec3 up)
{
	camera = new Camera(eye, target, up);
}

void Scene::Builder::addObject(std::string modelName, std::string shaderName)
{
	this->objects.push_back(new Object(shaderName, modelName));
}

void Scene::Builder::addDirLight(glm::vec3 lightPos, glm::vec3 lightColor)
{
	this->lights.push_back(new Light(lightType::directional, lightPos, lightColor));
}

void Scene::Builder::addSpotLight(glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 lightDir, float cutOff)
{
	this->lights.push_back(new Light(lightType::spot, lightPos, lightColor, lightDir, cutOff));
}

void Scene::Builder::addPointLight(glm::vec3 lightPos, glm::vec3 lightColor)
{
	this->lights.push_back(new Light(lightType::point, lightPos, lightColor));
}


Scene* Scene::Builder::build()
{
	Scene* s = new Scene{ objects, camera, lights };
	this->reset();
	return s;
}
