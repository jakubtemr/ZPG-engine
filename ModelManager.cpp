#include "ModelManager.h"

ModelManager* ModelManager::instance = nullptr;

ModelManager* ModelManager::getInstance() {
	if (!instance) {
		instance = new ModelManager();
	}
	return instance;
}

void ModelManager::initModels() {
	/*this->models.emplace("sun", Model(sphere, 17280, "../final/models/sun.jpg"));
	this->models.emplace("mercury", Model(sphere, 17280,"../final/models/mercury.jpg" ));
	this->models.emplace("venus", Model(sphere, 17280,"../final/models/venus.jpg" ));
	this->models.emplace("earth", Model(sphere, 17280, "../final/models/earth.jpg"));
	this->models.emplace("mars", Model(sphere, 17280,"../final/models/mars.jpg" ));
	this->models.emplace("jupiter", Model(sphere, 17280,"../final/models/jupiter.jpg" ));
	this->models.emplace("saturn", Model(sphere, 17280,"../final/models/saturn.jpg" ));
	this->models.emplace("uranus", Model(sphere, 17280,"../final/models/uranus.jpg" ));
	this->models.emplace("neptune", Model(sphere, 17280,"../final/models/neptune.jpg" ));
	this->models.emplace("ceres", Model(sphere, 17280,"../final/models/ceres.jpg" ));
	this->models.emplace("moon", Model(sphere, 17280, "../final/models/moon.jpg"));
	this->models.emplace("tree", Model(tree, 556884,"../final/models/tree.jpg"));
	this->models.emplace("suziSmooth", Model(suziSmooth,17424, "../final/models/leaf.jpg"));
	this->models.emplace("plain", Model(plain, 36, "../final/models/green.jpg"));
	*/
	this->models.emplace("zombie", Model("../final/models/model/zombie.obj"));
	this->models.emplace("house", Model("../final/models/model/model.obj"));
	this->models.emplace("tree", Model("../final/models/model/tree.obj"));
	this->models.emplace("zed", Model("../final/models/model/zed.obj"));
	this->models.emplace("teren", Model("../final/models/model/teren.obj"));


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
