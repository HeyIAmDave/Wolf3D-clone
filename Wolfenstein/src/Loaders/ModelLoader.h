#pragma once
#include "BaseLoader.h"
#include "Rendering/Model.h"

class ModelLoader : public BaseLoader<Model>
{
public:
	ModelLoader();

	virtual Model& Load(const std::string& fileName) override;
	Model& Create(const std::string& name, const Mesh& mesh);
};