#include "Object.h"

unsigned int Object::objectCount = 0;



Object::Object(std::string shaderName, std::string modelName) : model(ModelManager::getInstance()->getModel(modelName)) {
	this->shader = ShaderManager::getInstance()->getShader(shaderName);
	this->id = ++objectCount;

	shader.sendUniform("objectColor", objectColor);
	shader.sendUniform("ambientColor", this->ambientColor);
}

unsigned int Object::getId()
{
	return this->id;
}

void Object::addLineMove(glm::vec3 start, glm::vec3 end,float speed)
{
	this->move = new Movement(Direction::Line, start, end, speed);
}
void Object::addCurveMove(glm::vec3 start, glm::vec3 end, glm::vec3 control1, glm::vec3 control2, float speed)
{
	this->move = new Movement(Direction::Curve, start, end,control1,control2, speed);
}

void Object::addCircleMove(glm::vec3 start, int radius,float speed)
{
	this->move = new Movement(Direction::Circle, start, radius,speed);
}

void Object::update()
{
	if (move) {
		glm::vec3 newPos = move->getPos();
		if (parentObject) {
			newPos += parentObject->getPos();
		}
		this->setPos(newPos);
	}
}

void Object::draw() {

	shader.useProgram();

	shader.sendUniform("modelMatrix", this->M);
	glStencilFunc(GL_ALWAYS, this->id, 0xFF);
	this->model.draw(this->id, this->shader);

}

void Object::setColor(glm::vec3 color)
{
	if (this->objectColor == color)
		return;
	this->objectColor = color;
	shader.sendUniform("objectColor", color);
}

void Object::scale(glm::vec3 scale) {
	this->M = glm::scale(this->M, scale);
}


void Object::rotate(float angle, glm::vec3 axis) {
	this->M = glm::rotate(this->M, angle, axis);
}

void Object::translate(glm::vec3 delta) {
	this->M = glm::translate(this->M, delta);
}

void Object::setPos(glm::vec3 pos) {
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), pos);
	this->M[3] = translationMatrix[3];
}

glm::vec3 Object::getPos() const {
	return glm::vec3(this->M[3]);
}
