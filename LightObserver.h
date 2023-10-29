#pragma once
#include <glm/mat4x4.hpp> // glm::mat4
class LightObserver
{
public:
	virtual void update(int id, int type, glm::vec3 lightPos, glm::vec3 lightColor, int lightCount) = 0;
	virtual void update(int id, int type, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 lightDir, float cutOff, int lightCount) = 0;
};
