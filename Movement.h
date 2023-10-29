#pragma once
#define _USE_MATH_DEFINES
#include <glm/vec3.hpp>
#include <cmath>

enum Direction
{
	Line, Circle
};

class Movement
{
private:
	int type;
	float angle;
	int radius;

	glm::vec3 start;
	glm::vec3 end;

public:
	Movement(int type, glm::vec3 start, glm::vec3 end);
	Movement(int type, glm::vec3 center, int radius);

	glm::vec3 getPos();
};

