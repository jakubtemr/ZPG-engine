#include "Movement.h"

Movement::Movement(int type, glm::vec3 start, glm::vec3 end)
{
	this->type = type;
	this->start = start;
	this->end = end;
	this->angle = 0;
}

Movement::Movement(int type, glm::vec3 center, int radius)
{
	this->type = type;
	this->start = center;
	this->radius = radius;
	this->angle = 0;
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
	this->angle++;
	return res;
}
