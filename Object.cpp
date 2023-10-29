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

void Object::addLineMove(glm::vec3 start, glm::vec3 end)
{
	this->move = new Movement(Direction::Line, start, end);
}

void Object::addCircleMove(glm::vec3 start, int radius)
{
	this->move = new Movement(Direction::Circle, start, radius);
}

void Object::update()
{
	if (move == NULL) {
		return;
	}
	this->setPos(move->getPos());
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

void Object::setPos(glm::vec3 pos)
{
	this->M = glm::translate(glm::mat4(1.0f), pos);
}
