#pragma once
#include <glm/mat4x4.hpp> // glm::mat4

class CameraObserver
{
public:
	virtual void update(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 camPos) = 0;
};