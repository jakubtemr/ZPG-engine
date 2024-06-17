#include "Movement.h"

Movement::Movement(int type, glm::vec3 start, glm::vec3 end, float speedFactor = 1.0f)
{
	this->type = type;
	this->start = start;
	this->end = end;
	this->angle = 0;
	this->speedFactor = speedFactor;

}

Movement::Movement(int type, glm::vec3 center, int radius, float speedFactor = 1.0f)
{
	this->type = type;
	this->start = center;
	this->radius = radius;
	this->angle = 0;
	this->speedFactor = speedFactor;
}
Movement::Movement(int type, glm::vec3 start, glm::vec3 end, glm::vec3 control1, glm::vec3 control2, float speedFactor = 1.0f)
{
	this->type = type;
	this->start = start;
	this->end = end;
	this->control1 = control1; 
	this->control2 = control2; 
	this->angle = 0;
	this->speedFactor = speedFactor;
}

glm::vec3 Movement::getPos()
{
	glm::vec3 res;
	if (this->type == Direction::Line) {
		if (this->angle == 180) {
			angle = 0;
		}
		float par = std::sin(angle * M_PI / 180);
		res = (this->start * par) + (this->end * (1 - par));
	}
	if (this->type == Direction::Circle) {
		if (this->angle == 360) {
			angle = 0;
		}
		res.x = start.x + std::cos(angle * M_PI / 180) * radius;
		res.y = start.y;
		res.z = start.z + std::sin(angle * M_PI / 180) * radius;
	}
	if (this->type == Direction::Curve) {
		if (this->angle > 1.0f) {
			angle = 0;
		}
		float t = angle; 

		
		glm::mat4 A = glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
			glm::vec4(3.0, -6.0, 3.0, 0),
			glm::vec4(-3.0, 3.0, 0, 0),
			glm::vec4(1, 0, 0, 0));

		
		glm::mat4x3 B = glm::mat4x3(start, control1, control2, end);

		
		glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);

		
		res = parameters * A * glm::transpose(B);
	}
	this->angle += this->speedFactor;
	return res;
}
