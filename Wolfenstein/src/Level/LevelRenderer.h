#pragma once
#include "Rendering/Material.h"

class LevelRenderer
{
public:
	LevelRenderer();

	void Init(const std::string& name, const Mesh& mesh);
	void Render();
	void CleanUp();
private:
	bool m_initialized;
	Model m_model;
	Material m_material;
};