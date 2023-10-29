#include "ModelManager.h"

ModelManager* ModelManager::instance = nullptr;

ModelManager* ModelManager::getInstance() {
	if (!instance) {
		instance = new ModelManager();
	}
	return instance;
}

void ModelManager::initModels() {
	this->models.emplace("sphere", Model(sphere, 17280));
	this->models.emplace("tree", Model(tree, 92814));

}

Model& ModelManager::getModel(std::string name)
{
	auto s = this->models.find(name);
	if (s != models.end()) {
		return s->second;
	}
	throw std::runtime_error("Bad observer model!");
}

ModelManager::ModelManager() {
	initModels();
}
