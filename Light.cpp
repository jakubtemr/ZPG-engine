#include "Light.h"

unsigned int Light::lightCount = 0;

Light::Light(int type, glm::vec3 lightPos, glm::vec3 lightColor)
{
	this->id = lightCount++;
	this->type = type;
	this->lightPos = lightPos;
	this->lightColor = lightColor;
}

Light::Light(int type, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 lightDir, float cutOff)
{
	this->id = lightCount++;
	this->type = type;
	this->lightPos = lightPos;
	this->lightColor = lightColor;
	this->lightDir = lightDir;
	this->cutOff = cutOff;
}

void Light::addLightObserver(LightObserver* obs)
{
	this->lightObservers.push_back(obs);
}

void Light::removeLightObserver(LightObserver* obs)
{
	auto iterator = std::find(this->lightObservers.begin(), this->lightObservers.end(), obs);

	if (iterator != this->lightObservers.end()) {
		this->lightObservers.erase(iterator); 
	}
}

void Light::notifyLightObservers()
{
	for (LightObserver* observer : this->lightObservers) {
		if (type == point || type == directional) {
			observer->update(this->id, this->type, this->lightPos, this->lightColor, lightCount);
		}
		else {
			observer->update(this->id, this->type, this->lightPos, this->lightColor, this->lightDir, this->cutOff, lightCount);
		}
	}
}

int Light::getLightCount()
{
	return this->lightCount;
}
