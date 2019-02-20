#include "pch.h"
#include "ModelLoader.h"

ModelLoader::ModelLoader()
{ }

Model & ModelLoader::Load(const std::string & fileName)
{
	return *m_list[fileName];
}

Model & ModelLoader::Create(const std::string & name, const Mesh & mesh)
{
	if (m_list.find(name) == m_list.end())
	{
		std::shared_ptr<Model> model = std::make_shared<Model>();
		model->Init(mesh);
		m_list[name] = model;
	}

	return *m_list[name];
}