#pragma once
#include <unordered_map>
#include <string>
#include <iostream>

#include "Model.h"
#include "models/suzi_smooth.h"
#include "models/sphere.h"
#include "models/tree.h"

class ModelManager
{
public:
	static ModelManager* getInstance();
	Model& getModel(std::string name);
private:
	std::unordered_map<std::string, Model> models;

	static ModelManager* instance;
	void initModels();
	ModelManager();
};

