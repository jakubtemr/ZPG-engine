#pragma once
#define _USE_MATH_DEFINES
#include <glm/vec3.hpp>
#include <cmath>
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtx/string_cast.hpp>

enum Direction
{
	Line, Circle,Curve
};

class Movement
{
private:
	int type;
	float angle;
	int radius;
	float speedFactor;

	glm::vec3 start;
	glm::vec3 end;
	glm::vec3 control1;
	glm::vec3 control2;

public:
	Movement(int type, glm::vec3 start, glm::vec3 end,float speedFactor);
	Movement(int type, glm::vec3 center, int radius,float speedFactor);
	Movement(int type, glm::vec3 start, glm::vec3 end, glm::vec3 control1, glm::vec3 control2, float speedFactor);
	glm::vec3 getPos();
};

