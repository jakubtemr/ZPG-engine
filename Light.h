#pragma once
#include "LightObservable.h"
#include <vector>
#include <glm/vec3.hpp> // glm::vec3

enum lightType
{
	point, directional, spot
};

class Light : public LightObservable
{
public:
	Light(int type, glm::vec3 lightPos, glm::vec3 lightColor);
	Light(int type, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 lightDir, float cutOff);
	void addLightObserver(LightObserver* observer) override;
	void removeLightObserver(LightObserver* observer) override;
	void notifyLightObservers() override;
	int getLightCount();

private:
	glm::vec3 lightPos;
	glm::vec3 lightColor;
	glm::vec3 lightDir;
	unsigned int id;
	int type;
	float cutOff;

	std::vector<LightObserver*> lightObservers;
	static unsigned int lightCount;
};

